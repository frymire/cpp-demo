
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using namespace std::string_literals; // R"(...)"

void main() {

  // You can specify a multi-line string with R"({your text})"
  const char* multi_line_string = 
R"(Line1
Line2
Line3
Line4)";
  cout << multi_line_string << endl;
}