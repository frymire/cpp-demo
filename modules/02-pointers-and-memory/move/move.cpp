// Demonstrate move semantics (new in C++11).
// See here: https://www.youtube.com/watch?v=ehMg6zvXuMY&t=31s
// And here: https://www.youtube.com/watch?v=OWNeCTd7yQE&list=WL&index=19&t=1s
// And here: https://www.youtube.com/watch?v=6SaUwqw4ueE&list=WL&index=2&t=4s

#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class MovableString {

  char* m_data;
  size_t m_size; // size_t is the type returned by strlen()

public:
  
  MovableString() = default;
  
  MovableString(const char* str) { // NOLINT(*-explicit-constructor)
    m_size = strlen(str);
    m_data = new char[m_size];
    memcpy(m_data, str, m_size);
    printf("Created (size = %zu)!\n", m_size);  // %zu is for size_t
  }

  // Copy constructor (can pass an lvalue or rvalue parameter).
  MovableString(const MovableString& that) {
    m_size = that.m_size;
    m_data = new char[m_size]; // allocate memory
    memcpy(m_data, that.m_data, m_size); // copy everything into it
    printf("Copied (size = %zu)!\n", m_size);
  }

  // Move constructor (requires rvalue parameter).
  MovableString(MovableString&& that) noexcept {

    m_size = that.m_size;
    m_data = that.m_data; // can just assign the pointer, because that is an rvalue

    // Tricky: Need to create a "hallow object", so that the data block isn't deleted 
    // when the destructor is called on that. 
    that.m_size = 0;
    that.m_data = nullptr;

    printf("Moved (size = %zu)!\n", m_size);
  }

  ~MovableString() { 
    delete m_data; 
    printf("Destroyed (size = %zu)!\n", m_size);
  }

  MovableString& operator=(MovableString&& that) noexcept {

    // If we get a request to move this object to itself, do nothing.
    if (this == &that) return *this;

    // First, delete data for the current MovableString.
    delete[] m_data;
    printf("Deleted data (size = %zu)!\n", m_size);

    // Then, do the same steps as in the move constructor...
    m_size = that.m_size;
    m_data = that.m_data;
    that.m_size = 0;
    that.m_data = nullptr;
    printf("Moved (size = %zu)!\n", m_size);

    return *this;
  }


  void print() const {
    for (int i = 0; i < m_size; i++) printf("%c", m_data[i]);
    printf("\n");
  }
};


class Entity {

  MovableString m_name;

public:

  Entity(const MovableString& name): m_name(name) {}  // NOLINT(*-explicit-constructor)

  // Construct an Entity while ensuring the use of the MovableString move constructor. 
  //Entity(MovableString&& name): m_name(name) {} // no, still uses MovableString copy constructor to set m_name
  //Entity(MovableString&& name): m_name((MovableString&&) name) {} // casting works, but is poor style
  Entity(MovableString&& name): m_name(std::move(name)) {} // yes, uses move constructor, NOLINT(*-explicit-constructor)
  
  void print_name() const { m_name.print(); }
};

int main() {

  cout << "\nUse the explicit MovableString(const char*) constructor to instantiate an entity...\n";
  Entity e1(MovableString("Mark")); // creates the string on the stack and then moves it
  e1.print_name();

  cout << "\nUse the implicit conversion to instantiate an entity...\n";
  Entity e2("Frymire");
  e2.print_name();

  cout << "\nCopy from a source to a destination string...\n";
  MovableString source1 = "source";
  source1.print();
  MovableString copied_string = source1; // NOLINT(*-unnecessary-copy-initialization)
  copied_string.print();

  cout << "\nMove from a source to a new destination string by casting...\n";
  MovableString source2 = "source";
  source2.print();
  MovableString moved_with_cast = static_cast<MovableString&&>(source2); // cast to an rvalue
  // equivalent to "MovableString moved_with_cast((MovableString&&) source2);"
  moved_with_cast.print();

  cout << "\nMove from a source to a new destination string using std::move...\n";
  MovableString source3 = "source";
  source3.print();
  MovableString moved_with_std_move(std::move(source3)); // converts source3 to an rvalue
  // You could also say "MovableString moved_with_std_move = std::move(source);"
  // This looks like an assignment, but is actually a constructor.
  moved_with_std_move.print();

  cout << "\nMove from a source to an existing destination string using std::move...\n";
  MovableString source4 = "source";
  MovableString existing_string = "existing";
  source4.print();
  existing_string.print();
  existing_string = std::move(source4); // calls operator=, not a constructor
  source4.print(); // empty data, but still a valid MovableString
  existing_string.print();

  cout << "\nDemonstrate why you should generally avoid std::move...\n\n";

  {
    cout << "Create 2, copy 2 into the array, and destroy 4." << endl;
    MovableString s1("1");
    MovableString s2("2");
    std::array strings{s1, s2};
  }

  {
    cout << "\nCreate 2, move 2, but still destroy 4 (!), since std::move leaves behind hallow (size = 0) objects.\n";
    MovableString s1("1");
    MovableString s2("2");
    std::array strings{std::move(s1), std::move(s2)};
  }

  {
    // Lambda helper uses named RVO with copy/move elision rules to write return values directly into caller storage.
    auto make_string = [](const char *str) { MovableString s(str); /* ...other stuff... */; return s; };
    cout << "\nCreate 2, destroy 2. Named RVO avoids creation of temporaries in the lambda.\n";
    std::array strings{make_string("1"), make_string("2")};
  }

  cout << "\nCall remaining destructors...\n";
}
