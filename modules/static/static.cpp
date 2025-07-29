
// Demonstrate what happens when you declare variables and functions as static.
// See here: https://www.youtube.com/watch?v=f3FVU-iwNuA&list=WL&index=64
// And here: https://www.youtube.com/watch?v=V-BFlMrBtqQ&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=22
// And here: https://www.youtube.com/watch?v=f7mtWD9GdJ4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=23&t=1s

#include <iostream>
using std::cout;
using std::endl;

// This line is okay, even with the same line in external_variables.cpp.
#include "header_with_static.h"

int global = 10;
void DuplicateFunction() {}

extern int externally_linked;

//extern int externally_linked_to_static;

static int s_my_static;
void StaticFunction() {}

class Entity {

public:

  static int m_static;
  int m_non_static;

  Entity() { m_static++; }

  static void PrintStatic() { cout << "m_static = " << m_static << endl; }
  void PrintNonStatic() { cout << m_non_static << " " << m_static << endl; }

  // Static methods can't access non-static variables. Those variables are tied to 
  // a specific instance, but static methods aren't parameterized by instances. 
  // Declaring a method as static is almost equivalent to writing it in global scope.
  //static void BadPrintStatic() { cout << m_non_static << endl; } // compile error
};

// Have to explicitly declare static variables within classes/structs. Otherwise,
// you'll get an unresolved external linker error.
int Entity::m_static = 0;

// Show what happens with static in a local scope.
void FunctionWithLocalStatic() {
  static int nCalls = 0; // only initialized the first time
  cout << "Number of calls to FunctionWithLocalStatic() = " << ++nCalls << endl;
}

int main() {

  // Show what happens with static outside of classes.
  cout << "s_variable_in_header = " << s_variable_in_header << endl;
  cout << "global = " << global << endl; 
  cout << "externally_linked = " << externally_linked << endl;
  //cout << externally_linked_to_static << endl;
  cout << "s_my_static = " << s_my_static << endl << endl; // prints 0

  // Show what happens with static withing of classes/structs.
  Entity::PrintStatic(); // 0
  Entity e1;
  e1.PrintStatic(); // 1
  Entity e2;
  e2.PrintStatic(); // 2

  // Careful! Here, it looks like you're assigning to an instance, but you are 
  // actually assigning to variables within the class/struct itself.
  e2.m_static = 5; // equivalent to Entity::m_static = 5;
  e2.PrintStatic(); // 5
  e1.PrintStatic(); // 5!
  Entity::PrintStatic(); // 5

  // Show what happens with static in a local scope.
  cout << endl;
  FunctionWithLocalStatic();
  FunctionWithLocalStatic();
  FunctionWithLocalStatic();
}
