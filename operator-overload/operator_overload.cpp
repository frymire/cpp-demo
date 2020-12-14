
#include <iostream>
using std::cout;
using std::endl;

class Vertex {

  int x, y, z;

public:

  Vertex(int x, int y, int z): x(x), y(y), z(z) {}

  // Declare ostream as a friend, so it can access Vertex private members.
  friend std::ostream& operator<<(std::ostream& stream, const Vertex& v) { 
    stream << v.x << " " << v.y << " " << v.z << endl; 
    return stream; 
  }
};

int main() {
  Vertex v(1, 2, 3);
  cout << v << endl;
}
