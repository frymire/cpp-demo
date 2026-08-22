
// Demonstrate C++-style casts.
// See here: https://www.youtube.com/watch?v=pWZS1MtxI-A&list=WL&index=26
// And here: https://www.youtube.com/watch?v=CiHfz6pTolQ&list=WL&index=25

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::make_unique;
using std::unique_ptr;

namespace {

  class Entity {
  public:
    // You can only use dynamic_cast on a class instance that is explicitly polymorphic. You can achieve that by having
    // any virtual function, such as Dummy() below. Once you add it, though, you also need to add a virtual destructor,
    // or else calling the destructor on Player instance referenced by an Entity* would only run the Entity destructor,
    // even if ~Player() was defined. Adding the virtual destructor, though, is enough to make the class polymorphic,
    // so you no longer need Dummy().
    virtual ~Entity() = default;
    // [[maybe_unused]] virtual void Dummy() {}
  };

  class Player: public Entity {};
  class Enemy: public Entity {};

  // Don't pass the unique pointer here. This function just wants a view, not full ownership.
  void print_entity_is_player(Entity* e) {

    // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points to an
    // instance of a particular derived type. If so, return a valid pointer, otherwise nullptr.
    Player* p = dynamic_cast<Player*>(e);
    cout << ((p != nullptr) ? "true" : "false") << endl;

    // This will incur an additional run-time cost, because it must build and use type information.
    // You can turn it off in Visual Studio with the following setting, but dynamic_cast would then
    // give undefined behavior.
    //   Project Properties -> C/C++ -> Language -> Enable Run-Time Type Information: No
  }

}  // namespace

int main() {

  double value = 5.25;
  // ReSharper disable once CppCStyleCast
  const double a = (int) value + 5.5; // C-style cast
  cout << a << endl; // 10.5

  // C++-style casts provide syntax to make cast styles more explicit. Makes it easy 
  // to search for casts by type. Four types: static, reinterpret, const, dynamic.
 
  // static: verify at compile time that the conversion is possible
  const double s = static_cast<int>(value) + 5.5; // c++-style cast
  cout << s << endl;
  //double s2 = static_cast<Entity>(value); // compile error, can't cast a double as an Entity.

  // reinterpret: perform type punning to treat a memory block as a different type
  Enemy* s2 = reinterpret_cast<Enemy*>(&value);

  // TODO: const: add or remove const-ness

  // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points
  // to an instance of a particular derived type.
  unique_ptr<Entity> e = make_unique<Player>();
  print_entity_is_player(e.get());
  e = make_unique<Enemy>();
  print_entity_is_player(e.get());
}
