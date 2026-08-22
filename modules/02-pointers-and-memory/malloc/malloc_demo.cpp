
// Need this to use strcpy and strcat, which are potentially unsafe.
// #define _CRT_SECURE_NO_WARNINGS

#include <cstdio>  // printf
#include <cstdlib>  // malloc
#include <cstring>  // strcpy

static void print_it(char* str) {
  printf("String = %s, hex address = %p, unsigned int address = %llu\n", str, str, reinterpret_cast<uintptr_t>(str));
}

int main() {

  // Allocate memory for a string. In C++, you have to explicitly cast the return type.
  printf("Allocating memory...\n");
  char* p_string = static_cast<char*>(malloc(12)); // length of the string itself, plus 1 for the null terminator
  strcpy(p_string, "MarkFrymire");
  print_it(p_string);

  // Reallocate the memory. You might or might not get a new address.
  printf("\nReallocating (and automatically copying) memory...\n");
  char* p_reallocated_string = static_cast<char*>(realloc(p_string, 25));
  if (p_reallocated_string == nullptr) {  // if realloc fails, it does not free the original block
    free(p_string);
    return 1;
  }
  p_string = p_reallocated_string;
  print_it(p_string);

  strcat(p_string, ".com");
  print_it(p_string);

  free(p_string);

  return 0;
}
