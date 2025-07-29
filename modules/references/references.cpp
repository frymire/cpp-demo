
#include <iostream>
using std::cout;
using std::endl;

// This is the long way of passing data by reference to a function.
void ElaborateIncrement(int* p_value) { (*p_value)++; }

// Here's a cleaner way to do the same thing.
void Increment(int& value) { value++;  }

int main() {

  int a = 5;
  int b = 8;
  cout << a << endl;

  // Create an alias to the variable a.
  int& ref = a;
  ref = 2;
  cout << a << endl;

  ElaborateIncrement(&a);
  cout << a << endl;

  Increment(a);
  cout << a << endl;
}
