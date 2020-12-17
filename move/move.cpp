
// Demostrate move semantics (new in C++11).
// See here: https://www.youtube.com/watch?v=ehMg6zvXuMY&t=31s
// And here: https://www.youtube.com/watch?v=OWNeCTd7yQE&list=WL&index=19&t=1s

#include <iostream>
using std::cout;
using std::endl;

using std::move;

class MovableString {

  char* m_data;
  size_t m_size; // size_t is the type returned by strlen()

public:
  
  MovableString() = default;
  
  MovableString(const char* str) { 
    m_size = strlen(str);
    m_data = new char[m_size];
    memcpy(m_data, str, m_size);
    printf("Created (size = %d)!\n", m_size);
  }

  // Copy constructor (can pass an lvalue or rvalue parameter).
  MovableString(const MovableString& that) {
    m_size = that.m_size;
    m_data = new char[m_size]; // allocate memory
    memcpy(m_data, that.m_data, m_size); // copy everything into it
    printf("Copied (size = %d)!\n", m_size);
  }

  // Move constructor (requires rvalue parameter).
  MovableString(MovableString&& that) noexcept {

    m_size = that.m_size;
    m_data = that.m_data; // can just assign the pointer, because that is an rvalue

    // Tricky: Need to create a "hallow object", so that the data block isn't deleted 
    // when the destructor is called on that. 
    that.m_size = 0;
    that.m_data = nullptr;

    printf("Moved (size = %d)!\n", m_size);
  }

  ~MovableString() { 
    delete m_data; 
    printf("Destroyed (size = %d)!\n", m_size);
  }

  MovableString& operator=(MovableString&& that) noexcept {

    // If we get a request to move this object to itself, do nothing.
    if (this == &that) return *this;

    // First, delete data for the current MovableString.
    delete[] m_data;
    printf("Deleted data (size = %d)!\n", m_size);

    // Then, do the same steps as in the move constructor...
    m_size = that.m_size;
    m_data = that.m_data;
    that.m_size = 0;
    that.m_data = nullptr;
    printf("Moved (size = %d)!\n", m_size);

    return *this;
  }


  void Print() {
    for (int i = 0; i < m_size; i++) printf("%c", m_data[i]);
    printf("\n");
  }
};


class Entity {

  MovableString m_name;

public:

  Entity(const MovableString& name): m_name(name) {}

  // Construct an Entity while ensuring the use of the MovableString move constructor. 
  //Entity(MovableString&& name): m_name(name) {} // no, still uses MovableString copy constructor to set m_name
  //Entity(MovableString&& name): m_name((MovableString&&) name) {} // casting to (MovableString&&) works, but rarely used
  Entity(MovableString&& name): m_name(move(name)) {} // yes, uses move constructor
  
  void PrintName() { m_name.Print(); }
};

int main() {

  cout << "\nUse the explicit MovableString(const char*) constructor to instantiate an entity...\n";
  Entity e1(MovableString("Mark")); // creates the string on the stack and then moves it
  e1.PrintName();

  cout << "\nUse the implicit conversion to instantiate an entity...\n";
  Entity e2("Frymire");
  e2.PrintName();

  cout << "\nCopy from a source to a destination string...\n";
  MovableString source1 = "source";
  source1.Print();
  MovableString copied_string = source1;
  copied_string.Print();

  cout << "\nMove from a source to a new destination string by casting...\n";
  MovableString source2 = "source";
  source2.Print();
  MovableString moved_with_cast = (MovableString&&) source2; // cast to an rvalue
  // equivalent to "MovableString moved_with_cast((MovableString&&) source2);"
  moved_with_cast.Print();

  cout << "\nMove from a source to a new destination string using std::move...\n";
  MovableString source3 = "source";
  source3.Print();
  MovableString moved_with_std_move(move(source3)); // converts source3 to an rvalue
  // You could also say "MovableString moved_with_std_move = move(source);" 
  // This looks like an assignment, but is actually a constructor.
  moved_with_std_move.Print();

  cout << "\nMove from a source to an existing destination string using std::move...\n";
  MovableString source4 = "source";
  MovableString existing_string = "existing";
  source4.Print();
  existing_string.Print();
  existing_string = move(source4); // calls operator=, not a constructor
  source4.Print(); // empty data, but still a valid MovableString
  existing_string.Print();

  cout << "\nCall destructors...\n";
}
