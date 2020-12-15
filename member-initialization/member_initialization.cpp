
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

class Example {
public:
  Example() { cout << "Created default Example.\n"; }
  Example(int x) { cout << "Created Example with " << x << ".\n"; }
};

class Entity {

  std::string m_name;
  Example m_example;

public:

  // Without member initialization, a default Example instance (i.e. Example()) is first constructed 
  // from the private member declaration above. Then a second one is created with the Example(8) call
  // within the body of the constructor, and the first is lost when m_example is assigned.
  Entity() {
    m_name = string("Unknown");
    m_example = Example(8);
  }

  // With member initialization, there is no default Example() instantiation; m_name uses the string 
  // copy constructor and m_example uses its (int x) constructor. Note that having name as a variable
  // is just so that we can have two different constructors. The key is what happens with m_example.
  Entity(const string& name): m_name(name), m_example(8) {}

  // NOTE: Initialize members in the same order as they were declared to avoid weird errors.
};

int main() {

  cout << "Without member initialization...\n";
  Entity without; // be careful not to instantiate as "instance0()"

  cout << "\nWith member initialization...\n";
  Entity with("Mark");
}
