
// Demo unions, which provide a formal type punning capability in C++.
// See here: https://www.youtube.com/watch?v=6uqU9Y578n4&list=WL&index=24

#include <iostream>
using std::cout;
using std::endl;

struct Vector2D {
  float x, y; 
  void print() { cout << x << " " << y << endl; }
};

// Can treat the memory underlying a union as being of any declared type.
struct Vector4D {
  union {
    struct { float x, y, z, w; };
    struct { Vector2D a, b; };
  };
};

int main() {

  // Instantiate a Vector4, but access it as a pair of Vector2s.
  Vector4D v4 = {1.0f, 2.0f, 3.0f, 4.0f};
  v4.a.print();
  v4.b.print();
  cout << endl;

  // Update a value while treating it as a Vector4.
  v4.z = 500.0f;
  v4.a.print();
  v4.b.print();
}
