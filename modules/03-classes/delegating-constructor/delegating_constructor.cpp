
// Define a constructor based on a previously-defined constructor.
// See: https://stackoverflow.com/questions/308276/can-i-call-a-constructor-from-another-constructor-do-constructor-chaining-in-c

#include <iostream>
using std::cout;
using std::endl;

namespace {

  class Foo {
    char m_x;
    int m_y;
  public:
    Foo(const char x, const int y) : m_x(x), m_y(y) {}
    explicit Foo(const int y) : Foo('Z', y) {} // C++11
    void print() const { cout << m_x << " " << m_y << endl;  }
  };

} // namespace

int main() {

  const Foo foo1('A', 1);
  foo1.print();

  const Foo foo2(2);
  foo2.print();
}
