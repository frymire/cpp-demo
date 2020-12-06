
// Demo virtual functions and interfaces
// See here: https://www.youtube.com/watch?v=UWAdd13EfM8&list=WL&index=67&t=18s

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

void Print(Printable* obj) { cout << obj->GetClassName() << endl; }

class Entity: public Printable {
public:
  virtual void SayHi() { cout << "Hi.\n"; } // virtual
  void SayBye() { cout << "Entity says Bye.\n"; } // not virtual
  virtual string GetClassName() override { return "Entity"; }
  virtual string GetName() = 0; // pure virtual
};

class Player: public Entity {

private:
  string m_Name;

public:

  Player(const string& name): m_Name(name) {}

  // The override keyword verifies that you're overriding a base class function.
  //  You can get away without it, but adding it is good practice.
  //void SayHii() override { cout << "Hey...\n"; } // compile error, doesn't override anything in Entity
  void SayHi() override { cout << "Hey...\n"; } 

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

  Entity* e = new Player("Mark");
  e->SayHi();
  e->SayBye(); // uses Entity::SayBye(), not Player::SayBye()!
  Print(e);
  cout << e->GetName() << endl;

  Player* p = new Player("Kurt");
  p->SayBye(); // uses Player::SayBye()
}
