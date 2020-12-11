
// Demonstrate how to create a dynamic library.

// Create an empty project, then...
//   Project Settings -> General -> Configuration Type -> Dynamic library (.dll)

#pragma once

namespace engine {

  // Unlike static libraries, you have to add __declspec(dllexport) to explicitly export 
  // a function in the dll. If you aren't generating a .lib file when this dynamic library
  // project is built, it's probably because you haven't added this for any functions.
  __declspec(dllexport) void PrintMessage();

  // To export a class, put the __declspec to the left of the class name.
  class __declspec(dllexport) Foo {
  public:
    Foo() { cout << "Foo!" << endl; }
  };
}
