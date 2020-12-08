
// Demo lambda functions.
// See here:
// And here: https://www.youtube.com/watch?v=bP9z3H3cVMY&list=WL&index=62

#include <iostream>
using std::cout;
using std::endl;

int main() {

  // Use [=] to pass by value, [&] to pass by reference.


  // Demonstrate the (rarely used) "mutable" keyword for lambda functions....
  int count = 0, y = 10;

  // Passing by value should leave variables in the surrounding scope unchanged.
  auto f = [=]() mutable {

    // But, we want to increment count just within the function.
    count++; // only possible when passing by value [=] for mutable lambda functions 
    cout << "Count (lambda) = " << count << endl; // 1
    cout << y << endl; 
  };

  f();
  cout << "count (main) = " << count << endl; // still 0
}
