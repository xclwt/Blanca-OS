#include <pmm.h>

page_t* p_pages = (page_t*)(uint32_t)KERNEL_END + KERNEL_BASE + KPAGE_SIZE;

void init_pmm(){
	mmap_t* mmap = (mmap_t*)0x500;
	init_p_pages(mmap);	
}

void init_p_pages(mmap_t* mmap){
	uint32_t pmm_length = 0;
	
	for(uint32_t i = 0; i < mmap->count; ++i){
		if(mmap->ards[i].base_addr_l + mmap->ards[i].length_l > ZONE_HIGHMEM_ADDR){
			pmm_length = ZONE_HIGHMEM_ADDR;
			break;
		}else if(mmap->ards[i].type == 1){
			pmm_length = mmap->ards[i].base_addr_l + mmap->ards[i].length_l;
		}
	}

	uint32_t pages_mem_length = sizeof(page_t) * (pmm_length / PAGE_SIZE);
	memset(p_pages, 0, pages_mem_length);
	pmm_addr_start = ((uint32_t)KERNEL_END + pages_mem_length) & ALIGN; //considering...

	return;
}
