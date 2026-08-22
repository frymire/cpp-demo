
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

  // An old-style API that takes a non-const pointer, even though it only reads.
  void print_message(char* message) { cout << message << endl; }

  // Don't pass the unique pointer here. This function just wants a view, not full ownership.
  void print_entity_is_player(Entity* e) {

    // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points to an instance of a
    // particular derived type. If so, return a valid pointer, otherwise nullptr. Note that the type parameter passed
    // to the dynamic_cast must be polymorphic or the call doesn't make sense and a compile time error occurs.
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
  [[maybe_unused]] Enemy* s2 = reinterpret_cast<Enemy*>(&value);

  // const: add or remove const-ness. This is the only cast that can change const, and it
  // cannot change the underlying type.

  // Adding const never needs a cast, because it is always safe. The compiler does it for
  // you, so this line only documents the intent.
  const double* p_read_only = const_cast<const double*>(&value);
  cout << *p_read_only << endl; // 5.25

  // Removing const is well defined as long as the object itself is not const. Here, value
  // is a plain double, so writing through the stripped pointer is legal.
  double* p_writable = const_cast<double*>(p_read_only);
  *p_writable = 7.5;
  cout << value << endl; // 7.5

  // The main legitimate use: call an old API that takes a non-const pointer, even though
  // it only reads. Removing const to READ is always safe.
  const char* greeting = "Hello, from a const char pointer.";
  print_message(const_cast<char*>(greeting));

  // Removing const from an object that really is const gives undefined behavior as soon as
  // you write through the pointer. The compiler trusts the const, so it may keep the old
  // value, or it may put the object in read-only memory and crash. Never do this.
  const int kMax = 10;
  int* p_max = const_cast<int*>(&kMax);
  *p_max = 20;
  cout << kMax << " " << *p_max << " (undefined behavior)" << endl; // prints "10 20" with this compiler

  // dynamic_cast: evaluate at run-time whether a polymorphic base class pointer points
  // to an instance of a particular derived type.
  unique_ptr<Entity> e = make_unique<Player>();
  print_entity_is_player(e.get());
  e = make_unique<Enemy>();
  print_entity_is_player(e.get());
}
