#include "umem.h"
#include <assert.h>

// Bring in the global variable 'has_run' from 'umem.c' to allow resetting it 
// during umeminit testing. 
extern int has_run;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Test function prototypes for 'umeminit(size_t sizeOfRegion,
//                                               int allocationAlgo)
//
void test_single_run();
void test_sizeOfRegion(size_t);
void test_umeminit();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Test function prototypes for 'umalloc(size_t size)'
//
void test_umalloc() {
  umeminit(4096,FIRST_FIT);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
//
int main () {
  test_umeminit();
}

/**
 * test_sizeOfRegion(size_t): passes in a value of size_t to umeminit and tests
 *     for the proper return of '0' for sizes greater than zero or '-1' for 
 *     sizes less than or equal to zero. 'has_run' must be reset after each use.
 */
void test_sizeOfRegion(size_t test_size) {
  if ((int)test_size <= 0) {
    assert(umeminit(test_size,FIRST_FIT) == -1);
  } else {
    assert(umeminit(test_size,FIRST_FIT) == 0);
  }
  has_run=0;
}

/** 
 * test_single_run(): runs the umeminit function twice without resetting the
 *     has_run variable to verify umeminit will exit with a value of '-1' when
 *     run more than once.
 */

void test_single_run() {
  assert(umeminit(4096,FIRST_FIT) == 0);
  assert(umeminit(4096,FIRST_FIT) == -1);
  has_run=0;
}

/** 
 * test_umeminit(): combines all the other tests into a single run testing for
 *     - failure or '-1' when sizeOfRegion is less than or equal to zero, or
 *       when umeminit is run more than once.
 *     - success or '0' when sizeOfRegion is greater than zero
 *     Note: I am uncertain how to simulate 'mmap' failure to test that scenario
 *     We use 1024 * 1024 to test that the function works for larger sizes.
 */

void test_umeminit() {
  test_single_run();
  test_sizeOfRegion(-1);
  test_sizeOfRegion(0);
  test_sizeOfRegion(4096);
  test_sizeOfRegion(1024*1024);
}
