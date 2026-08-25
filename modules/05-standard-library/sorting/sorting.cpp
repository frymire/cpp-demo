
// Demonstrate alternative sorting techniques.
// See here: https://www.youtube.com/watch?v=x0uUKWJzSO4&list=WL&index=26

// ReSharper disable CppUseRangeAlgorithm

#include <stdio.h>  // printf

// ReSharper disable once CppUnusedIncludeDirective
#include <stdlib.h>  // qsort

#include <iostream>
using std::cout;
using std::endl;

#include <array>
using std::array;

#include <algorithm>
using std::ranges::sort;

#include <functional>
using std::function;

namespace {

  int compare_ints(const void* a, const void* b) {
    const int x = *static_cast<const int*>(a);
    const int y = *static_cast<const int*>(b);
    return (x - y);
  }

  void print_values(const array<int, 5>& values) { for (const int v : values) { cout << v << " "; } }

} // namespace

int main() {

  cout << "\nSort in ascending order by default...\n";
  {
    array values = {3, 5, 1, 4, 2};
    sort(values /*, std::less<int>() */);
    print_values(values);
  }

  cout << "\n\nOnly sort the first 3 elements...\n";
  {
    array values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.begin() + 3);
    print_values(values);
  }

  cout << "\n\nSort in descending order...\n";
  {
    array values = {3, 5, 1, 4, 2};
    sort(values, std::greater());
    print_values(values);
  }

  cout << "\n\nUse a lambda to sort in descending order...\n";
  {
    array values = {3, 5, 1, 4, 2};
    sort(values, [](const int a, const int b) { return a > b; });
    print_values(values);
  }

  cout << "\n\nUse a lambda to provide an ascending sort, except that 1 goes to the end...\n";
  {
    array values = {3, 5, 1, 4, 2};
    const function<bool(int, int)> /*auto*/ special = [](const int a, const int b) {
      if (a == 1) return false;
      if (b == 1) return true;
      return a < b;
    };
    sort(values, special);
    print_values(values);
  }

  cout << "\n\nSort ascending with qsort...\n";
  {
    int values[] = {40, 10, 100, 90, 20, 25};
    std::qsort(values, 6, sizeof(int), compare_ints);
    for (int n = 0; n < 6; n++) cout << values[n] << " ";
  }

  cout << endl;
  return 0;
}
