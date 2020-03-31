#include <buddy.h>

/*空闲内存块链*/
static list_head free_list[MAX_ORDER + 1];

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
static page_t* pages;

/*初始化物理页*/
void buddy_init_pages(page_t* pages, uint32_t n){

}

/*分配物理页*/
uint32_t buddy_alloc_pages(uint32_t n){

}

/*释放物理页*/
void buddy_free_pages(uint32_t addr,uint32_t n){

}

/*空闲页数量*/
uint32_t buddy_free_pages_count(void){

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