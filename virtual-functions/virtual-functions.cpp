
// Demo virtual functions and interfaces
// See here: https://www.youtube.com/watch?v=oIV2KchSyGQ
// And here: https://www.youtube.com/watch?v=UWAdd13EfM8&list=WL&index=67&t=18s
// And here: https://www.youtube.com/watch?v=jELbKhGkEi0

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// Define an interface comprised only of virtual functions (like a Scala trait).
class Printable {
public:
  virtual string GetClassName() = 0;
};

void PrintClassName(Printable* obj) { cout << "Class name is " << obj->GetClassName() << endl; }

class Entity: public Printable {
public:
  Entity() { cout << "Constructed an Entity.\n"; }

  // Key point here. Suppose you instantiate an Entity polymorphically by assigning an Entity* 
  // to an instance of a derived class (e.g. Player below). Without adding the "virtual" keyword
  // to the base class destructor, the destructor of the derived class would not be called,
  // probably resulting in a memory leak. Unlike virtual functions on normal functions, with
  // destructors, C++ calls *both* the base class and the derived class destructor, rather than
  // just overriding the base class function.
  virtual ~Entity() { cout << "Destroyed an Entity.\n"; } // try without "virtual"
  
  virtual void SayHi() { cout << "Entity says Hi.\n"; } // virtual
  void SayBye() { cout << "Entity says Bye.\n"; } // not virtual
  virtual string GetClassName() override { return "Entity"; }
  virtual string GetName() = 0; // pure virtual
};

class Player: public Entity {

private:
  string m_Name;

public:

  Player(const string& name): m_Name(name) { cout << "Constructed a Player.\n"; }
  ~Player() { cout << "Destroyed a Player.\n"; }

  // The override keyword verifies that you're overriding a base class function.
  //  You can get away without it, but adding it is good practice.
  //void SayHii() override { cout << "Hey...\n"; } // compile error, doesn't override anything in Entity
  void SayHi() override { cout << "Player says Hey...\n"; } 

  // The base class function SayBye() was not declared virtual, so you can't override it here.
  // Declaring it here with the same signature might lead to surprising behavior if you instantiate Player
  // as an instance of type Entity, since SayBye will use Entity::SayBye in that case.
  //void SayBye() override { cout << "Player says Bye bye!\n"; }
  void SayBye() { cout << "Player says Bye bye!\n"; }

  virtual string GetClassName() override { return "Player"; }

  // By providing this definition of the pure virtual function in Entity, you can now instantiate Players.
  string GetName() override { return m_Name; }
};

int main() {

  // You can't instantiate Entity directly, because GetName() is pure virtual.
  //Entity entity1(); // compile error

  // Instantiate a Player polymorphically as an Entity.
  Entity* e = new Player("Mark");
  e->SayHi();
  e->SayBye(); // uses Entity::SayBye(), not Player::SayBye()!
  PrintClassName(e);
  cout << e->GetName() << endl;
  cout << "Deleting e...\n";
  delete e;

  cout << endl;
  Player* p = new Player("Kurt");
  p->SayBye(); // uses Player::SayBye()
  cout << "Deleting p...\n";
  delete p;
}
