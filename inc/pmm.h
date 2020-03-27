#ifndef _INC_PMM_H
#define _INC_PMM_H

#include <types.h>

/*e820获得的地址范围描述符最大数量,其实已经知道是6个，
这里为了适应不同内存大小，暂且设20个*/
#define MMAP_MAX 20

#define ALIGN 0xfffff000
#define PAGE_SIZE 0x1000


#define ZONE_NORMAL_ADDR 0x1000000    // 16MB
#define ZONE_HIGHMEM_ADDR 0x38000000  // 896MB

typedef struct{
	uint32_t base_addr_l;
	uint32_t base_addr_h;
	uint32_t length_l;
	uint32_t length_h;
	uint32_t type;
}__attribute__((packed)) ards_t;

typedef struct{
	uint32_t count;
	ards_t ards[MMAP_MAX];
}mmap_t;

typedef struct{
	char *name;
	void (*init_pages)(page_t* pages, uint32_t n);
	uint32_t (*alloc_pages)(uint32_t n);
	void (*free_pages)(uint32_t addr,uint32_t n);
}p_manager;

void init_pmm();

void init_pages_dir(mmap_t* mmap);

void init_pages(page_t* pages, uint32_t n);

uint32_t alloc_pages(uint32_t n);

void free_pages(uint32_t addr,uint32_t n);
#endif
