
#include <stdio.h>  // printf
#include <stdlib.h> // qsort

int compareInts(const void* a, const void* b) {
  return (*(int*) a - *(int*) b);
}

void main() {
  int values[] = {40, 10, 100, 90, 20, 25};
  qsort(values, 6, sizeof(int), compareInts);
  for (int n = 0; n < 6; n++) printf("%d ", values[n]);
  printf("\n\n");
}
