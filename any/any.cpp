
// Demo std::any (C++17), which is similar to variant, but not really type safe. Not recommended.
// See here: https://www.youtube.com/watch?v=7nPrUBNGRAk&list=WL&index=16

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <any>
using std::any;
using std::any_cast;

// Overload the new operator to track memory allocations for demo purposes.
void* operator new(size_t size) { 
  cout << "Allocating " << size << " bytes.\n";
  return malloc(size); 
}

// For small types (up to around 32 bytes, processor dependent), std::any stores the underlying 
// data as a variant. For large types, it uses void* to dynamically allocate memory. To show
// this, define a struct that is bigger than the small type limit.
struct BigStruct { long long v[10]; };

int main() {

  cout << "Declare an any-typed variable (no need to list possible types, as with variant)...\n";
  any data;

  cout << "\nSet it to 2...\n";
  data = 2;

  cout << "\nSet it to string(\"Mark\")...\n";
  data = string("Mark"); // allocates memory 3 times, not clear why

  cout << "\nUse any_cast to get the data as a string and copy it to a new string...\n";
  string copied = any_cast<string>(data);
  cout << copied << endl;

  cout << "\nCast as a string reference, without copies...\n";
  string& referenced = any_cast<string&>(data);
  cout << referenced << endl;

  cout << "\nSet it as a TwoString instance to force dynamic memory allocation...\n";
  data = BigStruct{1ll, 2ll, 3ll, 4ll, 5ll, 6ll, 7ll, 8ll, 9ll, 10ll}; 

  cout << "\nCast and assign it, without copies...\n";
  BigStruct& my_big_struct = any_cast<BigStruct&>(data);
  for (int i = 0; i < 10; i++) { cout << my_big_struct.v[i] << " "; }
  cout << endl;
}
