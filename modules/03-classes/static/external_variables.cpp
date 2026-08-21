
// This line is okay, even with the same line in static.cpp.
#include "header_with_static.h"

// These would be linker errors, due to the duplicate declarations in static.cpp.
//int global = 5; 
//void DuplicateFunction() {}

// This was already declared in static.cpp, but not initialized. Because it 
// was declared in main with "extern" there is no linker error.
int externally_linked = 5;

// The declaration of this variable in main can't find this, because
// static effectively makes it "private" to this file. Linker error.
//static int externally_linked_to_static = 10;

// Redefining these here is okay, despite being declared in static.cpp.
// Declaring these as static means that the linker doesn't look outside of 
// this file. This is beneficial for limiting the scope of variables and 
// functions that would otherwise be global.
static int s_my_static_int = 10;
static void StaticFunction() {}
