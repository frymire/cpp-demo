
#pragma warning (disable : 4996) // to use potentially unsafe *scanf function

#include <stdio.h>
#include <stdlib.h>

struct Triple {
  int n1, n2, n3;
};

int main() {

  FILE* p_file = fopen("../resources/files data.txt", "r");
  if(!p_file) {
    printf("Error opening file.\n");
    exit(1);
  }

  // Read a line of values individually
  int n1, n2, n3;
  fscanf(p_file, "%d,%d,%d", &n1, &n2, &n3);
  printf("n1 = %d, n2 = %d, n3 = %d\n", n1, n2, n3);

  // Read into a struct.
  Triple my_triple;
  while (fscanf(p_file, "%d,%d,%d", &my_triple.n1, &my_triple.n2, &my_triple.n3) == 3) {
    printf("my_triple = %d %d %d\n", my_triple.n1, my_triple.n2, my_triple.n3);
  }

  fclose(p_file);
  return 0;
}
