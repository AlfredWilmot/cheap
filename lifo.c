#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_TYPE int

typedef struct Lifo {
  size_t _capacity;
  BUFFER_TYPE *const _head;  // dictates the base of stack memory, never change
  BUFFER_TYPE *_tail;        // the stack ptr <= _head + capacity
} Lifo;

Lifo NewLifo(size_t capacity) {
  Lifo lifo = {
    ._capacity = capacity,
    ._head = (BUFFER_TYPE *const) malloc(sizeof(BUFFER_TYPE) * capacity),  // determines stack allocation
    ._tail = NULL,
  };
  lifo._tail = (BUFFER_TYPE *) lifo._head; // stack-pointer, start at base of stack returned by malloc
  return lifo;
}

size_t Lifo_len(Lifo *self){
  if (self->_tail > self->_head) {
    return (size_t) (self->_tail - self->_head);
  } else {
    return (size_t) (self->_head - self->_tail);
  }
}

size_t Lifo_cap(Lifo *self){
  return self->_capacity;
};

bool Lifo_pop(Lifo *self, BUFFER_TYPE *val){
  if(val == NULL || self == NULL || Lifo_len(self) <= 0) {
    return false;
  } else {
    *val = *--self->_tail; // decrement stack ptr then pop value from memory
    return true;
  }
};

bool Lifo_push(Lifo *self, BUFFER_TYPE val){
  if(self == NULL || (Lifo_len(self) >= Lifo_cap(self))) {
    return false;
  } else {
    *self->_tail++ = val; // push value into memory then increment stack ptr
    return true;
  }
};

// test
int main(int argc, char **argv){
  size_t cap = 10;
  Lifo lifo = NewLifo(cap);
  BUFFER_TYPE data = 0;
  BUFFER_TYPE expect = 666;

  // test: stack size initialises to zero
  assert(Lifo_len(&lifo) == 0);

  // test: stack capacity is as much as is allocated
  assert(Lifo_cap(&lifo) == cap);

  // test: popping from empty stack repeatedly does not work
  while (cap-- > 0) {
    assert(Lifo_pop(&lifo, &data) == false);
    assert(data == 0);
  }
  // test: pushing within stack capactiy succeeds
  while (++cap < 10) {
    assert(Lifo_push(&lifo, expect) == true);
  }

  // test: pushing onto filled stack fails
  assert(Lifo_push(&lifo, expect) == false);

  // test: popping within stack capacity succeeds
  while (cap-- > 0) {
    assert(Lifo_pop(&lifo, &data) == true);
    assert(data == expect);
  }

}
