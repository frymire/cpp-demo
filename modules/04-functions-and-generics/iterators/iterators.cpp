
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

  vector values = { 5, 3, 4, 1, 2 };

  // Normally, you just do this...
  for (const int v : values) { cout << v << endl; }

  // Or more explicitly, in case you need to fiddle with the iterator along the way...
  cout << endl;
  // ReSharper disable once CppUseAuto
  for (vector<int>::iterator it = values.begin(); it != values.end(); ++it) {  // NOLINT(*-loop-convert, *-use-auto)
    cout << *it << endl;
  }

  // Do it again with a map.
  unordered_map<string, int> map;
  map["Anna"] = 37;
  map["Edward"] = 2;
  map["Mark"] = 45;

  // Print the map values with verbose syntax...
  cout << endl;
  using name_to_age_it = unordered_map<string, int>::const_iterator;
  for (name_to_age_it it = map.begin(); it != map.end(); ++it) {  // NOLINT(*-loop-convert, *-use-auto)
    cout << it->first << " " << it->second << endl;
  }

  // Print the map values with clean, but obscure syntax...
  cout << endl;
  // ReSharper disable once CppUseStructuredBinding
  for (const auto& kv: map) { cout << kv.first << " " << kv.second << endl; }

  // With C++17, you can use structured bindings...
  cout << endl;
  for (const auto& [key, value]: map) { cout << key << " " << value << endl; }
}
