#include <atomic.h>

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
