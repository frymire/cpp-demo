
// Demonstrate a common mistake in creating variables on the stack.
// See: https://www.youtube.com/watch?v=iNuTwvD6ciI&list=WL&index=62

// To avoid the silent runtime error demonstrated below, you can change the corresponding
// warning to be treated as an error like this.
//#pragma warning (error: 4172)

// Alternatively, to do it across all file in the project, do this...
//   Project Properties -> C/C++ -> Advanced -> Treat Specific Warnings As Errors -> {add 4172}

#include <stdio.h>

// Don't do this. It creates an array on the stack, then returns a pointer
// to that array. But once we leave the scope of this function, since the 
// array was created on the stack, stackArray is deleted automatically.
int* BadArrayCreateFunction() {
  int stackArray[3] = {1, 2, 3};
  return stackArray; // causes warning C4172: returning address of local variable or temporary
}

// Instead, allocate the data on the heap.
int* GoodArrayCreateFunction() {
  int* heapArray = new int[3];
  heapArray[0] = 4;
  heapArray[1] = 5;
  heapArray[2] = 6;
  return heapArray; 
}

int main() {

  int* badArray = BadArrayCreateFunction();
  
  // The memory locations where badArray was stored have been now freed, and the data may be
  // overwritten with new data. Insidiously, you probably think the code is fine 
  // because it probably prints the right answer with this next call immediately after
  // the function returns. However, this is simply because nothing else has happened
  // on the stack yet that would overwrite the data.
  printf("%d %d %d\n", badArray[0], badArray[1], badArray[2]);

  int* goodArray = GoodArrayCreateFunction();
  printf("%d %d %d\n", goodArray[0], goodArray[1], goodArray[2]);
  
  // By now, the stack has grown past where the data for badArray were stored originally,
  // so now this same call as before results in gibberish...a silent runtime error.
  printf("%d %d %d\n", badArray[0], badArray[1], badArray[2]);
}
