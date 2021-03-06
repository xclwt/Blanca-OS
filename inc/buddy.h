#ifndef _INC_BUDDY_H
#define _INC_BUDDY_H

#include <pmm.h>
#include <atomic.h>
#include <list.h>
#include <types.h>
#include <debug.h>

/*初始化物理页*/
void buddy_init_pages(page_t* pages, uint32_t n);

/*分配物理页*/
uint32_t buddy_alloc_pages(uint32_t n);

/*释放物理页*/
void buddy_free_pages(uint32_t addr,uint32_t n);

/*空闲页数量*/
uint32_t buddy_free_pages_count(void);

extern p_manager buddy_manager;

#endif
