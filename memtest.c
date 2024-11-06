#include <stdlib.h>
#include <stdio.h>
#include "umem.h"

/**
 * For this project we have to implement the 5 algorithms,
 *	BEST_FIT, WORST_FIT, FIRST_FIT NEXT_FIT, BUDDY. I am describing
 *	those algorithms here for reference during implementation in my
 *	actual code. 
 *	1)	BEST_FIT - Go through the free list at least once and pick the
 *	first block that closest fits the requested size of allocated
 *	memory.
 *	2) WORST_FIT - Take a chunk of memory from the largest block in the
 *	free list (usually located at the end).
 *	3) FIRST_FIT - Take a chunk of memory from the first block located
 *	in the free list that fits.
 *	4) EXT_FIT - Starting from the free block created from your last
 *	split search the free list and allocate memory from the next
 *	free block in the list that fits the request.
 *	5) BUDDY - Split memory when allocating into binary pairs. 
 *	Wikipedia example:
 *  Set a limit of the smallest 2^n size equal to or larger than the requested
 *  allocation. If a block is found
 *  
  */


int get_block_size (int size) {
	int n=1;
	int order=0;
	while(n<size) {
		n+=n;
	}
	return n;
}


int main (int argc, char * argv[]) {
	printf("%d\n", get_block_size(atoi(argv[1])));
	
}
