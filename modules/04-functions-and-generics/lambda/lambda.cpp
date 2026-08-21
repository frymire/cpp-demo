
// Demo lambda functions.
// See here: https://www.youtube.com/watch?v=mWgmBBz0y8c&list=WL&index=17
// And here: https://www.youtube.com/watch?v=bP9z3H3cVMY&list=WL&index=62

#include <iostream>
using std::cout;
using std::endl;

#include <vector>

#include <functional> 
// using std::function;

// Define a function to which we will pass a lambda function. If the lambda function won't capture any variables, 
// you could use a raw function pointer. Otherwise, use std::function.
//void MyForEach(const std::vector<int>& values, void(*func)(int)) { for (int v : values) func(v); }
void MyForEach(const std::vector<int>& values, const std::function<void(int)>& f) { for (int v : values) f(v); }

int main() {

  // Pass a lambda function to MyForEach (or anywhere else you can use a function pointer). The [] notation 
  // denotes the capture method, which provides a means to use variables from the local scope. Use [=] to pass 
  // all parameters by value, [&] to pass all by reference, [a, &b] to capture a by value and b by reference, and 
  // [] to capture nothing. The optional "-> {type}" notation on the interior explicitly declares the return type.
  std::vector<int> my_values = {1, 5, 3, 4, 2};
  auto print_value = [](int value) { cout << "Value = " << value << endl; };
  //auto print_value = [](int value) -> void { cout << "Value = " << value << endl; }; // explicit void return
  MyForEach(my_values, print_value);


  // Demonstrate the (rarely used) "mutable" keyword for lambda functions. Suppose we are passing by value to 
  // leave variables in the surrounding scope unchanged...
  int count = 0, y = 10;
  auto write_count_and_y = [=]() mutable {

    // ...but, we want to increment count just within the function.
    count++; // only possible when passing by value [=] for mutable lambda functions 
    cout << "Count (lambda) = " << count << endl; // 1
    cout << y << endl; 
  };

  write_count_and_y();
  cout << "count (main) = " << count << endl; // still 0
}
