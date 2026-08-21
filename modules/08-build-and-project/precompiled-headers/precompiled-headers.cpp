
// Demonstrate precompiled headers in Visual Studio. 
// See here: https://www.youtube.com/watch?v=trMdw6tCHlY
// And here: https://www.youtube.com/watch?v=eSI4wctZUto&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=72&t=2s

// With CMake, you don't need to do much. After you build the first time, look in the build directory...
//   cmake-build-debug/CMakeFiles/precompiled-headers.dir/
// The .gch file is the binary, so you can monitor when it is recreated. Experiment by commenting this line in
// CMakeLists.txt
//  target_precompile_headers(precompiled-headers PRIVATE modules/precompiled-headers/pch.h)

// With Visual Studio...
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
  cout << "Hello, world!" << endl;
}
