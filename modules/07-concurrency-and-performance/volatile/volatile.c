
// Demonstrate the keyword "volative" for preventing compiler optimizations.

// NOTE: The problem that this code is supposed to show doesn't show up when using Visual Studio. 
// Use wandbox.org to compile using gcc.

#include <stdio.h>

int main() {

  const int nonvolatile_int = 10;
  printf("Initial value of nonvolatile_local: %d\n", nonvolatile_int);

  // Even though nonvolatile_int was declared const, we can bypass and update it via pointer access.
  // This simulates cases when memory contents can be modified externally during runtime, for
  // instance, by other threads, interrupt service routines, or memory mapped I/O.
  int* ptr1 = (int*) &nonvolatile_int;
  *ptr1 = 100;

  // Using GCC, if compiler optimization is turned off (i.e. debug mode), the next print function reports 
  // 100, as expected. If compiler optimization is turned on, however (i.e. release mode), it returns 10. 
  // Since nonvolatile_int was declared const, the compiler thinks that it can't change, so the code 
  // that simulates the external change to the memory contents gets removed. 
  printf("Modified value of nonvolatile_local: %d\n", nonvolatile_int); // 100 in debug, 10 in release

  // Declaring a variable to be volatile prevents the compiler from applying any optimizations to it.
  volatile const int volatile_int = 10;
  printf("\nInitial value of volatile_int: %d\n", volatile_int);
  int* ptr2= (int*) &volatile_int;
  *ptr2 = 100;
  printf("Modified value of volatile_int: %d\n", volatile_int); // 100 in debug and release
}
