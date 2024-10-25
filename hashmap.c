#include "hashmap.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define INITIAL_CAPACITY 16

typedef struct {
  const char* key;
  void* value;
} hashmap_entry;

struct hashmap {
  hashmap_entry* entries;
  size_t capacity;
  size_t length;
};

hashmap* create_hashmap(void){
  hashmap* table = malloc(sizeof(hashmap));
  if(table == NULL){
    return NULL;
  }

  table->length = 0;
  table->capacity = INITIAL_CAPACITY; 
  table->entries = calloc(table->capacity, sizeof(hashmap_entry));

  return table;
}

void destroy_hashmap(hashmap* map){
  for(size_t i = 0; i < map->capacity; i++){
    free((void*)map->entries[i].key);
  }
  free(map->entries);
  free(map);
} 

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
  uint64_t hash = FNV_OFFSET;
  for (const char* p = key; *p; p++) {
    hash = hash ^ (uint64_t)(unsigned char)(*p);
    hash = hash * FNV_PRIME;
  }
  return hash;
}

void* hashmap_get(hashmap* map, const char* key){
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & (map->capacity - 1));
  while(map->entries[index].key != NULL){
    if(strcmp(key,map->entries[index].key) == 0){
      return map->entries[index].value;
    }
    if(index>=map->capacity){
      index = 0;
    }
  }

  return NULL;
}

static const char* hashmap_set_entry(
  hashmap_entry* entries, size_t capacity ,const char* key, void* value, size_t* plength
) {
  uint64_t hash = hash_key(key);
  size_t index = (size_t)( hash & (uint64_t)(capacity - 1) );
  
  while(entries[index].key != NULL){
    if(strcmp(entries[index].key, key) == 0 ){
      entries[index].value = value;
      return entries[index].key;
    }
    index++;
    if(index>=capacity){
      index = 0;
    }
  }

  if(plength != NULL){
    key = strdup(key);
    if(key == NULL){
      return NULL;
    }
    (*plength)++;
  }
  entries[index].key = (char*)key;
  entries[index].value = value;
  return key;
}

static bool hashmap_expand(hashmap* map) {
  size_t new_capacity = map->capacity * 2;
  if (new_capacity < map->capacity) {
    return false;
  }

  hashmap_entry* new_entries = calloc(new_capacity, sizeof(hashmap_entry));
  if(new_entries == NULL){
    return false;
  }

  for(size_t i = 0; i < map->capacity ; i++){
    hashmap_entry entry = map->entries[i];
    if(entry.key != NULL ){
      hashmap_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
    }
  }

  free(map->entries);
  map->entries = new_entries;
  map->capacity = new_capacity;
  return true;
}

const char* hashmap_set(hashmap* map, const char* key, void* value){
  assert(value != NULL);
  if (value == NULL) {
    return NULL;
  }

  if(map->length >= map->capacity / 2){
    if(!hashmap_expand(map)){
      return NULL;
    }
  }

  return hashmap_set_entry(map->entries, map->capacity, key, value, &map->length);
}

size_t hashmap_size(hashmap* map){
  return map->length;
}