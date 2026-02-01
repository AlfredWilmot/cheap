#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lifo.h"

struct Lifo {
  size_t _capacity;
  size_t _tail;  // top of the stack
  BUFFER_TYPE _buffer[];  // base of stack memory, never changes (cannot make const due to opaque struct)
} ;

Lifo *NewLifo(size_t capacity) {

  Lifo *lifo = (Lifo *) malloc(sizeof(Lifo) + sizeof(BUFFER_TYPE) * capacity);
  if (lifo == NULL) {
    printf("ERR: could not allocate Lifo container.");
    exit(EXIT_FAILURE);
  }

  lifo->_capacity = capacity,
  lifo->_tail = 0;

  return lifo;
}

/* The number of entries on the stack. */
size_t Lifo_len(Lifo *self){
  return self->_tail;
}

/* The maximum number of entries that can be pushed onto the stack. */
size_t Lifo_cap(Lifo *self){
  return self->_capacity;
};

/* Pop the last entry pushed onto the stack if the stack is not empty. */
bool Lifo_pop(Lifo *self, BUFFER_TYPE *val){
  if (self->_tail > 0 ) {
    *val = self->_buffer[--self->_tail];
    return true;
  } else {
    return false;
  }
};

/* Push an entry onto the stack if the stack is not full. */
bool Lifo_push(Lifo *self, BUFFER_TYPE val){
  if (self->_tail < self->_capacity) {
    self->_buffer[self->_tail++] = val;
    return true;
  } else {
    return false;
  }
};

/* Release the heap-allocated memory used to create the stack. */
void Lifo_del(Lifo **self){
  free((*self));
  *self = NULL; // prevent double-free vuln
}
