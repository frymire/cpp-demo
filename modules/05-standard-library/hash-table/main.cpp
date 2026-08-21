
// Demonstrate a hash table implementation, adapted from an Engineer Man demo.
// See: https://www.youtube.com/watch?v=wg8hZxMRwcw&list=WL&index=83
// And: https://github.com/engineer-man/youtube/blob/master/077/hashtable.c

#include "hash_table.h"

int main() {

  HashTable names(4); // also interesting with 20,000

  names.Set("name1", "em");
  names.Set("name2", "russian");
  names.Set("name3", "pizza");
  names.Set("name4", "doge");
  names.Set("name5", "pyro");
  names.Set("name6", "joost");
  names.Set("name7", "kalix");
  names.Print();

  printf("\n\nRemove names 3, 4, and 6...\n\n");
  names.Remove("name3");
  names.Remove("name4");
  names.Remove("name6");
  printf("\n");
  names.Print();
}
