#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printIt(char *myString) {
	printf("String = %s, hex address = %p, unsigned int address = %u\n", myString, myString, (unsigned int) myString);
}

int main() {

	// Allocate memory for a string. In C++, you have to explicitly cast the return type.
	printf("Allocating memory...\n"); 
	char* myString = (char*) malloc(15);
	strcpy(myString, "tutorialspoint");
	printIt(myString);

	// Reallocate the memory.
	printf("\nReallocating memory...\n");
	myString = (char*) realloc(myString, 25);
	printIt(myString);

	strcat(myString, ".com");
	printIt(myString);

	free(myString);
	return 0;
}