#include <assert.h>
#include "../src/lifo.h"

// unit-tests
int main(int argc, char **argv){
  size_t cap = 10;
  Lifo *lifo = NewLifo(cap);
  BUFFER_TYPE data = 0;
  BUFFER_TYPE expect = 666;

  // test: stack size initialises to zero
  assert(Lifo_len(lifo) == 0);

  // test: stack capacity is as much as is allocated
  assert(Lifo_cap(lifo) == cap);

  // test: popping from empty stack repeatedly does not work
  while (cap-- > 0) {
    assert(Lifo_pop(lifo, &data) == false);
    assert(data == 0);
  }
  // test: pushing within stack capactiy succeeds
  while (++cap < 10) {
    assert(Lifo_push(lifo, expect) == true);
  }

  // test: pushing onto filled stack fails
  assert(Lifo_push(lifo, expect) == false);

  // test: popping within stack capacity succeeds
  while (cap-- > 0) {
    assert(Lifo_pop(lifo, &data) == true);
    assert(data == expect);
  }

}
