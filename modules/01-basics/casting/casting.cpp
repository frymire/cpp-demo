
// Demonstrate C++-style casts.
// See here: https://www.youtube.com/watch?v=pWZS1MtxI-A&list=WL&index=26
// And here: https://www.youtube.com/watch?v=CiHfz6pTolQ&list=WL&index=25

#include <iostream>
using std::cout;
using std::endl;

class Entity {
public:
  // Can only use dynamic_cast on a class instance that is explicitly polymorphic. 
  // Achieve that by having any virtual function.
  virtual void Dummy() {}
};

class Player: public Entity {};
class Enemy: public Entity {};

bool IsPlayer(Entity* e) {

  // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points to an 
  // instance of a particular derived type. If so, return a valid pointer, otherwise nullptr.
  Player* p = dynamic_cast<Player*>(e);
  return (p != nullptr);

  // This will incur an additional run-time cost, because it must build and use type information. 
  // You can turn it off in Visual Studio with the following setting, but dynamic_cast would then
  // give undefined behavior.
  //   Project Properties -> C/C++ -> Language -> Enable Run-Time Type Information: No
}

int main() {

  double value = 5.25;
  double a = (int) value + 5.5; // C-style cast
  cout << a << endl; // 10.5

  // C++-style casts provide syntax to make cast styles more explicit. Makes it easy 
  // to search for casts by type. Four types: static, reinterpret, const, dynamic.
 
  // static: verify that the conversion is possible at compile time
  double s = static_cast<int>(value) + 5.5; // c++-style cast
  cout << s << endl;
  //double s2 = static_cast<Entity>(value); // compile error, can't cast a double as an Entity.

  // reinterpret: perform type punning to treat a memory block as a different type
  Enemy* s2 = reinterpret_cast<Enemy*>(&value);

  // TODO: const: add or remove const-ness

  // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points
  // to an instance of a particular derived type.
  Entity* e = new Player();
  cout << IsPlayer(e) << endl;
  e = new Enemy();
  cout << IsPlayer(e) << endl;
}
