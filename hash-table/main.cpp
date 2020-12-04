
// Demonstrate a hash table implementation, adapted from an Engineer Man demo.
// See: https://www.youtube.com/watch?v=wg8hZxMRwcw&list=WL&index=83
// And: https://github.com/engineer-man/youtube/blob/master/077/hashtable.c

#include "hash_table.h"

void main() {

  HashTable names(4); // also interesting with 20,000

  names.set("name1", "em");
  names.set("name2", "russian");
  names.set("name3", "pizza");
  names.set("name4", "doge");
  names.set("name5", "pyro");
  names.set("name6", "joost");
  names.set("name7", "kalix");
  names.print();

  printf("\n\nRemove names 3, 4, and 6...\n\n");
  names.remove("name3");
  names.remove("name4");
  names.remove("name6");
  printf("\n");
  names.print();
}
