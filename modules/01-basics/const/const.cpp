
#include <iostream>
using std::cout;
using std::endl;

namespace
{
  class Entity {

    int m_x;

    // Mutable variables can be changed even in methods marked as const.
    mutable int m_num_get_calls = 0;

  public:

    explicit Entity(const int x): m_x(x) {}

    // Appending const to a class method prevents you from modifying member variables.
    int get_x() const {
      //m_x = 2; // compile error
      m_num_get_calls++; // allowed for variables declared mutable
      return m_x;
    }

    void set_x(const int x) { m_x = x; }

    int get_num_get_calls() const { return m_num_get_calls; }
  };

  // Passing by constant reference.
  [[maybe_unused]] void print_entity(const Entity& e) {
    //e = new Entity(100); // compile error, can't change the pointer to the Entity.
    //e.SetX(100); // compile error, can't call a non-const method.
    cout << e.get_x() << endl;
  }

}

int main() {

  constexpr int kMaxAge = 90;

  // If you put const before the pointer sign *, the contents pointed to can't change.
  // You can do it two equivalent ways...
  const int* ptr1 = new int(1);
  int const* ptr2 = new int(2);
  cout << *ptr1 << endl;
  cout << *ptr2 << endl;
  //*ptr1 = 10; // compile error, can't change the contents 

  // It's possible to change the address that the pointer points to. 
  ptr1 = &kMaxAge;
  cout << *ptr1 << endl;
  //*ptr1 = 10; // compile error, still can't change the contents

  // If you put const after the pointer sign *, the pointer cannot change, but the contents can.
  int* const ptr3 = new int(3);
  cout << *ptr3 << endl; 
  *ptr3 = 30;
  cout << *ptr3 << endl;
  //ptr3 = &kMaxAge; // compile error, can't change the pointer address

  // Const pointer to const int. Can't change either.
  const int* const ptr4 = new int(4);
  cout << *ptr4 << endl;
  //*ptr4 = 40; // compile error
  //ptr4 = (const int*) &kMaxAge; // compile error

  cout << "\nIn classes...\n";
  Entity e{5};
  cout << e.get_x() << endl;
  cout << e.get_num_get_calls() << endl;
  e.set_x(6);
  cout << e.get_x() << endl;
  cout << e.get_num_get_calls() << endl;

  return 0;
}
