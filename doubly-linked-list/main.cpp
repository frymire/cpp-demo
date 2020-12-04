
// Adapted from Engineer Man demo. See here:
//   https://www.youtube.com/watch?v=RCHGco2NvMk&list=WL&index=80
//   https://github.com/engineer-man/youtube/blob/master/078/double.c

#include "doubly_linked_list.h"

int main(int argc, char **argv) {

  DoublyLinkedList myList;
  myList.add_at_end(2);
  myList.add_at_end(3);
  myList.add_at_end(5);
  myList.add_at_beginning(1);
  myList.add_at(4, 3);

  printf("forward:\n");
  myList.print();

  myList.remove(1);
  myList.remove(3);
  myList.remove(5);

  printf("\nreverse:\n");
  myList.print_in_reverse();

  return 0;
}
