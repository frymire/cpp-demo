// Exercises to help understand lvalues versus rvalues.
// See here: https://www.youtube.com/watch?v=fbYknr-HPYE

// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppPassValueParameterByConstReference

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;


namespace {

  // Here, x can be an lvalue or rvalue.
  void set_value_by_value(int x) { cout << x << endl; }

  // Here, x can only be an lvalue.
  void set_value_by_reference(int& x) { cout << x << endl; }

  // Here, x can be an lvalue or rvalue.
  void set_value_by_const_reference(const int& x) { cout << x << endl; }

  // Returning a reference to an int makes this function return an lvalue.
  int& get_value() {
    static int x = 10;
    return x;
  }

  // Repeat with strings.
  void print_name_by_value(string name) { cout << "either = " << name << endl; }
  void print_name_by_reference(string& name) { cout << "lvalue = " << name << endl; }
  void print_name_by_const_reference(const string& name) { cout << "either = " << name << endl; }

  // To require a rvalue reference, use &&. Facilitates optimizations.
  void print_name_by_r_value(const string&& name) { cout << "rvalue = " << name << endl; }

} // namespace


int main() {

  int i = 10;
  //int& j = 10; // compile error, can't have an lvalue reference of an rvalue
  [[maybe_unused]] const int& j = 10; // okay to have a *const* lvalue reference of an rvalue

  cout << "Pass by value...\n";
  set_value_by_value(i); // x is an lvalue
  set_value_by_value(20); // x is an rvalue

  cout << "\nPass by reference...\n";
  set_value_by_reference(i); // x is an lvalue
  //set_value_by_reference(20); // compile error, can't pass a reference to an rvalue

  cout << "\nPass by const reference...\n";
  set_value_by_const_reference(i);
  set_value_by_const_reference(20);

  // Repeat with strings.

  const string first_name = "Mark";
  const string last_name = "Frymire";
  string full_name = first_name + last_name;

  cout << "Pass by value...\n";
  print_name_by_value(full_name); // passing lvalue
  print_name_by_value(first_name + last_name); // passing rvalue

  cout << "\nPass by reference...\n";
  print_name_by_reference(full_name); // passing lvalue
  //print_name_by_reference(first_name + last_name); // compile error, can't pass rvalue by reference

  cout << "\nPass by const reference...\n";
  print_name_by_const_reference(full_name); // okay to pass rvalue by const reference
  print_name_by_const_reference(first_name + last_name); // okay to pass rvalue by const reference

  cout << "\nPass by rvalue reference...\n";
  // print_name_by_r_value(full_name); // compile error, must pass rvalue reference
  print_name_by_r_value(first_name + last_name); // okay, passing rvalue reference

  // Now do tricks with function returns...

  cout << "\nReturn by rvalue...\n";
  cout << get_value() << endl;

  cout << "\nReturn by lvalue...\n";
  get_value() = 5;  // the method returns the reference to the internal static which we then set
  cout << get_value() << endl << endl;
}
