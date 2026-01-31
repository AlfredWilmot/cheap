#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lifo.h"

struct Lifo {
  size_t _capacity;
  BUFFER_TYPE *_head;  // base of stack memory, never changes (cannot make const due to opaque struct)
  BUFFER_TYPE *_tail;  // the stack ptr <= _head + capacity
} ;

Lifo *NewLifo(size_t capacity) {
  Lifo *lifo = (Lifo *) malloc(sizeof(Lifo));
  lifo->_capacity = capacity,
  lifo->_head = (BUFFER_TYPE *const) malloc(sizeof(BUFFER_TYPE) * capacity),  // determines stack allocation
  lifo->_tail = (BUFFER_TYPE *) lifo->_head; // stack-pointer, start at base of stack returned by malloc

  return lifo;
}

/* The number of entries on the stack. */
size_t Lifo_len(Lifo *self){
  if (self->_tail > self->_head) {
    return (size_t) (self->_tail - self->_head);
  } else {
    return (size_t) (self->_head - self->_tail);
  }
}

/* The maximum number of entries that can be pushed onto the stack. */
size_t Lifo_cap(Lifo *self){
  return self->_capacity;
};

/* Pop the last entry pushed onto the stack if the stack is not empty. */
bool Lifo_pop(Lifo *self, BUFFER_TYPE *val){
  if(val == NULL || self == NULL || Lifo_len(self) <= 0) {
    return false;
  } else {
    *val = *--self->_tail; // decrement stack ptr then pop value from memory
    return true;
  }
};

/* Push an entry onto the stack if the stack is not full. */
bool Lifo_push(Lifo *self, BUFFER_TYPE val){
  if(self == NULL || (Lifo_len(self) >= Lifo_cap(self))) {
    return false;
  } else {
    *self->_tail++ = val; // push value into memory then increment stack ptr
    return true;
  }
};

/* Release the heap-allocated memory used to creat the stack. */
void Lifo_del(Lifo *self){
  if (self->_head != NULL) {
    free(self->_head);
    // NOTE: cannot set _head to NULL as it is constant (beware of double-free vulns)
    self->_tail = NULL;
  }
}
