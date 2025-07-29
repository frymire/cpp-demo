
// Demo pairs, tuples, and structured bindings.
// See here: https://www.youtube.com/watch?v=eUsTO5BO3WI&list=WL&index=24

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>
using std::pair;
using std::make_pair;

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;

pair<int, char> GetPair() {
  return make_pair(1, 'a'); // instead of pair<int, char>(1, 'a')
}

tuple<int, char, double> GetTuple() {
  return make_tuple(2, 'b', 10.0); // instead of tuple<int, char, double>(2, 'b', 10.0)
}

// It's nicer to use a struct, so that you can see the member names.
struct StructReturn {
  string name;
  int year;
};

StructReturn GetStruct() {
  //return StructReturn({"Mark", 45}); // long way
  return {"Mark", 1975}; // cleaner
}

int main() {

  pair<int, char> x = GetPair();
  cout << x.first << " " << x.second << endl;

  // Use std:get() to extract elements from tuples. The template parameter provides the index. (Awkward.)
  tuple<int, char, double> y = GetTuple();
  cout << get<0>(y) << " " << get<1>(y) << " " << get<2>(y) << endl;

  // You can use a structured binding to declare multiple return values as local variables (C++17).
  auto[age, grade, cost] = GetTuple();
  cout << age << " " << grade << " " << cost << endl;

  // Using a struct lets you see the member names. Useful if you will use the result repeatedly.
  StructReturn z = GetStruct();
  cout << z.name << " " << z.year << endl;
}
