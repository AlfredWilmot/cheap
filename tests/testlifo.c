#include <criterion/criterion.h>
#include <assert.h>
#include <criterion/internal/test.h>
#include <stddef.h>
#include "../src/lifo.h"


/* Prepare test fixtures. */
static Lifo *lifo = NULL;

static void setup(void){
  lifo = NewLifo(10);
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
  Lifo_del(&lifo);
  cr_expect(lifo == NULL, "ptr to released LIFO should be NULL");
}

// unit-tests
//int main(int argc, char **argv){
//  size_t cap = 10;
//  Lifo *lifo = NewLifo(cap);
//  BUFFER_TYPE data = 0;
//  BUFFER_TYPE expect = 666;
//
//  // test: stack size initialises to zero
//  assert(Lifo_len(lifo) == 0);
//
//  // test: stack capacity is as much as is allocated
//  assert(Lifo_cap(lifo) == cap);
//
//  // test: popping from empty stack repeatedly does not work
//  while (cap-- > 0) {
//    assert(Lifo_pop(lifo, &data) == false);
//    assert(data == 0);
//  }
//  // test: pushing within stack capactiy succeeds
//  while (++cap < 10) {
//    assert(Lifo_push(lifo, expect) == true);
//  }
//
//  // test: pushing onto filled stack fails
//  assert(Lifo_push(lifo, expect) == false);
//
//  // test: popping within stack capacity succeeds
//  while (cap-- > 0) {
//    assert(Lifo_pop(lifo, &data) == true);
//    assert(data == expect);
//  }
//
//}
