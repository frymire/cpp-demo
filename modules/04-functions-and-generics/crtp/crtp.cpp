
// Demonstrate the Curiously Recurring Template Pattern (CRTP), which gives you static polymorphism.
// A class derives from a template that is instantiated with the derived class itself. The base can
// then call functions in the derived class with no virtual functions at all, so the compiler
// resolves the calls at compile time. C++23 has a simpler way to do the same thing. See the
// deducing-this module.

#include <iostream>
using std::cout;
using std::endl;

#include <array>
using std::array;

namespace {

  // A mixin base. It supplies an algorithm, print_twice(), written in terms of a function that each
  // derived class must provide, print(). The template parameter is the derived class itself, which
  // looks circular. It works because the compiler only instantiates the body of a member function
  // when you call it, and by then the derived class is complete.
  template<typename DerivedT>
  class PrintableTwice {
  public:
    void print_twice() const {
      // Cast this pointer down to the derived type. The cast is safe, because the derived class
      // passed its own type as the template argument.
      const DerivedT* self = static_cast<const DerivedT*>(this);
      self->print();
      self->print();
    }
  };

  class Vertex : public PrintableTwice<Vertex> {
  public:
    static void print() { cout << "vertex" << endl; }
  };

  class Circle : public PrintableTwice<Circle> {
  public:
    static void print() { cout << "circle" << endl; }
  };

  // A second use, which virtual functions cannot do at all. Each instantiation of the template is a
  // separate class, so each derived class gets its own copy of the static counter.
  template<typename DerivedT>
  class InstanceCounter {
    static inline int s_count = 0;
  public:
    InstanceCounter() { s_count++; }
    static int count() { return s_count; }
  };

  class Apple : public InstanceCounter<Apple> {};
  class Orange : public InstanceCounter<Orange> {};

  // A third use. C++ has no virtual static member variables, but CRTP gives you the same effect.
  // The base names the derived type, so it can read a static member that each derived class
  // declares for itself. A virtual function cannot do this, because virtual dispatch works through
  // an object, and a static member belongs to the type.
  template<typename DerivedT>
  class PrintsIndices {
  public:
    void print_indices() const {
      for (const int i: DerivedT::indices) { cout << i << ' '; }
      cout << endl;
    }
  };

  class Triangle : public PrintsIndices<Triangle> {
  public:
    static constexpr array<int, 3> indices = {1, 2, 3};
  };

  class Quad : public PrintsIndices<Quad> {
  public:
    static constexpr array<int, 4> indices = {1, 2, 3, 4};
  };

}  // namespace

int main() {

  cout << "The base class calls print() in the derived class, with no virtual functions...\n";
  constexpr Vertex vertex;
  vertex.print_twice();
  constexpr Circle circle;
  circle.print_twice();

  cout << "\nEach derived class gets its own static counter...\n";
  [[maybe_unused]] Apple apple1, apple2, apple3;
  [[maybe_unused]] Orange orange1;
  cout << "Apples created: " << Apple::count() << endl;   // 3
  cout << "Oranges created: " << Orange::count() << endl; // 1

  cout << "\nThe base class reads a static member variable of the derived class...\n";
  Triangle().print_indices(); // 1 2 3
  Quad().print_indices();     // 1 2 3 4

  // The cost of CRTP: PrintableTwice<Vertex> and PrintableTwice<Circle> are unrelated types, so
  // there is no common base pointer that can hold both a Vertex and a Circle. The next two lines
  // do not compile. If you need to store mixed types together, use virtual functions instead.
  //   PrintableTwice* p = &vertex;
  //   std::vector<PrintableTwice*> shapes{&vertex, &circle};

  // The benefit: no vtable, no vtable pointer inside the object, and the compiler can inline the
  // calls. An empty base class also adds no size at all.
  cout << "\nsizeof(Vertex) = " << sizeof(Vertex) << endl; // 1, the same as an empty class

  return 0;
}
