#include "umem.h"
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define CHUNK_SIZE 8

// GLOBAL
int has_run = FALSE;
int allocation_state;
node_t * free_list = NULL;

// UTILITY-BASED FUNCTIONS
size_t round_to_page_size (size_t size) {
  size_t page_size = getpagesize(); 
  if ((size % page_size) == 0) {
    return size;
  } else if(size < page_size) {
    return page_size;
  }
  return size + page_size - (size % page_size);
}

size_t align_8_byte (size_t size) {
  if ((int)size <= CHUNK_SIZE) {
    return CHUNK_SIZE;
  } else {
    return size + CHUNK_SIZE - (size % CHUNK_SIZE);
  }
}

void verify_magic (header_t * block) {
  if (block->magic != MAGIC) {
    fprintf(stderr, "Error: Memory corruption detected at block %p\n",block);
    exit(1);
  }
  return;
}

// void* split_block(size_t size, node_t* previous) {
  
// }
// FIT-BASED FUNCTIONS


// This function initializes the memory space using 'mmap()', assuming
// a valid allocationAlgo value(0-5) is given, and the function
// has only been called one time with a positive sizeOfRegion.
int umeminit (size_t sizeOfRegion, int allocationAlgo) {
  if (!has_run && (int)sizeOfRegion > 0) {
    sizeOfRegion = round_to_page_size(sizeOfRegion);
    free_list = mmap(0, sizeOfRegion,
                              PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (free_list == MAP_FAILED) {
      fprintf(stderr, "[Error] mmap() failed to allocate memory.");
      return -1;
    }
    
    has_run=TRUE;
    allocation_state = allocationAlgo;
    free_list->size=sizeOfRegion-sizeof(node_t);
    free_list->next=NULL;
    
    return 0;
  } else {
    return -1;
  }
}

// void* umalloc(size_t size) {
//   if ((int)size <= 0)
//     fprintf(stderr, "Error: Cannot allocate zero or negative memory")
//     return NULL;
//   size = align_8_byte(size);
    
//   return ptr;
// }
// void ufree(void * ptr) {
//   if (ptr == NULL)
//     return;
  
//   ptr->magic = 0;
//   ptr->size = (ptr->size) + sizeof(header_t); 
//   node_t * new_free_block;
//   new_free_block->size=ptr->size;
//   new_free_block->next=free_list;
  
// }

// void* seek_first_fit(size_t size) {
//   node_t* waypoint = free_list;

//   while (waypoint->next != NULL) {
//   }
// }

int contains(void * ptr) {
  node_t * current = free_list;
  while (current != NULL) {
    if (current == ptr)
      return TRUE;
    current=current->next;
  }
  return FALSE;
}
