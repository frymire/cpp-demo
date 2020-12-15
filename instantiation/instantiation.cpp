
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

class Entity {
  string m_name;
public:
  Entity(): m_name("Unknown") {}
  Entity(const string& name): m_name(name) {}
  void Print() { cout << m_name << endl; }
};

int main() {

  Entity e1; // don't say e1() for default constructor.
  e1.Print();

  // To pass a parameter...
  Entity e2("Mark");
  e2.Print();

  // Equivalently...
  Entity e3 = Entity("Kurt"); // without "new" still instantiates on the stack
  e3.Print();

  // Also equivalently...
  Entity e4 = {"Edward"};
  e4.Print();

  // To instantiate on the heap, use "new", which returns a pointer to the Entity.
  Entity* e5 = new Entity("Anna");
  e5->Print();
  delete e5; // call delete to free the heap-allocated memory
}
