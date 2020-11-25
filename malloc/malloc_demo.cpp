
// Need this to use strcpy and strcat, which are potentially unsafe.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printIt(char* str) {
  printf("String = %s, hex address = %p, unsigned int address = %u\n", str, str, (unsigned int) str);
}

void main() {

  // Allocate memory for a string. In C++, you have to explicitly cast the return type.
  printf("Allocating memory...\n");
  char* myString = (char*) malloc(12); // Length of the string itself, plus 1 for the null terminator.
  strcpy(myString, "MarkFrymire");
  printIt(myString);

  // Reallocate the memory.
  printf("\nReallocating memory...\n");
  myString = (char*) realloc(myString, 25);
  printIt(myString);

  strcat(myString, ".com");
  printIt(myString);

  free(myString);
}
