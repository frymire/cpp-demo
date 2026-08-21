
// Need this to use strcpy and strcat, which are potentially unsafe.
// #define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

void print_it(char* str) {
  printf("String = %s, hex address = %p, unsigned int address = %lu\n", str, str, (uintptr_t) str);
}

int main() {

  // Allocate memory for a string. In C++, you have to explicitly cast the return type.
  printf("Allocating memory...\n");
  char* my_string = (char*) malloc(12); // Length of the string itself, plus 1 for the null terminator.
  strcpy(my_string, "MarkFrymire");
  print_it(my_string);

  // Reallocate the memory.
  printf("\nReallocating memory...\n");
  my_string = (char*) realloc(my_string, 25);
  print_it(my_string);

  strcat(my_string, ".com");
  print_it(my_string);

  free(my_string);
}
