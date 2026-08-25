// Demo pairs, tuples, and structured bindings.
// See here: https://www.youtube.com/watch?v=eUsTO5BO3WI&list=WL&index=24

// ReSharper disable CppUseStructuredBinding
// ReSharper disable CppUseDesignatedInitializers
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <tuple>
using std::tuple;
using std::get;

namespace {

  pair<int, char> get_pair() { return {1, 'a'}; }
  // instead of...
  // return pair(1, 'a');               // C++17 deduces the types
  // return std::make_pair(1, 'a');     // pre-C++17 idiom; still needed to unwrap std::ref
  // return pair<int, char>(1, 'a');    // fully explicit, always works

  tuple<int, char, double> get_tuple() { return {2, 'b', 10.0}; }
  // instead of...
  // return tuple(2, 'b', 10.0);
  // return std::make_tuple(2, 'b', 10.0);
  // return tuple<int, char, double>(2, 'b', 10.0);

  // It can be nicer to use a struct, so the client has the option to see member names.
  struct StructReturn {
    string name;
    int year;
  };

  StructReturn get_struct() { return {"Mark", 1975}; }
  // or...
  // return {.name = "Mark", .year = 1975}; // with designated initializers
  // return StructReturn("Mark", 1975);

}  // namespace

int main() {

  // ReSharper disable once CppUseStructuredBinding
  const pair<int, char> x = get_pair();
  cout << x.first << " " << x.second << endl;

  // Use std:get() to extract elements from tuples. The template parameter provides the index. (Awkward.)
  const tuple<int, char, double> y = get_tuple();
  cout << get<0>(y) << " " << get<1>(y) << " " << get<2>(y) << endl;

  // You can use a structured binding to declare multiple return values as local variables (C++17).
  auto /* tuple<int, char, double> but must use auto */ [age, grade, cost] = get_tuple();
  cout << age << " " << grade << " " << cost << endl;

  // Using a struct lets you see the member names. Useful if you will use the result repeatedly.
  const StructReturn z = get_struct();
  cout << z.name << " " << z.year << endl;
}
