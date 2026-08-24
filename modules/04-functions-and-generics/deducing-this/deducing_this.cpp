
// Demonstrate the C++23 explicit object parameter, known informally as "deducing this". It replaces most uses of the
// Curiously Recurring Template Pattern. See the crtp module for the older form.

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>

namespace {

  // Compare this with the crtp module. The base needs no template parameter, no static_cast, and no
  // circular reference to the derived class. It is a plain class.
  struct PrintableTwice {

    // Write the object the function was called on as the first parameter, marked with
    // the keyword "this". The compiler deduces its real type at the call site.
    void print_twice(this const auto& self) {
      self.print();
      self.print();
    }
  };

  struct Vertex : PrintableTwice { static void print() { cout << "vertex" << endl; } };
  struct Circle : PrintableTwice { static void print() { cout << "circle" << endl; } };

  // A second use. Before C++23, a getter that works on both const and non-const objects needed two
  // near-identical functions. Here, "this auto& self" deduces the constness, so one function does
  // the work of both, and the return type follows automatically.
  class Box {
    string m_label;
  public:
    explicit Box(string label) : m_label(std::move(label)) {}
    auto& get_label(this auto& self) { return self.m_label; }
  };

}  // namespace

int main() {

  cout << "The base class calls print() in the derived class, with no template parameter...\n";
  constexpr Vertex vertex;
  vertex.print_twice();
  constexpr Circle circle;
  circle.print_twice();

  cout << "\nOne getter serves both const and non-const objects...\n";
  Box box("first");
  box.get_label() = "second"; // self is Box&, so label() returns string&
  cout << box.get_label() << endl;

  const Box const_box("locked");
  cout << const_box.get_label() << endl; // self is const Box&, so label() returns const string&
  // const_box.label() = "no"; // compile error, exactly as you want

  // A third use. A lambda now has a name for itself, so it can call itself. Before C++23, a
  // recursive lambda needed a std::function or an awkward helper.
  cout << "\nA lambda can now call itself...\n";
  auto factorial = [](this auto&& self, const int n) -> int { return (n <= 1) ? 1 : n * self(n - 1); };
  cout << "factorial(5) = " << factorial(5) << endl; // 120

  return 0;
}
