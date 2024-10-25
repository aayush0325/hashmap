#include <stdio.h>
#include "hashmap.h"
#include <stdint.h>

int main() {
  hashmap* someMap = create_hashmap();
  printf("hashmap was created\n");

  int bar = 1;
  char* boop = "boop";

  hashmap_set(someMap, "foo", &bar);
  hashmap_set(someMap, "beep", &boop);

  void* result = hashmap_get(someMap, "foo");
  void* result2 = hashmap_get(someMap, "beep");

  printf("%d\n", *(int*)result);
  printf("%s\n", *(char**)result2);

  size_t size_of_hashmap = hashmap_size(someMap);
  printf("The size of this hashmap is %ld\n", size_of_hashmap);

  destroy_hashmap(someMap);
  printf("hashmap was destroyed\n");

  return 0;
}

/*

hashmap was created
1
boop
The size of this hashmap is 2
hashmap was destroyed

*/