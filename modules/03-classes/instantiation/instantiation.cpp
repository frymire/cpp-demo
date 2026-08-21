
// Demonstrate different ways to instantiate class instances.
// See here: https://www.youtube.com/watch?v=Rr1NX1lH3oE&list=WL&index=17&t=8s

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

class Entity {
  string m_name;
  int m_age;
public:
  Entity(): m_name("Unknown") {}
  Entity(const string& name): m_name(name), m_age(-1) {}
  explicit Entity(int age): m_name("Unknown"), m_age(age) {}
  void Print() const { cout << m_name << endl; }
};

void GlobalPrintEntity(const Entity& entity) { entity.Print(); }

int main() {

  Entity e1; // don't say e1() for default constructor.
  e1.Print();
  GlobalPrintEntity(e1);

  // To pass a parameter...
  Entity e2("Mark");
  e2.Print();

  // Equivalently...
  Entity e3 = Entity("Kurt"); // without "new" still instantiates on the stack
  e3.Print();

  // Also equivalently...
  Entity e4 = {"Anna"};
  e4.Print();

  // You can also implicitly convert from a string, both for the constructor, and for passing
  // parameters to functions. Probably inadvisable, due to readabiliy concerns.
  Entity e5 = string("Edward");
  e5.Print();
  GlobalPrintEntity(string("Magoo"));
  GlobalPrintEntity(Entity("Gunny")); // also works, char* to string for Entity

  // You can't do transitive implicit conversion, for instance, from char* to string to Entity.
  //GlobalPrintEntity("Mango"); // compile error

  // You can't use implicit conversion for constructors marked "explicit".
  //Entity e6 = 22; // compile error
  Entity e6(22); // fine, explicitly uses (int age) constructor
  e6.Print();

  // You could explicitly cast an int to an Entity. Probably inadvisable.
  Entity e7 = (Entity) 22; // but better to just say "Entity e7 = Entity(22);"
  e7.Print();

  // To instantiate on the heap, use "new", which returns a pointer to the Entity.
  Entity* e8 = new Entity("Mango");
  e8->Print();
  delete e8; // call delete to free the heap-allocated memory
}
