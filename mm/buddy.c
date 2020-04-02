#include <buddy.h>

#define MAX_ORDER 10

#define list2page(l) ((page_t*)((char*)(l) - (uint32_t)&(((page_t*) 0)->list)))

/*空闲内存块链*/
static list_node free_list[MAX_ORDER + 1];

/*链上空闲内存块数量*/
static atomic_t free_num[MAX_ORDER + 1];

/*物理页总数量*/
static atomic_t phy_pages_count;

/*物理页剩余数量*/
static atomic_t phy_pages_left;

/*物理页起始地址*/
static uint32_t pmm_addr_start;

/*物理页结束地址*/
static uint32_t pmm_addr_end;

/*物理页管理结构起始地址*/
static page_t* pages_start;

/*初始化物理页*/
void buddy_init_pages(page_t* pages, uint32_t n){
	uint32_t order = MAX_ORDER;
	uint32_t size = (1 << order);

	atomic_set(&phy_pages_count, n);
	atomic_set(&phy_pages_left, n);
	pmm_addr_start = page2addr(&pages[0]);
	pmm_addr_end = page2addr(&pages[n - 1]) + PAGE_SIZE;
	pages_start = pages;

	for(uint32_t i = 0; i < MAX_ORDER; ++i){
		init_list_head(free_list[i]);
	}

	while(n){
		while(n >= size){
			pages->order = order;
			list_insert_after(&(pages->list), &free_list[order]);
			n -= order;
			pages += order;
			atomic_inc(&free_num[order]);
		}

		--order;
		size >>= 1;
	}

}

/*计算order值*/
uint32_t get_order(unt32_t n){
	uint32_t order = 0, size = 1;
	
	while(n > size){
		++order;
		size <<= 1;
	}

	return order;
}

/*分配物理页子功能*/
page_t* buddy_alloc_pages_sub(uint32_t order){
	assert(order <= MAX_ORDER, "buddy memory manager can't allocate over 1024 pages!!!");

	for(uint32_t cur = order; order <= MAX_ORDER; ++cur){
		if(free_num[cur] != 0){
			list_node *list = free_list[cur].next;
			list_del(list);
			atomic_dec(free_num[cur]);
			page_t* page = list2page(list);
			uint32_t size = 1 << cur;
			
			while(cur > order){
				--cur;
				size >>= 1;
				(page + size)->order = cur;
				list_insert_after(&(page->list), &free_list[cur]);
				atomic_inc(free_num[cur]);
				page->order = cur;
			}

			return page;
		}
	}

	return 0;
}

/*分配物理页*/
uint32_t buddy_alloc_pages(uint32_t n){
	if(n <= 0 || n > (uint32_t)atomic_read(phy_pages_left)){
		return 0;
	}

	uint32_t order = get_order(n);
	uint32_t size = 1 << order;
	page_t* page = buddy_alloc_pages_sub(order);

	if(!page){
		return 0;
	}

	if(size != n){
		buddy_free_pages(page2addr(page + n), size - n);
	}

	atomic_sub(&phy_pages_left, n);

	return page2addr(page);
}

/*检测buddy page*/
bool is_buddy(){

}


/*释放物理页子功*/
page_t* buddy_free_pages_sub(page_t* page, uint32_t order){
	assert(order <= MAX_ORDER, "buddy memory manager can't free over 1024 pages!!!");
}

/*释放物理页*/
void buddy_free_pages(uint32_t addr,uint32_t n){
	if(n <= 0 || n > (uint32_t)(atomic_read(phy_pages_count) - atomic_read(phy_pages_left)) || n > MAX_ORDER){
		return;
	}

	uint32_t order = 0;
	uint32_t size = 1;
	page_t* page = addr2page(addr);

	atomic_add(phy_pages_left, n);

	while(size < n){
		if((n & size) != 0){
			buddy_free_pages_sub(page, order);
			page += size;
			n -= size;
		}
		++order;
		size <<= 1;
	}
}

/*空闲页数量*/
uint32_t buddy_free_pages_count(void){
	return atomic_read(phy_pages_left);
}

/*可能用到，暂时写在这*/
uint32_t next_pow_of_2(uint32_t x){
	if(!(x & (x - 1)){  // power of 2 or not
	    return x;
	}

	x |= x>>1;
	x |= x>>2;
	x |= x>>4;
	x |= x>>8;
	x |= x>>16;	
	
	return x + 1;
}
