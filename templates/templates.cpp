
// Demonstrate templates.
// See here: https://www.youtube.com/watch?v=I-hZkUa9mIs&list=WL&index=76

#include <iostream>
using std::cout;
using std::endl;

template<typename T> void Print(T value) { cout << value << endl; }

// Unlike Java generics, which depend on the type system, C++ templates let you pass 
// other categories of information. Here, use it to create whole class types on the fly.
// You're effectively programming what the compiler will do during compile-time.
template<typename T, int N> 
class Array {
private:
  T m_Array[N];
public:
  T GetSize() const { return N; }
};

int main() {

  // Implicit calls.
  Print(5);
  Print("Hello");
  Print(5.5f);

  // Explicit calls.
  Print<int>(5);
  Print<const char*>("Hello");
  Print<float>(5.5f);

  // Pass an array type and size via the template argument.
  Array<int, 10> my_array;
  cout << endl << my_array.GetSize() << endl;
}
