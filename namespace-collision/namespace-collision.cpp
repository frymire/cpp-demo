
// This code is shows why you really should use explicit scoped calls such as std::cout, 
// rather than saying "using namespace std" or *even* "using std::cout".
// See here: https://www.youtube.com/watch?v=4NYC-VU-svE&list=WL&index=86

#include <iostream>
#include <string> // provides a conversion from const std::string to const char*

namespace printer {
  void print(const std::string& name) { std::cout << name << " is awesome!\n"; }
}

namespace malicious_printer {
  void print(const char* name) { std::cout << name << " is terrible!\n"; }
}

void main() {

  // Naming functions with explicit scope works fine, of course.
  printer::print("Mark");
  malicious_printer::print("Mark");

  // Here, we might expect printer:print() to be called, relying on an implicit conversion from 
  // char* to string. However, malicious_printer::print() takes precedence, because it doesn't 
  // need to do any conversion. There's no compiler warning, because both functions are declared 
  // with the same name, but a different signature. The result is a silent run-time error.
  using printer::print;
  using malicious_printer::print;
  print("Mark"); // prints "Mark is terrible!"
}
