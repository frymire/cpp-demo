
#include <iostream>
using std::cout;
using std::endl;

namespace {

  // This is the long way of passing data by reference to a function.
  void increment_elaborately(int* p_value) { (*p_value)++; }

  // Here's a cleaner way to do the same thing.
  void increment(int& value) { value++;  }
}

int main() {

  int a = 5;
  cout << a << endl;

  // Create an alias to the variable a.
  int& ref = a;
  ref = 2;
  cout << a << endl;

  increment_elaborately(&a);
  cout << a << endl;

  increment(a);
  cout << a << endl;
}
