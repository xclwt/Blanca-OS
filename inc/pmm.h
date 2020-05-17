/*
----------------------
|                    |
|	ZONE_HIGHMEM     |
|                    |
----------------------  <--3GB+896MB
|	                 |
|	内核可用物理页   |
|                    |
----------------------  <--pmm_addr_start
|                    |
|	物理页数组       |
|                    |
----------------------  <--p_pages
|	                 |
|	内核镜像         |
|                    |
----------------------  <--3GB+1MB
|                    |
----------------------  <--3GB
|                    |
|	用户空间         | 
|                    |
----------------------
*/

#ifndef _INC_PMM_H
#define _INC_PMM_H

#include <types.h>
#include <list.h>
#include <idt.h>

/*e820获得的地址范围描述符最大数量,其实已经知道是6个，
这里为了适应不同内存大小，暂且设20个*/
#define MMAP_MAX 20

#define KERNEL_BASE 0xc0000000

#define PAGE_SHIFT 12

//页对齐地址
#define PAGE_ALIGN 0xfffff000

//物理页框大小（4KB）
#define PAGE_SIZE 0x1000

#define ZONE_NORMAL_ADDR 0x1000000    // 16MB
#define ZONE_HIGHMEM_ADDR 0x38000000  // 896MB

#define PAGE_FREE 0
#define PAGE_USED 1

#define set_page_free(page) page->flag = PAGE_FREE
#define set_page_used(page) page->flag = PAGE_USED
#define is_page_free(page) page->flag == PAGE_FREE ? TRUE : FALSE

/*内核镜像末尾*/
//extern uint8_t KERNEL_END; 
#define KERNEL_END 0xc0050000
/*地址范围描述符*/
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

/*物理页结构体*/
typedef struct{
	list_node list;
	atomic_t count;
	uint32_t order;
	uint32_t flag;
}page_t;

/*内存管理器，可更换算法*/
typedef struct{
	char *name;
	void (*init_pages)(page_t* pages, uint32_t n);
	uint32_t (*alloc_pages)(uint32_t n);
	void (*free_pages)(uint32_t addr,uint32_t n);
	uint32_t (*free_pages_count)(void);
}p_manager;

page_t* addr2page(uint32_t addr);

uint32_t page2addr(page_t* page);

/*初始化物理内存管理器*/
void init_pmm();

/*初始化物理页结构体*/
void init_pages_dir(mmap_t* mmap);

/*初始化物理页*/
void init_pages(page_t* pages, uint32_t n);

/*分配物理页*/
uint32_t alloc_pages(uint32_t n);

/*释放物理页*/
void free_pages(uint32_t addr,uint32_t n);

/*空闲页数量*/
uint32_t free_pages_count(void);

uint32_t alloc_pages(uint32_t n);

void free_pages(uint32_t addr,uint32_t n);

#endif
