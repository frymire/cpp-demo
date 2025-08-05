// C++ doesn't support virtual static member variables, but you can get the same effect using concepts.

#include <array>
#include <concepts>
#include <iostream>

// Require static constexpr indices
template <typename T>
concept HasIndices = requires {
  { T::indices } -> std::convertible_to<const std::array<int, std::tuple_size<decltype(T::indices)>::value>&>;
};

template <typename Derived>  // curiously recurring template pattern (CRTP)
class Parent {
public:
  void print_indices() const {
    for (int idx : Derived::indices) {
      std::cout << idx << ' ';
    }
    std::cout << '\n';
  }
};

class Child1 : public Parent<Child1> {
public:
  static constexpr std::array<int, 3> indices = {1, 2, 3};
};

class Child2 : public Parent<Child2> {
public:
  static constexpr std::array<int, 3> indices = {4, 5, 6};
};

template <HasIndices T>
class Composite : public Parent<Composite<T>> {
public:
  static constexpr auto& indices = T::indices;
};

int main() {
  Child1().print_indices();                  // → 1 2 3
  Child2().print_indices();          // → 4 5 6
  Composite<Child1>().print_indices(); // → 1 2 3
  return 0;
}
