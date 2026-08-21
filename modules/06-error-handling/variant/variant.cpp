
// Demonstrate variant (C++17).
// See here: https://www.youtube.com/watch?v=qCc_Vqg3hJk&list=WL&index=19

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <variant>
using std::variant;
using std::get; // variant version of get()
using std::get_if;

int main() {

  // Declare data to be a string or an int. This might make sense, for instance, where 
  // a successful operation returns a string, while failure returns an error code.
  variant<string, int> data; 

  // A union lets you treat the same block of memory as one type or the other, so its
  // size is max(sizeof(string), sizeof(int)). Variants, on the other hand, store both
  // possible types, so its size is sizeof(string) + sizeof(int).
  cout << "size = " << sizeof(string) << endl;
  cout << "size = " << sizeof(int) << endl;
  cout << "size = " << sizeof(data) << endl << endl;

  // Treat it as a string...
  data = "Mark";
  cout << get<string>(data) << endl;

  // Treat it as an int...
  data = 5;
  cout << get<int>(data) << endl;

  // You get a bad_variant_access run-time error if you access it as the wrong type.
  //cout << get<string>(data) << endl; // run-time error

  // Get the index of the type currently stored by data.
  cout << data.index() << endl; // 1
  data = "Kurt";
  cout << data.index() << endl; // 0

  // Use get_if as a clean way to be sure the type is what you expect. Returns either
  // nullptr or a valid pointer to the requested type.
  string* data_value1 = get_if<string>(&data);
  if (data_value1) { cout << "It's a string: " << *data_value1 << endl; }

  // Use get_if again, but this time put the assignment within the if condition.
  data = 10;
  if (int* data_value2 = get_if<int>(&data)) {
    cout << "It's an int: " << *data_value2 << endl;
  }
}
