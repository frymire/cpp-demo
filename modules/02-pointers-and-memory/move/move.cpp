// Demonstrate move semantics (new in C++11).
// See here: https://www.youtube.com/watch?v=ehMg6zvXuMY&t=31s
// And here: https://www.youtube.com/watch?v=OWNeCTd7yQE&list=WL&index=19&t=1s
// And here: https://www.youtube.com/watch?v=6SaUwqw4ueE&list=WL&index=2&t=4s

// ReSharper disable CppNonExplicitConvertingConstructor

// ReSharper disable CppLocalVariableMayBeConst
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

namespace {

  class MovableString {

    char* m_data = nullptr;  // set explicitly so the default constructor doesn't leave it set to a garbage address
    size_t m_size = 0; // size_t is the type returned by strlen()

  public:

    MovableString() = default;

    MovableString(const char* str) { // NOLINT(*-explicit-constructor)
      m_size = strlen(str);
      m_data = new char[m_size];
      memcpy(m_data, str, m_size);
      printf("MovableString constructor, (size = %zu)!\n", m_size);  // %zu is for size_t
    }

    // Copy constructor. The const reference binds to lvalues and rvalues alike, but since a
    // move constructor exists, rvalues go there instead. A const rvalue lands here, which is
    // why std::move on a const object silently copies.
    MovableString(const MovableString& that) {
      m_size = that.m_size;
      m_data = new char[m_size]; // allocate memory
      memcpy(m_data, that.m_data, m_size); // copy everything into it
      printf("MovableString copy constructor, (size = %zu)\n", m_size);
    }

    // Move constructor (requires rvalue parameter).
    MovableString(MovableString&& that) noexcept {

      m_size = that.m_size;
      m_data = that.m_data; // can just assign the pointer, because that is an rvalue

      // Tricky: Need to create a "hollow object", so that the data block isn't deleted
      // when the destructor is called on that.
      that.m_size = 0;
      that.m_data = nullptr;

      printf("MovableString move constructor, (size = %zu)\n", m_size);
    }

    ~MovableString() {
      delete[] m_data;
      printf("MovableString destroyed (size = %zu)\n", m_size);
    }

    // Copy assignment operator (takes an lvalue, or a const rvalue, like the copy constructor).
    // Needed to satisfy Rule of 5, since adding the move assignment operator (below) deletes the implicit version.
    MovableString& operator=(const MovableString& that) {

      // If we get a request to copy this object to itself, do nothing. The check matters more here
      // than in the move version below, because without it we would delete our own data, and then
      // copy from the block we just released.
      if (this == &that) return *this;

      // Allocate and fill the new block first. If new throws here, this object still owns its
      // original data and stays valid. Deleting first would leave it holding a dangling pointer.
      char* p_new = new char[that.m_size];
      memcpy(p_new, that.m_data, that.m_size);

      // Only once that has succeeded, release the old data and take ownership of the new block.
      delete[] m_data;
      printf("Deleted data (size = %zu)\n", m_size);

      m_data = p_new;
      m_size = that.m_size;
      printf("MovableString copy assignment operator, (size = %zu)\n", m_size);

      return *this;
    }

    MovableString& operator=(MovableString&& that) noexcept {

      // If we get a request to move this object to itself, do nothing.
      if (this == &that) return *this;

      // First, delete data for the current MovableString.
      delete[] m_data;
      printf("Deleted data (size = %zu)\n", m_size);

      // Then, do the same steps as in the move constructor...
      m_size = that.m_size;
      m_data = that.m_data;
      that.m_size = 0;
      that.m_data = nullptr;
      printf("MovableString move assignment operator, (size = %zu)\n", m_size);

      return *this;
    }


    void print() const {
      for (size_t i = 0; i < m_size; i++) printf("%c", m_data[i]);
      printf("\n");
    }
  };


  class Entity {

    MovableString m_name;

  public:

    Entity(const MovableString& name): m_name(name) {  // NOLINT(*-explicit-constructor)
      cout << "Entity constructor\n";
    }

    // Construct an Entity while ensuring the use of the MovableString move constructor.
    //Entity(MovableString&& name): m_name(name) {} // no, still uses MovableString copy constructor to set m_name
    //Entity(MovableString&& name): m_name((MovableString&&) name) {} // casting works, but is poor style
    Entity(MovableString&& name): m_name(std::move(name)) {
      cout << "Entity move constructor\n";
    } // yes, uses move constructor, NOLINT(*-explicit-constructor)

    void print_name() const { m_name.print(); }
  };

}  // namespace

int main() {

  cout << "\nUse the explicit MovableString(const char*) constructor to instantiate an entity...\n";
  {
    const Entity e1(MovableString("Mark")); // creates the string on the stack and then moves it
    e1.print_name();
  }

  cout << "\nUse the implicit conversion to instantiate an entity...\n";
  {
    const Entity e2("Frymire");
    e2.print_name();
  }

  cout << "\nCopy from a source to a destination string...\n";
  {
    MovableString s = "source";
    s.print();
    const MovableString copied = s; // NOLINT(*-unnecessary-copy-initialization)
    copied.print();
  }

  cout << "\nMove from a source to a new destination string by casting...\n";
  {
    MovableString s = "source";
    s.print();
    const MovableString moved_with_cast = static_cast<MovableString&&>(s); // cast to an rvalue
    moved_with_cast.print();
  }

  cout << "\nMove from a source to a new destination string using std::move...\n";
  {
    MovableString s = "source";
    s.print();
    const MovableString moved_with_std_move(std::move(s)); // converts s to an rvalue
    // const MovableString moved_with_std_move = std::move(s);  // same, looks like assignment, but is a constructor
    moved_with_std_move.print();
  }

  cout << "\n*Copies* from a source to a new destination string even with std::move, because source is const...\n";
  {
    const MovableString s = "source";
    s.print();
    const MovableString moved_with_std_move(std::move(s)); // copies (!) because s is const
    moved_with_std_move.print();
  }

  cout << "\nCopy from a source to an existing destination string...\n";
  {
    MovableString s1 = "existing";
    MovableString s2 = "source";
    s1 = s2; // calls the copy assignment operator, not a constructor
    s1.print(); // source
    s2.print(); // source
  }

  cout << "\nMove from a source to an existing destination string using std::move...\n";
  {
    MovableString s1 = "existing";
    MovableString s2 = "source";
    s1.print();
    s2.print();
    s1 = std::move(s2); // calls operator=, not a constructor
    s1.print(); // source
    s2.print(); // "", because it's still a valid MovableString
  }

  cout << "\nDemonstrate why you should generally avoid std::move...\n\n";

  {
    cout << "Create 2, copy 2 into the array, and destroy 4." << endl;
    const MovableString s1("1");
    const MovableString s2("2");
    std::array strings{s1, s2};
  }

  {
    cout << "\nCreate 2, move 2, but still destroy 4 (!), since std::move leaves behind hollow (size = 0) objects.\n";
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

}
