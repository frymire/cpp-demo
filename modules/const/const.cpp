
#include <iostream>
using std::cout;
using std::endl;

class Entity {

  int m_X;

  // Mutable variables can be changed even in methods marked as const.
  mutable int m_nGetCalls = 0;

public:

  Entity(int x): m_X(x) {}

  // Appending const to a class method prevents you from modifying member variables.
  int ConstGetter() const {
    //m_X = 2; // compile error
    m_nGetCalls++; // allowed for variables declared mutable 
    return m_X;
  }

  int SetX(int x) { m_X = x; }

  int NumGetCalls() { return m_nGetCalls; }
};

// Passing by constant reference.
void PrintEntity(const Entity& e) { 
  //e = new Entity(100); // compile error, can't change the pointer to the Entity.
  //e.SetX(100); // compile error, can't call a non-const method.
  cout << e.ConstGetter() << endl; 
}

int main() {
  
  const int MAX_AGE = 90;

  // If you put const before the pointer sign *, the contents pointed to can't change.
  // You can do it two equivalent ways...
  const int* ptr1 = new int(1);
  int const* ptr2 = new int(2);
  cout << *ptr1 << endl;
  cout << *ptr2 << endl;
  //*ptr1 = 10; // compile error, can't change the contents 

  // It's possible to change the address that the pointer points to. 
  ptr1 = (int*) &MAX_AGE;
  cout << *ptr1 << endl;
  //*ptr1 = 10; // compile error, still can't change the contents 

  // If you put const after the pointer sign *, the pointer cannot change, but the contents can.
  int* const ptr3 = new int(3);
  cout << *ptr3 << endl; 
  *ptr3 = 30;
  cout << *ptr3 << endl;
  //ptr3 = (int*) &MAX_AGE; // compile error, can't change the pointer address

  // Const pointer to const int. Can't change either.
  const int* const ptr4 = new int(4);
  cout << *ptr4 << endl;
  //*ptr4 = 40; // compile error
  //ptr4 = (const int*) &MAX_AGE; // compile error

  Entity e(5);
  cout << e.ConstGetter() << endl;
  cout << e.NumGetCalls() << endl;
}
