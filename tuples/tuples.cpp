
#include <iostream>
using std::cout;
using std::endl;

#include <utility>
using std::pair;
using std::make_pair;

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;

pair<int, char> GetPair() {
  return make_pair(1, 'a'); // no need to specify template argument tuple<int, char>(1, 'a')
}

tuple<int, char, double> GetTuple() {
  return make_tuple(2, 'b', 10.0); // no need to specify template argument tuple<int, char>(1, 'a')
}

// It's nicer to use a struct, so that you can see the member names.
struct StructReturn {
  char* name;
  int year;
};

StructReturn GetStruct() {

  // Set up a return struct.
  //StructReturn toReturn( {(char*) "Mark", 45} );
  //return toReturn;

  // Or even cleaner...
  return { (char*) "Mark", 1975};
}

int main() {

  pair<int, char> x = GetPair();
  cout << x.first << " " << x.second << endl;

  // Use std:get() to extract elements from tuples. The template parameter provides the index. (Awkward.)
  tuple<int, char, double> y = GetTuple();
  cout << get<0>(y) << " " << get<1>(y) << " " << get<2>(y) << endl;

  // Using a struct lets you see the member names.
  StructReturn z = GetStruct();
  cout << z.name << " " << z.year << endl;
}
