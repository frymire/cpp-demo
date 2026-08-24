
// Demonstrate templates.
// See here: https://www.youtube.com/watch?v=I-hZkUa9mIs&list=WL&index=76

#include <iostream>
using std::cout;
using std::endl;

namespace {
  template<typename T> void print(T value) { cout << value << endl; }

  // Unlike Java generics, which depend on the type system, C++ templates let you pass
  // other categories of information. Here, use it to create whole class types on the fly.
  // You're effectively programming what the compiler will do during compile-time.
  template<typename T, int N>
  class Array {
  private:
    T m_array[N];
  public:
    // ReSharper disable once CppMemberFunctionMayBeStatic
    [[nodiscard]] T get_size() const { return N; }
  };
}

int main() {

  // Implicit calls
  print(5);
  print("Hello");
  print(5.5f);

  // Explicit calls
  print<int>(5);
  print<const char*>("Hello");
  print<float>(5.5f);

  // Pass an array type and size via the template argument.
  constexpr Array<int, 10> my_array{};
  cout << endl << my_array.get_size() << endl;
}
