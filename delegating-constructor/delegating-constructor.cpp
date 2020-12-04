
// Define a constructor based on a previously-defined constructor.
// See: https://stackoverflow.com/questions/308276/can-i-call-a-constructor-from-another-constructor-do-constructor-chaining-in-c

#include <iostream>
using std::cout;
using std::endl;

class Foo {

  char m_x;
  int m_y;

public:
  Foo(char x, int y) : m_x(x), m_y(y) {}
  Foo(int y) : Foo('Z', y) {} // C++11
  void print() { cout << m_x << " " << m_y << endl;  }
};

int main() {
  
  Foo foo1('A', 1);
  foo1.print(); 
  
  Foo foo2(2);
  foo2.print();  
}
