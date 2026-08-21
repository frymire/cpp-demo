#pragma once

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

namespace shared_library {

  EXPORT void PrintMessage();

  class EXPORT Foo {
  public:
    Foo() { std::cout << "Foo!" << std::endl; }
  };
}
