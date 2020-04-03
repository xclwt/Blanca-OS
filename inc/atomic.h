#ifndef _INC_ATOMIC_H
#define _INC_ATOMIC_H

#include <types.h>

/*linux中连这个宏都优化到了机制，我这就不效仿了*/
#define LOCK_PREFIX "lock;"

inline int32_t atomic_read(atomic_t n){
	return n.counter;
}

inline void atomic_set(atomic_t* n, int32_t i){
	asm volatile (LOCK_PREFIX "movl %1, %0"
				: "+m" (n->counter)
				: "ia" (i));
}

inline void atomic_add(atomic_t* n, int32_t i){
	asm volatile (LOCK_PREFIX "addl %1, %0"
				: "+m" (n->counter)
				: "ia" (i));
}

inline void atomic_sub(atomic_t* n, int32_t i){
	asm volatile (LOCK_PREFIX "subl %1, %0"
				: "+m" (n->counter)
				: "ia" (i));
}

inline void atomic_inc(atomic_t *n){
	asm volatile (LOCK_PREFIX "incl %0"
				: "+m" (n->counter));
}

inline void atomic_dec(atomic_t *n){
	asm volatile (LOCK_PREFIX "decl %0"
				: "+m" (n->counter));
}

#endif
