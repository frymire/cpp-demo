
// Demonstrate alternative sorting techniques.
// See here: https://www.youtube.com/watch?v=x0uUKWJzSO4&list=WL&index=26

#include <stdio.h>  // printf
#include <stdlib.h> // qsort

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;

int compareInts(const void* a, const void* b) {
  return (*(int*) a - *(int*) b);
}

int main() {

  // Quick sort
  int values[] = {40, 10, 100, 90, 20, 25};
  qsort(values, 6, sizeof(int), compareInts);
  for (int n = 0; n < 6; n++) printf("%d\n", values[n]);
  printf("\n");

  // Use std::sort to sort in ascending order by default.
  vector<int> values2 = {3, 5, 1, 4, 2};
  sort(values2.begin(), values2.end());
  for (int v : values2) { cout << v << endl; }
  cout << endl;

  // Use a lambda to sort in descending order.
  vector<int> values3 = {3, 5, 1, 4, 2};
  sort(values3.begin(), values3.end(), [](int a, int b) { return a > b; });
  for (int v : values3) { cout << v << endl; }
  cout << endl;

  // Use a lambda to provide an ascending sort, except that 1 goes to the end.
  vector<int> values4 = {3, 5, 1, 4, 2};
  auto special = [](int a, int b) { 
    if (a == 1) return false;
    if (b == 1) return true;
    return a < b; 
  };
  sort(values4.begin(), values4.end(), special);
  for (int v : values4) { cout << v << endl; }
}
