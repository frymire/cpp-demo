
// Demonstrate different ways to instantiate class instances.
// See here: https://www.youtube.com/watch?v=Rr1NX1lH3oE&list=WL&index=17&t=8s

// ReSharper disable CppNonExplicitConvertingConstructor

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

namespace {

  class Entity {
    string m_name;
    int m_age;
  public:
    // ReSharper disable once CppPossiblyUninitializedMember
    Entity(): m_name("Unknown") {}
    Entity(const string& name): m_name(name), m_age(-1) {}
    explicit Entity(int age): m_name("Unknown"), m_age(age) {}
    void print() const { cout << m_name << endl; }
  };

void print_entity(const Entity& entity) { entity.print(); }

}

int main() {

  const Entity e1; // don't say e1() for default constructor.
  e1.print();
  print_entity(e1);

  // To pass a parameter...
  const Entity e2("Mark");
  e2.print();

  // Equivalently...
  const Entity e3 = Entity("Kurt"); // without "new" still instantiates on the stack
  e3.print();

  // Also equivalently...
  const Entity e4 = {"Anna"};
  e4.print();

  // You can also implicitly convert from a string, both for the constructor, and for passing
  // parameters to functions. Probably inadvisable, due to readability concerns.
  const Entity e5 = string("Edward");
  e5.print();
  print_entity(string("Magoo"));
  print_entity(Entity("Gunny")); // also works, char* to string for Entity

  // You can't do transitive implicit conversion, for instance, from char* to string to Entity.
  //GlobalPrintEntity("Mango"); // compile error

  // You can't use implicit conversion for constructors marked "explicit".
  // Entity e6 = 22; // compile error
  const Entity e6(22); // fine, explicitly uses (int age) constructor
  e6.print();

  // You could explicitly cast an int to an Entity. Probably inadvisable.
  const Entity e7 = static_cast<Entity>(22); // but better to just say "Entity e7 = Entity(22);"
  e7.print();

  // To instantiate on the heap, use "new", which returns a pointer to the Entity.
  Entity* e8 = new Entity("Mango");
  e8->print();
  delete e8; // call delete to free the heap-allocated memory
}
