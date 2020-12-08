
// Demonstrate function pointers.
// See here: https://www.youtube.com/watch?v=p4sDgQ-jao4&list=WL&index=16

#include <iostream>
using std::cout;
using std::endl;

#include <vector>

void HelloWorld(int value) { cout << "Hello World! Value = " << value << endl; }
void GoodbyeWorld(int value) { cout << "Goodbye, cruel world! Value = " << value << endl; }

void MyForEach(const std::vector<int>& values, void(*func)(int)) { for (int v : values) func(v); }

int main() {

  // The actual type for a function pointer looks weird: "void (*{name})(int)". To declare 
  // a function pointer variable called "hello", do this...(or just use auto when you assign it).
  void (*hello)(int);
  
// Now assign it to a function, just like any other variable. Without (), "HelloWorld" gives 
  // you the function pointer, which is the address where the HelloWorld function is stored. 
  hello = HelloWorld;
  cout << "Address of HelloWorld() = " << &HelloWorld << endl; // same
  cout << "Value of hello function pointer = " << hello << endl; // same 
  cout << "Address of hello function pointer = " << &hello << endl << endl; // different

  hello(5);
  hello(10);

  // Here's how you might use it.
  std::vector<int> my_values = {1, 5, 3, 4, 2};
  cout << endl;
  MyForEach(my_values, HelloWorld);
  cout << endl;
  MyForEach(my_values, GoodbyeWorld);
}
