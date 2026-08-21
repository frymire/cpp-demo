
// Adapted from Engineer Man demo. See here:
//   https://www.youtube.com/watch?v=RCHGco2NvMk&list=WL&index=80
//   https://github.com/engineer-man/youtube/blob/master/078/double.c

#include "doubly_linked_list.h"

int main(int argc, char **argv) {

  DoublyLinkedList my_list;
  my_list.AddAtEnd(2);
  my_list.AddAtEnd(3);
  my_list.AddAtEnd(5);
  my_list.AddAtBeginning(1);
  my_list.AddAt(4, 3);

  printf("forward:\n");
  my_list.Print();

  my_list.Remove(1);
  my_list.Remove(3);
  my_list.Remove(5);

  printf("\nreverse:\n");
  my_list.PrintInReverse();

  return 0;
}
