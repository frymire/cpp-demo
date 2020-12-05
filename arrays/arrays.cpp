
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <functional> // lambda functions
//#include <algorithm> // find_if

class Vertex {

  int x, y, z;

public:

  Vertex(int x, int y, int z): x(x), y(y), z(z) {}

  // Copy constructor
  Vertex(const Vertex& vertex): x(vertex.x), y(vertex.y), z(vertex.z) {
    cout << "Copied a Vertex\n";
  }
};

int main() {

  int n[3] = {1, 2, 3};
  for (int i = 0; i < 3; i++) cout << n[i];
  cout << endl;

  vector<int> values = {1, 5, 4, 2, 3};
  std::function<void(int)> lambda = [=](int x) { cout << "Value = " << x << endl;  };
  for (int value: values) lambda(value); 

  // Filter like this...
  //auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
  //cout << *it << endl;


  cout << "\n\nDemonstrate unexpected copying due to dynamic vector resizing...\n";
  // See: https://www.youtube.com/watch?v=HcESuwmlHEY&list=WL&index=72
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

  cout << "\nDo it again, but use emplace_back() rather than push_back()...\n";
  vector<Vertex> best_vertices;
  best_vertices.reserve(3);
  best_vertices.emplace_back(1, 2, 3); // Only pass the parameter list for the Vertex constructor.
  best_vertices.emplace_back(4, 5, 6);
  best_vertices.emplace_back(7, 8, 9); // no copies!

  return 0;
}
