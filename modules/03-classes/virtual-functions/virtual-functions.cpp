
// Demo virtual functions and interfaces
// See here: https://www.youtube.com/watch?v=oIV2KchSyGQ
// And here: https://www.youtube.com/watch?v=UWAdd13EfM8&list=WL&index=67&t=18s
// And here: https://www.youtube.com/watch?v=jELbKhGkEi0

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

namespace {

  // Define an interface comprised only of virtual functions (like a Scala trait).
  // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
  class Printable {
  public:
    // virtual ~Printable() = default;  // omitting this for demonstration purposes
    virtual string get_class_name() = 0; // = 0 means it's a pure virtual function, no implementation
  };

  void print_class_name(Printable* obj) { cout << "Class name is " << obj->get_class_name() << endl; }

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

    virtual void say_hi() { cout << "Entity says Hi.\n"; } // virtual

    // ReSharper disable once CppHiddenFunction
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void say_bye() { cout << "Entity says Bye.\n"; } // not virtual

    string get_class_name() override { return "Entity"; }

    virtual string get_name() = 0; // pure virtual
  };

  class Player: public Entity {

  private:
    string m_name;

  public:

    Player(const string& name): m_name(name) { cout << "Constructed a Player.\n"; }

    // The override here is weird, both because ~Player() has a different name than the base class method ~Entity()
    // that it is overriding. It's also weird because destructors in child classes chain with the behavior in parent
    // classes, rather than replace it, as is the behavior in all other functions. Nevertheless, the C++ standard
    // prescribes using override as an exception to the conventional understanding in this case. Leaving override
    // here is good practice, because it would give a compile error if virtual was ever removed from the parent
    // destructor.
    ~Player() override { cout << "Destroyed a Player.\n"; }

    // The override keyword verifies that you're overriding a base class function.
    //  You can get away without it, but adding it is good practice.
    //void SayHii() override { cout << "Hey...\n"; } // compile error, doesn't override anything in Entity
    void say_hi() override { cout << "Player says hi...\n"; }

    // The base class function say_bye() was not declared virtual, so you can't override it here. Declaring it here
    // with the same signature instead hides the base class method. This will lead to surprising behavior if you
    // instantiate Player as an instance of type Entity, since SayBye will use Entity::SayBye in that case.
    // ReSharper disable once CppHidingFunction
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void say_bye() { cout << "Player says bye!\n"; }
    // void say_bye() override { cout << "Player says Bye bye!\n"; }  // compile error, can't override non-virtual

    // The parent Entity class already marked this as virtual, and that holds all the way down the hierarchy, so we
    // don't restate "virtual" here; "override" implies "virtual", you don't put both. If you want to prevent child
    // classes inheriting below this class, instead mark this method as final, as shown below. Similarly, "final"
    // implies "override" so you don't put both. The best practice is to use no marker, or one of "override",
    // "virtual", or "final".
    string get_class_name() override { return "Player"; }
    // string get_class_name() final { return "Player"; }

    // By providing this definition of the pure virtual function in Entity, you can now instantiate Players.
    string get_name() override { return m_name; }
  };
}

int main() {

  // You can't instantiate Entity directly, because get_name() is pure virtual.
  //Entity entity1(); // compile error

  // Instantiate a Player polymorphically as an Entity.
  Entity* e = new Player("Mark");
  e->say_hi();
  e->say_bye(); // uses Entity::SayBye(), not Player::SayBye()!
  cout << "^^^ You would have expected \"Player says Bye.\"\n";
  print_class_name(e);
  cout << e->get_name() << endl;
  cout << "Deleting e...\n";
  delete e;

  cout << endl;
  Player* p = new Player("Kurt");
  p->say_bye(); // uses Player::SayBye()
  cout << "Deleting p...\n";
  delete p;
}
