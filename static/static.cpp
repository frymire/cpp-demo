
// Demonstrate what happens when you declare global variables and functions as static.
// See here: https://www.youtube.com/watch?v=f3FVU-iwNuA&list=WL&index=64
// And here: https://www.youtube.com/watch?v=V-BFlMrBtqQ&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=22

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
void FunctionWithStatic() {}


struct Entity {

  static int m_static;
  int m_not_static;

public:

  static void PrintStatic() { cout << m_static << endl; }
  void PrintNonStatic() { cout << m_not_static << " " << m_static << endl; }

  // Static methods can't access not-static variables. It's basically equivalent 
  // to writing a method outside of the struct.
  //static void BadPrintStatic() { cout << m_not_static << endl; } // compile error
};

// Have to explicitly declare static variables within classes/structs.
int Entity::m_static;

int main() {

  // Show what happens with static outside of classes.
  cout << "s_variable_in_header = " << s_variable_in_header << endl;
  cout << "global = " << global << endl; 
  cout << "externally_linked = " << externally_linked << endl;
  //cout << externally_linked_to_static << endl;
  cout << "s_my_static = " << s_my_static << endl << endl; // prints 0


  // For static variables within structs/classes, it can look like you're assigning
  // to an instance, but really, you are assigning to variables at the class level.
    
  Entity e1;
  e1.m_static = 2; // Bad style! This is equivalent to Entity::m_static = 2;
  e1.PrintStatic(); // 2

  Entity e2;
  e2.m_static = 5; // Bad style! This is equivalent to Entity::m_static = 5;
  e2.PrintStatic(); // 5

  e1.PrintStatic(); // now 5
}
