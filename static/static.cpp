
// Demonstrate what happens when you declare global variables and functions as static.
// See https://www.youtube.com/watch?v=f3FVU-iwNuA&list=WL&index=64

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

int main() {
  cout << "s_variable_in_header = " << s_variable_in_header << endl;
  cout << "global = " << global << endl; 
  cout << "externally_linked = " << externally_linked << endl;
  //cout << externally_linked_to_static << endl;
  cout << "s_my_static = " << s_my_static << endl; // prints 0
}
