#ifndef LIFO_H
#define LIFO_H

#include <stddef.h>
#include <stdbool.h>

#define BUFFER_TYPE int

typedef struct Lifo Lifo;

Lifo *NewLifo(size_t);

/* The number of entries on the stack. */
size_t Lifo_len(Lifo *);

/* The maximum number of entries that can be pushed onto the stack. */
size_t Lifo_cap(Lifo *);

/* Pop the last entry pushed onto the stack if the stack is not empty. */
bool Lifo_pop(Lifo *, BUFFER_TYPE *);

/* Push an entry onto the stack if the stack is not full. */
bool Lifo_push(Lifo *, BUFFER_TYPE);

/* Release the heap-allocated memory used to creat the stack. */
void Lifo_del(Lifo *);

#endif
