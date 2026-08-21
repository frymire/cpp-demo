
#include <iostream>
using std::cout;
using std::endl;

#include "shared_library.h"

namespace shared_library {
  void PrintMessage() { cout << "Hi, from the dynamic library." << endl; }
}
