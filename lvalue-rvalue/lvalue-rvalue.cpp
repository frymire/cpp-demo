
// Exercises to help understand lvalues versus rvalues.
// See here: https://www.youtube.com/watch?v=fbYknr-HPYE

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// Here, x can be an lvalue or rvalue.
void SetValuePassByValue(int x) { cout << x << endl; }

// Here, x can only be an lvalue.
void SetValuePassByReference(int& x) { cout << x << endl; }

// Here, x can be an lvalue or rvalue.
void SetValuePassByConstReference(const int& x) { cout << x << endl; }

// Returning a reference to an int makes this function return an lvalue.
int& GetValue() {
  static int x = 10;
  return x;
}

// Repeat with strings.
void PrintNamePassByValue(string name) { cout << "either = " << name << endl; }
void PrintNamePassByReference(string& name) { cout << "lvalue = " << name << endl;  }
void PrintNamePassByConstReference(const string& name) { cout << "either = " <<name << endl; }

// To require a rvalue reference, use &&. Facilitates optimizations.
void PrintNamePassByRValueReference(const string&& name) { cout << "rvalue = " << name << endl; }

int main() {

  int i = 10;
  //int& j = 10; // compile error, can't have an lvalue reference of an rvalue
  const int& j = 10; // okay to have a *const* lvalue reference of an rvalue

  cout << "Pass by value...\n";
  SetValuePassByValue(i); // x is an lvalue;
  SetValuePassByValue(20); // x is an rvalue;

  cout << "\nPass by reference...\n";
  SetValuePassByReference(i); // x is an lvalue;
  //SetValuePassByReference(20); // compile error, can't pass a reference to an rvalue
  
  cout << "\nPass by const reference...\n";
  SetValuePassByConstReference(i);
  SetValuePassByConstReference(20);


  // Repeat with strings.

  string first_name = "Mark";
  string last_name = "Frymire";
  string full_name = first_name + last_name;

  cout << "Pass by value...\n";
  PrintNamePassByValue(full_name); // passing lvalue
  PrintNamePassByValue(first_name + last_name); // passing rvalue

  cout << "\nPass by reference...\n";
  PrintNamePassByReference(full_name); // passing lvalue
  //PrintNamePassByReference(first_name + last_name); // compile error, can't pass rvalue by reference
  
  cout << "\nPass by const reference...\n";
  PrintNamePassByConstReference(full_name); // okay to pass rvalue by const reference
  PrintNamePassByConstReference(first_name + last_name); // okay to pass rvalue by const reference
  
  cout << "\nPass by rvalue reference...\n";
  //PrintNamePassByRValueReference(full_name); // compiler error, must pass rvalue reference
  PrintNamePassByRValueReference(first_name + last_name); // okay, passing rvalue reference


  // Now do tricks with function returns...

  cout << "\nReturn by rvalue...\n";
  cout << GetValue() << endl;

  cout << "\nReturn by lvalue...\n";
  GetValue() = 5;
  cout << GetValue() << endl << endl;
}
