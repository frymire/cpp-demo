
// Demonstrate function pointers.
// See here: https://www.youtube.com/watch?v=p4sDgQ-jao4&list=WL&index=16

#include <iostream>
using std::cout;
using std::endl;

#include <vector>

namespace {
  void say_hello_world(const int value) { cout << "Hello World! Value = " << value << endl; }
  void say_goodbye_world(const int value) { cout << "Goodbye, cruel world! Value = " << value << endl; }
  void my_for_each(const std::vector<int>& values, void(*func)(int)) { for (const int v : values) func(v); }
}

int main() {

  // The actual type for a function pointer looks weird: "void (*{name})(int)". To declare 
  // a function pointer variable called "hello", do this...(or just use auto when you assign it).
  // So here, hello is a pointer to a function that takes an int and returns void.
  void (*hello)(int);
  
  // Now assign it to a function, just like any other variable. Without (), "say_hello_world" gives
  // you the function pointer, which is the address where the say_hello_world function is stored.
  hello = say_hello_world;
  cout << "Address of say_hello_world() = " << &say_hello_world << endl; // same
  cout << "Value of hello function pointer = " << hello << endl; // same 
  cout << "Address of hello function pointer = " << &hello << endl << endl; // different

  hello(5);
  hello(10);

  // Here's how you might use it.
  const std::vector my_values = {1, 5, 3, 4, 2};
  cout << endl;
  my_for_each(my_values, say_hello_world);
  cout << endl;
  my_for_each(my_values, say_goodbye_world);
}
