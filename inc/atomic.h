#ifndef _INC_ATOMIC_H
#define _INC_ATOMIC_H

#include <types.h>

/*linux中连这个宏都优化到了机制，我这就不效仿了*/
#define LOCK_PREFIX "lock;"

int32_t atomic_read(atomic_t n);

void atomic_set(atomic_t* n, int32_t i);

void atomic_add(atomic_t* n, int32_t i);

void atomic_sub(atomic_t* n, int32_t i);

void atomic_inc(atomic_t *n);

void atomic_dec(atomic_t *n);

#endif
