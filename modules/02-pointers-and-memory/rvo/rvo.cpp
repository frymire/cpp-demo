// Return value optimization (RVO), named RVO (NRVO), and the cases where NRVO cannot apply.

// ReSharper disable CppJoinDeclarationAndAssignment
// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppEntityAssignedButNoRead

#include <iostream>
#include <utility>
using std::cout;

namespace {

  class Traceable {

    static int s_next_id;
    int m_id;

  public:

    Traceable(): m_id(s_next_id++) { cout << "  #" << m_id << " constructor\n"; }

    Traceable(const Traceable& other): m_id(s_next_id++) {
      cout << "  #" << m_id << " copy constructor (from #" << other.m_id << ")\n";
    }

    Traceable(Traceable&& other) noexcept: m_id(s_next_id++) {
      cout << "  #" << m_id << " move constructor (from #" << other.m_id << ")\n";
    }

    // Copy assignment. Declaring the move assignment operator deletes the implicit
    // copy assignment operator, so we add it to satisfy the Rule of 5.
    Traceable& operator=(const Traceable& other) {
      if (this == &other) return *this;  // a no-op here, but a real resource owner must not delete its own data
      cout << "  #" << m_id << " copy assignment (from #" << other.m_id << ")\n";
      return *this;
    }

    // Move assignment. Note that assignment is never elided: the object on the left already exists, so there is no
    // uninitialized storage for the compiler to construct into.
    Traceable& operator=(Traceable&& other) noexcept {
      if (this == &other) return *this;
      cout << "  #" << m_id << " move assignment (from #" << other.m_id << ")\n";
      return *this;
    }

    ~Traceable() { cout << "  #" << m_id << " destructor\n"; }

    // Restarts the numbering, so each demo scope in main traces its own objects from #1 instead of continuing the
    // count across every scope in the file.
    static void reset_ids() { s_next_id = 1; }
  };

  int Traceable::s_next_id = 1;


  // --- Elision works ------------------------------------------------------------------------------------------------

  // This directly returns a pure rvalue (prvalue), an expression that computes a value with no persistent storage of
  // its own. It is therefore a candidate for RVO, which writes directly into the caller's storage. This behavior is
  // guaranteed as of C++17.
  Traceable create_traceable() { return Traceable(); }

  // NRVO requires the compiler to prove, statically, that exactly one specific local object will occupy the return
  // slot no matter which path execution takes.
  Traceable create_traceable_with_named_temporary() {
    Traceable named_temporary;  // an lvalue (i.e. "named")
    cout << "  (before return)\n";
    return named_temporary;  // named RVO (NRVO) is permitted for an lvalue, but not guaranteed
  }

  // If RVO and NRVO fail, the compiler falls back to a move, or to a copy if the returned expression is not
  // implicitly movable. The examples below demonstrate these failures in action.

  // NRVO Failure #1: branching between different named objects
  Traceable create_with_branch(const bool use_first) {
    // Two locals compete for the single return slot, and which one wins is known only at run time, so the compiler
    // cannot construct either of them in the caller's storage up front. The returned name is still implicitly moved,
    // so this costs a move constructor rather than a copy.
    Traceable first, second;
    cout << "  (before return)\n";
    if (use_first) return first;
    return second;
  }

  // NRVO Failure #1 (Restored): Hoisting the branch above the objects restores NRVO, because each path now holds
  // exactly one named local, and every return in that scope hands back that one object - the proof the compiler needs.
  // Constructing only the object to be returned is a second, separate saving: it is what shrinks the trace from two
  // constructions to one, while NRVO is what removes the move at the return. Even a compiler that declined NRVO here
  // would still build just one object and move it.
  Traceable create_with_hoisted_branch(const bool use_first) {
    if (use_first) {
      Traceable first;
      cout << "  (before return)\n";
      return first;
    }

    Traceable second;
    cout << "  (before return)\n";
    return second;
  }

  // --- Reason 2: indirection through parameters and members ---------------------------------------------------------

  // NRVO Failure #2: indirection through parameters. A by-value parameter lives in storage the *caller* laid out as
  // part of the call, not in the return slot, so NRVO is forbidden outright. Parameters are still implicitly movable
  // on return, so this costs a move, not a copy.
  Traceable create_from_parameter(Traceable incoming) { return incoming; }

  // NRVO Failure #3: indirection through members. A member of a local is a subobject: it sits at some offset inside
  // its parent, which occupies its own storage and still has to be destroyed, so there is no way to place it in the
  // return slot instead. Worse, the implicit-move rule applies only to an expression that names a movable local object
  // outright, and holder.member is a member access, not such a name. So this falls all the way back to the *copy*
  // constructor. Writing std::move(holder.member) buys the move back, at the cost of leaving the parent holding a
  // hollowed-out member.
  struct Holder { Traceable member; };
  Traceable create_from_member() {
    Holder holder;
    cout << "  (before return)\n";
    return holder.member;
  }

  // NRVO Failure #4: explicit std::move on a would-be-elided value. std::move is a cast to an rvalue reference, so the
  // return operand stops being the name of a local object and becomes an xvalue that merely refers to one. NRVO needs
  // the name; the cast hides it. The result is a guaranteed move where the compiler was poised to give a guaranteed
  // nothing. This is the classic "pessimizing move" that -Wpessimizing-move (gcc and clang alike) and clang-tidy's
  // performance-no-automatic-move warn about.
  Traceable create_with_explicit_move() {
    Traceable local;
    cout << "  (before return)\n";
    return std::move(local);  // don't do this; "return local;" already moves when it cannot elide
  }

  // NRVO Failure #5: explicit std::move on a guaranteed-to-be-elided value. This same mistake against a prvalue is
  // worse, because there it defeats the elision that C++17 *guarantees*: the temporary now has to be materialized so
  // std::move has something to bind to, and is then moved into the caller.
  Traceable create_with_explicit_move_of_prvalue() { return std::move(Traceable()); }  // NOLINT(*-move-const-arg)

}  // namespace

int main() {

  {
    cout << "\nReturn a prvalue (guaranteed RVO since C++17)...\n";
    Traceable::reset_ids();
    Traceable obj = create_traceable();  // one construction (#1) in the function is written directly here
    cout << "  (back in main)\n";
  }  // #1 destroyed

  {
    cout << "\nReturn a named local (NRVO permitted, not guaranteed)...\n";
    Traceable::reset_ids();
    Traceable obj = create_traceable_with_named_temporary();  // #1 constructed in the function is written directly here
    cout << "  (back in main)\n";
  }  // #1 destroyed

  {
    cout << "\nAssignment is never elided, no matter how the right-hand side was produced...\n";
    Traceable::reset_ids();
    [[maybe_unused]] Traceable obj;  // #1 constructed here
    // #2, the returned prvalue, is materialized here, move-assigned into #1, and destroyed at the end of the
    // statement.
    obj = create_traceable();
    cout << "  (back in main)\n";
  }  // #1 destroyed

  {
    cout << "\nNRVO broken by branching between two named locals...\n";
    Traceable::reset_ids();
    // #1 and #2 are constructed in the function; #3 is move constructed here from #1, and then #2 and #1 are
    // destroyed as the function ends.
    Traceable obj = create_with_branch(true);
    cout << "  (back in main)\n";
  }  // #3 destroyed

  {
    cout << "\nNRVO restored by hoisting the branch, which also constructs only the returned object...\n";
    Traceable::reset_ids();
    Traceable obj = create_with_hoisted_branch(true);  // one construction (#1) is written directly here
    cout << "  (back in main)\n";
  }  // #1 destroyed

  {
    cout << "\nNRVO forbidden for a by-value parameter...\n";
    Traceable::reset_ids();
    Traceable argument;  // #1 constructed here
    // #2 is copy constructed into the parameter from #1, #3 is move constructed here from #2, and #2 is destroyed
    // as the call ends.
    Traceable obj = create_from_parameter(argument);
    cout << "  (back in main)\n";
  }  // #3, then #1 destroyed (reverse construction order)

  {
    cout << "\nNRVO impossible for a member of a local, and the implicit move does not apply either...\n";
    Traceable::reset_ids();
    // #1 is constructed in the function as the holder's member, #2 is copy constructed here from it, and #1 is
    // destroyed with its holder as the function ends.
    Traceable obj = create_from_member();
    cout << "  (back in main)\n";
  }  // #2 destroyed

  {
    cout << "\nNRVO suppressed by an explicit std::move on the returned local...\n";
    Traceable::reset_ids();
    // #1 is constructed in the function, #2 is move constructed here from it, and #1 is destroyed as the function
    // ends.
    Traceable obj = create_with_explicit_move();
    cout << "  (back in main)\n";
  }  // #2 destroyed

  {
    cout << "\nGuaranteed RVO defeated by an explicit std::move on the returned prvalue...\n";
    Traceable::reset_ids();
    // #1 is the temporary materialized in the function for std::move to bind to, #2 is move constructed here from
    // it, and #1 is destroyed at the end of the return statement.
    Traceable obj = create_with_explicit_move_of_prvalue();
    cout << "  (back in main)\n";
  }  // #2 destroyed

  return 0;
}
