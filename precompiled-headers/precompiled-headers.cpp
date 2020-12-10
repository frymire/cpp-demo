
// Demonstrate precompiled headers.
// See here: https://www.youtube.com/watch?v=trMdw6tCHlY
// And here: https://www.youtube.com/watch?v=eSI4wctZUto&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=72&t=2s

// Project Setup...
// Go to Project Properties -> C/C++ -> Precompiled Headers
//   - Platform: 'All Platforms'
//   - Configuration: All Configurations
//   - Precompiled Header: Use (/Yu)
// The Precompiled Header settings for new files are inherited from the project.

// You also need to explicitly create the precompiled header from the pch.cpp file like this...
// pch.cpp Properties -> Configuration Properties -> C/C++ Precompiled Headers -> Precompiled Header : Create(/Yc)

// Any time pch.h is changed, the compiler makes a binary {project}.pch file which the rest 
// of your code can link to. To see if it makes a difference, compare compile times with the 
// precompiled header setting above turned on (i.e. "Use (/Yu)") versus off. 

// Tell MSVC to output build timing like this...
//   Tools -> Options -> Projects and Solutions -> VC++ Project Settings -> Build Timing: Yes

// It's possible, but difficult, to use precompiled headers in a shared project.
// See here: https://devblogs.microsoft.com/cppblog/shared-pch-usage-sample-in-visual-studio/

#include "pch.h"
using std::cout;
using std::endl;

int main() {
  cout << "Hello World! " << endl;
}
