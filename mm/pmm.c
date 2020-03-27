#include <pmm.h>
#include <string.h>
p_manager* manager = &buddy_manager;

page_t* p_pages = (page_t*)(uint32_t)KERNEL_END + KERNEL_BASE + KPAGE_SIZE;

uint32_t p_pages_count;

void init_pmm(){
	mmap_t* mmap = (mmap_t*)0x500;
	init_p_pages(mmap);	
	init_pages(p_pages, p_pages_count);
}

void init_pages_dir(mmap_t* mmap){
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

void init_pages(page_t *pages, uint32_t n){
	manager->init_pages(pages, n);
}

uint32_t alloc_pages(uint32_t){

}

void free_pages(uint32_t addr, uint32_t n){

}
