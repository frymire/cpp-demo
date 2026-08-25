
// Adapted from Engineer Man demo. See here:
//   https://www.youtube.com/watch?v=RCHGco2NvMk&list=WL&index=80
//   https://github.com/engineer-man/youtube/blob/master/078/double.c

#include <cstdio>

#include "doubly_linked_list.h"

int main() {

  DoublyLinkedList list;
  list.add_at_end(2);
  list.add_at_end(3);
  list.add_at_end(5);
  list.add_at_beginning(1);
  list.add_at(4, 3);

  printf("forward:\n");
  list.print();

  list.remove(1);
  list.remove(3);
  list.remove(5);

  printf("\nreverse:\n");
  list.print_in_reverse();

  return 0;
}
