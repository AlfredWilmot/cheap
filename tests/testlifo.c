#include <criterion/criterion.h>
#include <assert.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stddef.h>
#include <stdio.h>
#include "../src/lifo.h"


/* Prepare test fixtures. */
static Lifo *lifo = NULL;

const size_t TEST_CAPACITY = 10;

static void setup(void){
  lifo = NewLifo(TEST_CAPACITY);
}

static void teardown(void){
  Lifo_del(&lifo);
}

TestSuite(lifotests, .init=setup, .fini=teardown);

/* Unit-tests. */

Test(lifotests, create){
  cr_expect(lifo != NULL, "ptr to newly created LIFO should not be NULL");
}

Test(lifotests, destroy){
  Lifo_del(&lifo);
  cr_expect(lifo == NULL, "ptr to released LIFO should be NULL");
}

Test(lifotests, initialise_zero_length){
  cr_expect(Lifo_len(lifo) == 0, "expect zero entries for new LIFO");
}

Test(lifotests, capacity_matches_alloacted_amount){
  cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to match allocated amount: %zu", TEST_CAPACITY);
}

Test(lifotests, verify_length_on_consecutive_pushes_and_pops){

  for (size_t i = 1; i <= TEST_CAPACITY; i++) {
    cr_expect(Lifo_push(lifo, i), "expect pushing to LIFO within its capacity to succeed");
    cr_expect(Lifo_len(lifo) == i, "expect length to match push count: %zu", i);
    cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to remain unchanged");
  }

  for (size_t i = 1; i <= TEST_CAPACITY; i++) {
    cr_expect(Lifo_push(lifo, i) == false, "expect pushing to full LIFO to fail");
  }

  BUFFER_TYPE val = 0;
  for (size_t i = TEST_CAPACITY; i > 0 ; i--) {
    cr_expect(Lifo_pop(lifo, &val), "expect popping to LIFO with entries to succeed");
    cr_expect(val == i, "expect value to correspond to entry popped from LIFO");
    cr_expect(Lifo_len(lifo) == i - 1, "expect length to match pop count %zu", i);
    cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to remain unchanged");
  }

  for (size_t i = 1; i <= TEST_CAPACITY; i++) {
    cr_expect(Lifo_pop(lifo, &val) == false, "expect popping from empty LIFO to fail");
  }

}

// unit-tests
//int main(int argc, char **argv){
//  size_t cap = 10;
//  Lifo *lifo = NewLifo(cap);
//  BUFFER_TYPE data = 0;
//  BUFFER_TYPE expect = 666;
//
//  // test: popping from empty stack repeatedly does not work
//  while (cap-- > 0) {
//    assert(Lifo_pop(lifo, &data) == false);
//    assert(data == 0);
//  }
//  // test: pushing onto filled stack fails
//  assert(Lifo_push(lifo, expect) == false);
//
//}
