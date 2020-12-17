
// Demostrate move semantics (new in C++11).
// See here: https://www.youtube.com/watch?v=ehMg6zvXuMY&t=31s
// And here: https://www.youtube.com/watch?v=OWNeCTd7yQE&list=WL&index=19&t=1s

#include <iostream>
using std::cout;
using std::endl;

class MyString {

  char* m_data;
  size_t m_size; // size_t is the type returned by strlen()

public:
  
  MyString() = default;
  
  MyString(const char* str) { 
    m_size = strlen(str);
    m_data = new char[m_size];
    memcpy(m_data, str, m_size);
    printf("Created (size = %d)!\n", m_size);
  }

  // Copy constructor (can pass an lvalue or rvalue parameter).
  MyString(const MyString& that) {
    m_size = that.m_size;
    m_data = new char[m_size]; // allocate memory
    memcpy(m_data, that.m_data, m_size); // copy everything into it
    printf("Copied (size = %d)!\n", m_size);
  }

  // Move constructor (requires rvalue parameter).
  MyString(MyString&& that) noexcept {

    m_size = that.m_size;
    m_data = that.m_data; // can just assign the pointer, because that is an rvalue

    // Tricky: Need to create a "hallow object", so that the data block isn't deleted 
    // when the destructor is called on that. 
    that.m_size = 0;
    that.m_data = nullptr;

    printf("Moved (size = %d)!\n", m_size);
  }

  ~MyString() { 
    delete m_data; 
    printf("Destroyed (size = %d)!\n", m_size);
  }

  void Print() {
    for (int i = 0; i < m_size; i++) printf("%c", m_data[i]);
    printf("\n");
  }
};


class Entity {

  MyString m_name;

public:

  Entity(const MyString& name): m_name(name) {}

  // Provide an Entity constructor that ensures the use of the MyString copy constructor. 
  //Entity(MyString&& name): m_name(name) {} // no, still uses MyString copy constructor to set m_name
  //Entity(MyString&& name): m_name((MyString&&) name) {} // casting to (MyString&&) works, but rarely used
  Entity(MyString&& name): m_name(std::move(name)) {} // best
  
  void PrintName() { m_name.Print(); }
};

int main() {
  Entity e(MyString("Mark"));
  e.PrintName();
}
