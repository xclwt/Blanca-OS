#ifndef _INC_VMM_H
#define _INC_VMM_H

#include <types.h>
#include <asm.h>
#include <pmm.h>
#include <string.h>

#define KERNEL_BASE 0xc0000000  //内核基址
#define KPAGE_SIZE 0x400000		//内核页表大小

#define pde_index(vaddr) (vaddr >> 22)
#define pte_index(vaddr) (vaddr >> 12)

#define PHY_MEM_LENGTH 0x38000000
#define PAGE_DIR_SIZE 0x400000
#define PDE_COUNT (PHY_MEM_LENGTH / PAGE_DIR_SIZE) 
#define PTE_COUNT (PAGE_SIZE / sizeof(uint32_t))

#define PAGE_P 0x1
#define PAGE_R 0x0
#define PAGE_W 0x2
#define PAGE_S 0x0
#define PAGE_U 0x4

typedef uint32_t pde_t;
typedef uint32_t pte_t;

#endif
