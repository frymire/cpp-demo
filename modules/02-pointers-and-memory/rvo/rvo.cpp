// Return value optimization (RVO), named RVO (NRVO), and the cases where NRVO cannot apply.
//
// Copy elision lets the compiler skip a copy or move by constructing the returned object directly in the caller's
// storage. Two flavors:
//
//   - RVO, for a returned prvalue. Mandatory as of C++17: there is no temporary to elide, because the prvalue's
//     initializer is simply applied to the caller's storage.
//   - NRVO, for a returned named local (an lvalue). Always optional; the compiler may do it, but is never required to.
//
// When NRVO does not happen, the return is not silently a copy. A returned local name is treated as an rvalue first
// (the implicit-move rule), so the move constructor runs, and the copy constructor only steps in if no move
// constructor is viable, or if the returned expression does not qualify for the implicit move at all.

#include <iostream>
#include <utility>
using std::cout;

namespace {

  // Traceable owns nothing, so its copies and moves are equally cheap. It carries an id purely so the output can be
  // read as a story: which object was built, from which, and when it died.
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

    // Copy assignment. Not needed by the demos below, but declaring the move assignment operator deletes the implicit
    // copy assignment operator, so the Rule of 5 says to write it out.
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
  };

  int Traceable::s_next_id = 1;


  // --- Elision works ------------------------------------------------------------------------------------------------

  // This directly returns a pure rvalue (prvalue), an expression that computes a value with no persistent storage of
  // its own. It is therefore a candidate for RVO, which writes directly into the caller's storage. This behavior is
  // guaranteed as of C++17.
  Traceable create_traceable() { return Traceable(); }

  Traceable create_traceable_with_named_temporary() {

    Traceable named_temporary;  // an lvalue (i.e. "named")
    cout << "  (before return)\n";
    return named_temporary;  // named RVO (NRVO) is permitted for an lvalue, but not guaranteed

    // NRVO requires the compiler to prove, statically, that exactly one specific local object will occupy the return
    // slot no matter which path execution takes. Otherwise the compiler falls back to a move, or to a copy if the
    // returned expression is not implicitly movable. These break it:
    // - branching between different named objects
    // - indirection through parameters/members
    // - explicit std::move on a would-be-elided value
    //
    // Each is demonstrated below.
  }


  // --- Reason 1: branching between different named objects ----------------------------------------------------------

  // Two locals compete for the single return slot, and which one wins is known only at run time, so the compiler cannot
  // construct either of them in the caller's storage up front. The returned name is still implicitly moved, so this
  // costs a move constructor rather than a copy.
  Traceable create_with_branch(const bool use_first) {

    Traceable first;
    Traceable second;
    cout << "  (before return)\n";

    if (use_first) return first;
    return second;

    // Hoisting the branch above the objects, so that only the one to be returned is ever constructed, restores NRVO.
  }


  // --- Reason 2: indirection through parameters and members ---------------------------------------------------------

  // A by-value parameter lives in storage the *caller* laid out as part of the call, not in the return slot, so NRVO is
  // forbidden outright rather than merely optional. Parameters are still implicitly movable on return, so this costs a
  // move, not a copy.
  Traceable create_from_parameter(Traceable incoming) { return incoming; }

  struct Holder { Traceable member; };

  // A member of a local is a subobject: it sits at some offset inside its parent, which occupies its own storage and
  // still has to be destroyed, so there is no way to place it in the return slot instead. Worse, the implicit-move rule
  // applies only to an expression that names a movable local object outright, and holder.member is a member access, not
  // such a name. So this falls all the way back to the *copy* constructor. Writing std::move(holder.member) buys the
  // move back, at the cost of leaving the parent holding a hollowed-out member.
  Traceable create_from_member() {

    Holder holder;
    cout << "  (before return)\n";
    return holder.member;
  }


  // --- Reason 3: explicit std::move on a would-be-elided value ------------------------------------------------------

  // std::move is a cast to an rvalue reference, so the return operand stops being the name of a local object and
  // becomes an xvalue that merely refers to one. NRVO needs the name; the cast hides it. The result is a guaranteed
  // move where the compiler was poised to give a guaranteed nothing. This is the classic "pessimizing move" that
  // -Wpessimizing-move (gcc and clang alike) and clang-tidy's performance-no-automatic-move warn about.
  Traceable create_with_explicit_move() {

    Traceable local;
    cout << "  (before return)\n";
    return std::move(local);  // don't do this; "return local;" already moves when it cannot elide
  }

  // The same mistake against a prvalue is worse, because there it defeats the elision that C++17 *guarantees*: the
  // temporary now has to be materialized so std::move has something to bind to, and is then moved into the caller.
  Traceable create_with_explicit_move_of_prvalue() { return std::move(Traceable()); }  // NOLINT(*-move-const-arg)

}  // namespace

int main() {

  cout << "Return a prvalue (guaranteed RVO since C++17)...\n";
  {
    Traceable obj = create_traceable();  // one construction, one destruction, and nothing in between
    cout << "  (back in main)\n";
  }

  cout << "\nReturn a named local (NRVO permitted, not guaranteed)...\n";
  {
    Traceable obj = create_traceable_with_named_temporary();
    cout << "  (back in main)\n";
  }

  cout << "\nNRVO broken by branching between two named locals...\n";
  {
    Traceable obj = create_with_branch(true);
    cout << "  (back in main)\n";
  }

  cout << "\nNRVO forbidden for a by-value parameter...\n";
  {
    Traceable argument;
    Traceable obj = create_from_parameter(argument);  // copy into the parameter, then move out of it
    cout << "  (back in main)\n";
  }

  cout << "\nNRVO impossible for a member of a local, and the implicit move does not apply either...\n";
  {
    Traceable obj = create_from_member();
    cout << "  (back in main)\n";
  }

  cout << "\nNRVO suppressed by an explicit std::move on the returned local...\n";
  {
    Traceable obj = create_with_explicit_move();
    cout << "  (back in main)\n";
  }

  cout << "\nGuaranteed RVO defeated by an explicit std::move on the returned prvalue...\n";
  {
    Traceable obj = create_with_explicit_move_of_prvalue();
    cout << "  (back in main)\n";
  }

  cout << "\nAssignment is never elided, no matter how the right-hand side was produced...\n";
  {
    Traceable obj;
    obj = create_traceable();  // the returned prvalue is materialized, move-assigned, then destroyed
    cout << "  (back in main)\n";
  }

  return 0;
}
