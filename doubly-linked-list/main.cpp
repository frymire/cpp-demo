
// Adapted from Engineer Man demo. See here:
//   https://www.youtube.com/watch?v=RCHGco2NvMk&list=WL&index=80
//   https://github.com/engineer-man/youtube/blob/master/078/double.c

#include "doubly_linked_list.h"

int main(int argc, char **argv) {

  DoublyLinkedList myList;
  myList.AddAtEnd(2);
  myList.AddAtEnd(3);
  myList.AddAtEnd(5);
  myList.AddAtBeginning(1);
  myList.AddAt(4, 3);

  printf("forward:\n");
  myList.Print();

  myList.Remove(1);
  myList.Remove(3);
  myList.Remove(5);

  printf("\nreverse:\n");
  myList.PrintInReverse();

  return 0;
}
