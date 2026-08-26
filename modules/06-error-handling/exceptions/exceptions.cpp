
// Demonstrate exceptions.
// See here: https://docs.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-160

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <limits>
using std::numeric_limits;

#include <stdexcept>
using std::invalid_argument;

#include<assert.h>

namespace {

  void my_function(const int value) {

    // Use assert to check errors for which you will not provide error handling.
    // assert(value < numeric_limits<char>::max()); // runtime assertion failure, only in debug mode

    // Use exceptions if the caller might provide error handling.
    if (value > numeric_limits<char>::max()) {
      throw invalid_argument("MyFunction argument too large."); // throw exceptions by value
    }
  }

} // namespace

int main() {

  try {
    my_function(256); // cause an exception
  }
  catch (invalid_argument& e) { // catch exceptions by reference
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
