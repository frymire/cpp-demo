
// Demo miscellaneous features with strings.
// See here: https://www.youtube.com/watch?v=S7oVXMzTo4w&list=WL&index=20
// And here: https://www.youtube.com/watch?v=ZO68JEgoPeg&list=WL&index=20

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using namespace std::string_literals; // R"(...)"

#include <string_view>
using std::string_view;

// Override new so that we can see memory allocations for demo purposes.
static uint32_t s_AllocCount = 0;
void* operator new(size_t size) {
  cout << "Allocating " << size << " bytes, " << ++s_AllocCount << " allocations total.\n";
  return malloc(size);
}

void PrintName(const string& name) { cout << name << endl; }

void PrintNameStringView(string_view name) { cout << name << endl; }

int main() {

  // Specify a multi-line string with R"({your text})".
  const char* multi_line_string = 
R"(Line1
Line2
Line3
Line4)";
  cout << multi_line_string << endl;

  
  // Small string optimization: For 15 characters or less, std::string allocates on the stack
  // Run in release mode, since debug allocates 16 bytes for its purposes.

  cout << "\nTest memory allocations when calling string functions...\n";

  cout << "\nMake a string less than 16 characters long...\n";
  string short_name = "Mark Frymire..."; // stack
  cout << short_name << endl;

  PrintName("Mark Frymire..."); // stack

  cout << "\nMake a string at least 16 characters long...\n";
  string long_name = "Mark Frymire...."; // heap
  cout << long_name << endl;
 
  PrintName("Mark Frymire...."); // heap

  cout << "\nExtract substrings...\n";
  string full_name = "Mark Edward Frymire"; // heap
  cout << full_name << endl;
  cout << full_name.substr(1, 15) << endl; // stack
  cout << full_name.substr(1, 16) << endl; // heap

  cout << "\nView substrings without memory allocations...\n"; // C++17
  cout << string_view(full_name.c_str() + 1, 15) << endl; // + 1 advances the start 1 character
  cout << string_view(full_name.c_str() + 1, 16) << endl;

  cout << "\nAvoid even the original heap allocation using views into a char*...\n";
  const char* char_star_name = "Mark Edward Frymire"; // stack
  cout << string_view(char_star_name + 1, 15) << endl;
  cout << string_view(char_star_name + 1, 16) << endl;

  cout << "\nAvoid heap allocation when calling functions with string_view parameter...\n";
  PrintNameStringView("Mark Frymire....");
}
