
// Demonstrate what happens when you declare variables and functions as static.
// See here: https://www.youtube.com/watch?v=f3FVU-iwNuA&list=WL&index=64
// And here: https://www.youtube.com/watch?v=V-BFlMrBtqQ&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=22
// And here: https://www.youtube.com/watch?v=f7mtWD9GdJ4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=23&t=1s

#include <iostream>
using std::cout;
using std::endl;

// This line is okay, even with the same line in external_variables.cpp.
#include "header_with_static.h"

// ReSharper disable once CppUseInternalLinkage
int global = 10;

// ReSharper disable once CppUseInternalLinkage
void duplicate_function() {}

// Even though this wasn't initialized here, we can use it in main below, because we initialize it in
// external_variables.cpp. Without extern, you get a multiple definitions linker error. With static, it compiles and
// runs, but the value is 0 rather than 5, since it is default initialized here locally.
extern int externally_linked;

// You will get a linker error if you attempt to use this (see in main() below). It's defined as static in
// external_variables.cpp, and therefore not visible from here.
extern int externally_linked_to_static;

static int s_my_static;

// ReSharper disable once CppUseInternalLinkage
void static_function() {}


// ReSharper disable once CppUseInternalLinkage
class Entity {

public:

  static int m_static;
  int m_non_static;

  // ReSharper disable once CppPossiblyUninitializedMember
  Entity() { m_static++; }

  static void print_static() { cout << "m_static = " << m_static << endl; }
  [[maybe_unused]] void print_non_static() const { cout << m_non_static << " " << m_static << endl; }

  // Static methods can't access non-static variables. Those variables are tied to 
  // a specific instance, but static methods aren't parameterized by instances. 
  // Declaring a method as static is almost equivalent to writing it in global scope.
  //static void bad_print_static() { cout << m_non_static << endl; } // compile error
};

// Have to explicitly declare static variables within classes/structs. Otherwise,
// you'll get an unresolved external linker error.
int Entity::m_static = 0;

// Show what happens with static in a local scope.
// ReSharper disable once CppUseInternalLinkage
void function_with_local_static() {
  static int n_calls = 0; // only initialized the first time
  cout << "Number of calls to function_with_local_static() = " << ++n_calls << endl;
}

int main() {

  // Show what happens with static outside of classes.
  cout << "s_variable_in_header = " << s_variable_in_header << endl;
  cout << "global = " << global << endl; 
  cout << "externally_linked = " << externally_linked << endl;
  // cout << externally_linked_to_static << endl;  // uncommenting this leads to a undefined reference linker error
  cout << "s_my_static = " << s_my_static << endl << endl; // prints 0

  // Show what happens with static withing of classes/structs.
  Entity::print_static(); // 0
  Entity e1;
  e1.print_static(); // 1
  Entity e2;
  e2.print_static(); // 2

  // Careful! Here, it looks like you're assigning to an instance, but you are 
  // actually assigning to variables within the class/struct itself.
  e2.m_static = 5; // equivalent to Entity::m_static = 5;
  e2.print_static(); // 5
  e1.print_static(); // 5!
  Entity::print_static(); // 5

  // Show what happens with static in a local scope.
  cout << endl;
  function_with_local_static();
  function_with_local_static();
  function_with_local_static();
}
