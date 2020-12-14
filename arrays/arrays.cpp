
// Demo arrays and vectors.
// See here: https://www.youtube.com/watch?v=ENDaJi08jCU&list=WL&index=20

#include <iostream>
using std::cout;
using std::endl;

#include <array>
using std::array;

#include <vector>
using std::vector;

#include <functional> // lambda functions
using std::function;

#include <algorithm>
using std::find_if;
using std::copy_if;

#include <iterator>
using std::back_inserter;

class Vertex {
  int x, y, z;
public:
  Vertex(int x, int y, int z): x(x), y(y), z(z) {}  
  Vertex(const Vertex& v): x(v.x), y(v.y), z(v.z) { cout << "Copied a Vertex\n"; }
  void print() { printf("%d %d %d\n", x, y, z); }
};

int main() {

  cout << "\nC-style array on the stack...\n";
  double c_array_stack[3] = {1.1, 2.2, 3.3};
  cout << "address = " << c_array_stack << endl << endl;
  cout << "Bracket notation...\n";
  for (int i = 0; i < 3; i++) { cout << c_array_stack[i] << endl; }
  cout << "\nPointer arithmetic notation...\n";
  for (int i = 0; i < 3; i++) { cout << *(c_array_stack + i) << endl; }
  cout << "On the stack, can get total size in bytes: " << sizeof(c_array_stack) << endl;
  cout << "Recover number of elements: " << sizeof(c_array_stack) / sizeof(double) << endl;

  cout << "\nC-style array on the heap...\n";
  double* c_array_heap = new double[3]{10.1, 20.2, 30.3};
  cout << "address = " << c_array_heap << endl << endl;
  cout << "Bracket notation...\n";
  for (int i = 0; i < 3; i++) { cout << c_array_heap[i] << endl; }
  cout << "\nPointer arithmetic notation...\n";
  for (int i = 0; i < 3; i++) { cout << *(c_array_heap + i) << endl; }
  delete[] c_array_heap;
  cout << "On the heap, can't recover total size.\n";

  cout << "\nStatic array (std::array, C++11) (data stored on the stack)...\n";
  array<int, 3> static_array = {4, 5, 6}; // set the size as a type parameter
  for (auto v: static_array) { cout << v << endl; }
  cout << "Length of static array = " << static_array.size() << endl;
  
  cout << "\nVector (data stored on the heap)...\n";
  vector<int> values = {1, 5, 3, 2, 4};
  function<void(int)> lambda = [=](int x) { cout << x << endl; };
  for (int value: values) lambda(value); 

  cout << "\nFind the first element greater than 2...\n";
  auto gt_2 = [](int value) { return value > 2; };
  vector<int>::iterator first_gt_2 = find_if(begin(values), end(values), gt_2);
  cout << *first_gt_2 << endl;
  
  cout << "\nFilter for all elements greater than 2...\n";
  vector<int> all_gt_2;
  copy_if(values.begin(), values.end(), back_inserter(all_gt_2), gt_2);
  for (auto value: all_gt_2) { cout << value << endl; }

  cout << "\nInitialize class instances directly...\n";
  vector<Vertex> directlyInitialized{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  for (Vertex v : directlyInitialized) { v.print(); }

  // See: https://www.youtube.com/watch?v=HcESuwmlHEY&list=WL&index=72
  cout << "\n\nDemonstrate unexpected copying due to dynamic vector resizing...\n";
  vector<Vertex> naive_vertices;

  // Here, we create a copy of the 123 Vertex when we resize the vector, which is already surprising.
  // The Vertex(1, 2, 3) call creates the instance on the stack, then gets copied into the vector's memory.
  naive_vertices.push_back(Vertex(1, 2, 3)); 

  // Here, we create two more copies, one of 123, and one of 456. Total = 3.
  naive_vertices.push_back(Vertex(4, 5, 6));

  // Here, we create two more for the existing vertices (123 and 456), plus one for 789. Total = 6.
  naive_vertices.push_back(Vertex(7, 8, 9)); 
  
  cout << "\nDo it again, but reserve enough capacity for 3 entries...\n";
  vector<Vertex> better_vertices;
  better_vertices.reserve(3);
  better_vertices.push_back(Vertex(1, 2, 3)); // 1 copy, since the instance is still created on the stack first.
  better_vertices.push_back(Vertex(4, 5, 6)); // 2 copies
  better_vertices.push_back(Vertex(7, 8, 9)); // 3 copies
  cout << "Done pushing back.\n";

  cout << "\nDo it again, but use emplace_back() rather than push_back()...\n";
  vector<Vertex> best_vertices;
  best_vertices.reserve(3); // save room for 3 instances
  best_vertices.emplace_back(1, 2, 3); // Only pass the parameter list for the Vertex constructor.
  best_vertices.emplace_back(4, 5, 6);
  best_vertices.emplace_back(7, 8, 9);
  cout << "Done emplacinging back (no copies!).\n";

  return 0;
}
