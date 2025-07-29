
// Demonstrate some subtle evaluation order issues.
// See here: https://www.youtube.com/watch?v=qYxTP7wrCho&list=WL&index=18&t=263s

// You can easily compile the following code using different compilers at wandbox.org.

#include <iostream>
using std::cout;
using std::endl;

void PrintSum(int a, int b) {
  cout << a << " + " << b << " = " << (a + b) << endl;
}

int main() {

  int value = 0;
  
  // Undefined behavior: the order of the multiple increments is not defined by the C++ standard. 
  // For the following line of code, the result is 1 + 0 = 1 in Debug, and 0 + 0 = 0 in Release.
  // The reason for getting two zeros in the second case is because the compiler is allowed to 
  // work out the values in parallel. This is changed in C++17, and Release also results in
  // 1 + 0 = 1, but the rules also allow 0 + 1 = 1 (which is given by C++14 and Clang).
  PrintSum(value++, value++);

  value = 0;
  PrintSum(++value, ++value); // 2 + 2 = 4 in Debug and Release
}

