
// This code is shows why you really should use explicit scoped calls such as std::cout, 
// rather than saying "using namespace std" or *even* "using std::cout".
// See here: https://www.youtube.com/watch?v=4NYC-VU-svE&list=WL&index=86

#include <iostream>
#include <string> // provides a conversion from const std::string to const char*

namespace top_level_namespace { namespace lower_level_namespace {
  void print() { std::cout << "Hey, how's it going?\n"; }
} }

namespace printer {
  void print(const std::string& name) { std::cout << name << " is awesome!\n"; }
}

namespace malicious_printer {
  void print(const char* name) { std::cout << name << " is terrible!\n"; }
}

void main() {

  // First, let's just demonstrate a namespace alias, which is nice for long nested namespaces.
  namespace n2 = top_level_namespace::lower_level_namespace;
  n2::print();

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
