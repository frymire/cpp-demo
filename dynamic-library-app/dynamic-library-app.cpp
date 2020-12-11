
// Demonstrate an application that uses a dynamic library built as a separate project in the Visual 
// Studio solution. See here: https://www.youtube.com/watch?v=pLy69V2F_8M&list=WL&index=16

#include <iostream>
using std::cout;
using std::endl;

// It's possible, but brittle, to find your header file by a relative path.
//#include "../dynamic-library/engine.h"

// It's better to specify the path relative to the solution directory.
//   Project Properties -> C/C++ -> Additional Include Directories -> $(SolutionDir)dynamic-library
#include "engine.h"

// To use a DLL, you need to link the code to an "import library." This is a .lib file built
// with the DLL that provides pointers into functions stored in the DLL itself.
//   Project Properties -> General -> Additional Library Directories: {path to .lib folder}
//   Project Properties -> Linker -> Input -> Additional Libraries: dynamic-library.lib

// For a library built within the same solution, however, you can let Visual Studio make this
// connection automatically by referencing the library project. This setup also ensures that 
// any changes to the dynamic library are reflected in the application when running the latter.
//   Right-click the project -> Add -> Reference -> {select the dynamic library project}

// When running the application, dynamic-library.dll must be on the path. This is easiest achieved by 
// putting the DLL in the same folder as the executable.

int main() {
  engine::Foo my_foo;
  engine::PrintMessage();
}
