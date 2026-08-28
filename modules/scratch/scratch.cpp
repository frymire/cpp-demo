#include <iostream>
using std::cout;

namespace {

  class Traceable {

  public:
    Traceable() { cout << "Constructor called\n"; }
    Traceable([[maybe_unused]] const Traceable& other) { cout << "Copy constructor called\n"; }
    Traceable([[maybe_unused]] Traceable&& other) noexcept { cout << "Move constructor called\n"; }
    ~Traceable() { cout << "Destructor called\n"; }
  };

  // This directly returns a pure r-value (prvalue), an expression that computes a value with no persistent storage of
  // its own.  It is therefore a candidate for RVO, which writes directly into callers storage. This behavior is
  // guaranteed as of C++17.
  Traceable create_traceable() { return Traceable(); }

  Traceable create_traceable_with_named_temporary() {

    Traceable named_temporary;  // an l-value (i.e. "named")
    std::cout << "Before return\n";
    return named_temporary;  // named RVO (NRVO) is permitted for an l-value, but not guaranteed

    // NRVO requires the compiler to prove, statically, that exactly one specific local object will occupy the return
    // slot no matter which path execution takes. Otherwise, the compiler falls back to a move or copy constructor.
    // These break it:
    // - branching between different named objects
    // - indirection through parameters/members
    // - explicit std::move on a would-be-elided value
  }
}  // namespace

int main() {

  {
    cout << "About to call create_traceable()\n";
    Traceable obj = create_traceable();  // would use copy constructor without RVO
    cout << "Back in main\n";
  }

  {
    cout << "\nAbout to call create_traceable_with_named_temporary()\n";
    Traceable obj = create_traceable_with_named_temporary();  // will likely use NRVO instead of copy constructor
    cout << "Back in main\n";
  }
  return 0;
}
