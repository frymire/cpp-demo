
// Demonstrate an application that uses a static library built as a separate project in the Visual 
// Studio solution. See here: https://www.youtube.com/watch?v=Wt4dxDNmDA8&list=WL&index=19

// It's possible, but brittle, to find your header file by a relative path.
//#include "../static-library/engine.h"

// It's better to specify the path relative to the solution directory.
//   Project Properties -> C/C++ -> Additional Include Directories -> $(SolutionDir)static-library
#include "engine.h"

// You could reference the library directly where it is built, as with any other externally 
// generated library. For a library built within the same solution, however, you can let Visual 
// Studio make the connection automatically by referencing the library project. This setup also
// ensures that any changes to the static library are reflected in the application when running the
// latter.
//   Right-click the project -> Add -> Reference -> {select the static library project}

int main() {
  engine::PrintMessage();
}
