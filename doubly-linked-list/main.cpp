
// Adapted from Engineer Man demo. See here:
//   https://www.youtube.com/watch?v=RCHGco2NvMk&list=WL&index=80
//   https://github.com/engineer-man/youtube/blob/master/078/double.c

#include "doubly_linked_list.h"

int main(int argc, char **argv) {

  add_at_end(2);
  add_at_end(3);
  add_at_end(5);
  add_at_beginning(1);
  add_at(4, 3);

  printf("forward:\n");
  print();

  remove(1);
  remove(3);
  remove(5);

  printf("reverse:\n");
  print_in_reverse();

  return 0;
}
