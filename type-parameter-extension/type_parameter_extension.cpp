
// Demonstrate the equivalent of <ChildType extends ParentType> type extension in Java. See:
// https://stackoverflow.com/questions/30687305/c-equivalent-of-using-t-extends-class-for-a-java-parameter-return-type
// https://ideone.com/rkFVXa

#include <iostream>
#include <type_traits> // enable_if, is_base_of
using std::cout;
using std::endl;
using std::enable_if;
using std::is_base_of;

class ParentClass {
public:
  char* a = (char*) "parent";
};

class ChildClass: public ParentClass {
public:
  char* b = (char*) "child";
};

class OtherClass {
public:
  char* b = (char*) "other";
};

template<typename T, typename enable_if<is_base_of<ParentClass, T>::value>::type* = nullptr> T Foo(T bar) {
  return T();
}

void main() {

  ChildClass child;
  cout << Foo(child).b << endl;

  //OtherClass other;
  //cout << (Foo(other)).b << endl; //compiler error
}
