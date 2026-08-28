
// Demonstrate a common mistake in creating variables on the stack.
// See: https://www.youtube.com/watch?v=iNuTwvD6ciI&list=WL&index=62

// To avoid the silent runtime error demonstrated below, you can change the corresponding
// warning to be treated as an error like this.
//#pragma warning (error: 4172)

// Alternatively, to do it across all files in the project, do this...
//   Project Properties -> C/C++ -> Advanced -> Treat Specific Warnings As Errors -> {add 4172}

#include <cstdio>

namespace {

// Don't do this. It creates an array on the stack, then returns a pointer
// to that array. But once we leave the scope of this function, since the
// array was created on the stack, stack_array is deleted automatically.
int* create_ephemeral_array() {
  int stack_array[3] = {1, 2, 3};
  return stack_array; // causes warning C4172: returning address of local variable or temporary
}

// Instead, allocate the data on the heap.
int* create_durable_array() {
  int* heap_array = new int[3];
  heap_array[0] = 4;
  heap_array[1] = 5;
  heap_array[2] = 6;
  return heap_array;
}

}

int main() {

  const int* bad_array = create_ephemeral_array();

  // The memory locations where bad_array was stored have been now freed, and the data may be
  // overwritten with new data. Insidiously, you probably think the code is fine
  // because it probably prints the right answer with this next call immediately after
  // the function returns. However, this is simply because nothing else has happened
  // on the stack yet that would overwrite the data.
  printf("%d %d %d\n", bad_array[0], bad_array[1], bad_array[2]);  // segfaults here on Linux

  const int* good_array = create_durable_array();
  printf("%d %d %d\n", good_array[0], good_array[1], good_array[2]);

  // By now, the stack has grown past where the data for bad_array were stored originally,
  // so now this same call as before results in gibberish...a silent runtime error.
  printf("%d %d %d\n", bad_array[0], bad_array[1], bad_array[2]);

  delete(good_array);
}
