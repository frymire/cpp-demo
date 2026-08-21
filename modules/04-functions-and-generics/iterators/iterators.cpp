
// Demo iterators.
// See here: https://www.youtube.com/watch?v=SgcHcbQ0RCQ

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

int main() {

  vector<int> values = { 5, 3, 4, 1, 2 };

  // Normally, you just do this...
  for (int value : values) { cout << value << endl; }

  // Or more explicitly, in case you need to fiddle with the iterator along the way...
  cout << endl;
  for (vector<int>::iterator it = values.begin(); it != values.end(); it++) { cout << *it << endl; }

  // Do it again with a map.
  unordered_map<string, int> map;
  map["Anna"] = 37;
  map["Edward"] = 2;
  map["Mark"] = 45;

  // Print the map values with verbose syntax...
  using name_to_age_it = unordered_map<string, int>::const_iterator;
  for (name_to_age_it it = map.begin(); it != map.end(); it++) {
    cout << it->first << " " << it->second << endl;
  }

  // Print the map values with clean, but obscure syntax...
  cout << endl;
  for (auto kv: map) { cout << kv.first << " " << kv.second << endl; }

  // With C++17, you can use structured bindings...
  cout << endl;
  for (auto [key, value]: map) { cout << key << " " << value << endl; }
}
