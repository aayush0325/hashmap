#include <stdio.h>
#include "hashmap.h"

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

  destroy_hashmap(someMap);
  printf("hashmap was destroyed\n");

  return 0;
}

/*

hashmap was created
1
boop
hashmap was destroyed

*/