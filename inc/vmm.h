#ifndef _INC_VMM_H
#define _INC_VMM_H

#include <types.h>
#include <asm.h>

#define KERNEL_BASE 0xc0000000  //内核基址
#define KPAGE_SIZE 0x400000		//内核页表大小

#define pde_index(vaddr) (vaddr >> 22) & 0x3ff
#define pte_index(vaddr) (vaddr >> 12) & 0x3ff

typedef uint32_t pde_t;
typedef uint32_t pte_t;

#endif
