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

Test(lifotests, capacity_matches_allocated_amount){
  cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to match allocated amount: %zu", TEST_CAPACITY);
}

Test(lifotests, push_til_full_then_pop_til_empty){

  for (size_t i = 1; i <= TEST_CAPACITY; i++) {
    cr_expect(Lifo_push(lifo, i), "expect pushing to LIFO within its capacity to succeed");
    cr_expect(Lifo_len(lifo) == i, "expect length to match push count: %zu", i);
    cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to remain unchanged");
  }

  BUFFER_TYPE val = 0;
  for (size_t i = TEST_CAPACITY; i > 0 ; i--) {
    cr_expect(Lifo_pop(lifo, &val), "expect popping from LIFO with entries to succeed");
    cr_expect(val == i, "expect value to correspond to entry popped from LIFO");
    cr_expect(Lifo_len(lifo) == i - 1, "expect length to match pop count %zu", i);
    cr_expect(Lifo_cap(lifo) == TEST_CAPACITY, "expect capacity to remain unchanged");
  }

}

Test(lifotests, push_when_full){
  for (size_t i = 1; i <= TEST_CAPACITY; i++) {
    Lifo_push(lifo, i);
  }
  cr_expect(Lifo_push(lifo, 0) == false, "expect pushing to full LIFO to fail");
}

Test(lifotests, pop_when_empty){
  BUFFER_TYPE val = 0;
  cr_expect(Lifo_pop(lifo, &val) == false, "expect popping from empty LIFO to fail");
}
