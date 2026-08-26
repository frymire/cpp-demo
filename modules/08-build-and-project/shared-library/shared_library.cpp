
#include <iostream>
using std::cout;
using std::endl;

#include "shared_library.h"

namespace shared_library {
  void print_message() { cout << "Hi, from the dynamic library." << endl; }
}
