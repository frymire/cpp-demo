// Demonstrate the equivalent of <ChildType extends ParentType> type extension in Java, both the
// pre-C++20 enable_if idiom and the C++20 concept that replaces it. See:
// https://stackoverflow.com/questions/30687305/c-equivalent-of-using-t-extends-class-for-a-java-parameter-return-type
// https://en.cppreference.com/w/cpp/concepts/derived_from

#include <iostream>
using std::cout;
using std::endl;

#include <type_traits>
using std::enable_if;
using std::is_base_of;

#include <concepts>
using std::derived_from;

namespace {
  class ParentClass {
  public:
    [[maybe_unused]] const char* name = "parent";
  };

  class ChildClass : public ParentClass {
  public:
    const char* name = "child";
  };

  class OtherClass {
  public:
    [[maybe_unused]] const char* name = "other";
  };

  // The pre-C++20 approach. is_base_of answers the question, but there is nowhere natural to put
  // the answer, so it goes in a dummy template parameter that exists only to disappear: if the
  // condition is false, enable_if has no member type, substitution fails, and the overload drops
  // out of the candidate set. The requirement is invisible in the signature, and a bad call is
  // reported as deduction failure without saying what was wanted.
  template <typename T, typename enable_if<is_base_of<ParentClass, T>::value>::type* = nullptr>
  T get_parameter_enable_if([[maybe_unused]] T x) { return T(); }

  // The same constraint in C++20. A concept named in the template parameter list takes T as its
  // implicit first argument, so this reads as derived_from<T, ParentClass> -- note the argument
  // order is flipped relative to is_base_of<ParentClass, T>. The requirement is now part of the
  // declaration, and a bad call reports which constraint failed. derived_from is also stricter
  // than is_base_of: it insists the inheritance be public and unambiguous, i.e. that T is really
  // usable as a ParentClass.
  template <derived_from<ParentClass> T>
  T get_parameter([[maybe_unused]] T x) { return T(); }

}  // namespace

int main() {

  constexpr ChildClass child;
  cout << get_parameter_enable_if(child).name << endl;  // both work because ChildClass
  cout << get_parameter(child).name << endl;            // derives from ParentClass

  // A concept is an ordinary compile-time predicate, so you can also just ask it directly.
  static_assert(derived_from<ChildClass, ParentClass>);
  static_assert(!derived_from<OtherClass, ParentClass>);

  [[maybe_unused]] OtherClass other;
  //cout << get_parameter_enable_if(other).name << endl;  // error: template argument deduction failed
  //cout << get_parameter(other).name << endl;            // error: constraint not satisfied, and the
                                                          // diagnostic names the failed requirement
}
