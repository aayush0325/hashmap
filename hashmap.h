#ifndef HASHMAP_H

#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct hashmap hashmap;

hashmap* create_hashmap(void);

void destroy_hashmap(hashmap* map);

void* hashmap_get(hashmap* map, const char* key);

const char* hashmap_set(hashmap* map, const char* key, void* value);

size_t hashmap_size(hashmap* map);

#endif // HASHMAP_H
