#include <pmm.h>
#include <string.h>
p_manager* manager = &buddy_manager;

page_t* p_pages = (page_t*)(uint32_t)KERNEL_END + KERNEL_BASE;

static uint32_t p_pages_count;

uint32_t pmm_addr_start;

uint32_t pmm_addr_end;

#define vaddr2page(vaddr) (p_pages + (vaddr - pmm_addr_start) >> PAGE_SHIFT)
#define page2vaddr(page) (pmm_addr_start + (uint32_t)(page - p_pages) * PAGE_SIZE)
#define PFN_UP(x) ((x + PAGE_SIZE - 1) >> PAGE_SHIFT)
#define PFN_DOWN(x) (x >> PAGE_SHIFT)

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
		}
		pmm_length += mmap->ards[i].length_l;
	}

	uint32_t pages_mem_length = sizeof(page_t) * (pmm_length / PAGE_SIZE);
	memset(p_pages, 0, pages_mem_length);
	pmm_addr_start = ((uint32_t)KERNEL_END + pages_mem_length + PAGE_SIZE - 1) >> PAGE_SHIFT; //considering...
	
	for(uint32_t i = 0; i < mmap->count; ++i){
		uint32_t addr_start = mmap->ards[i].base_addr_l;
		uint32_t addr_end = mmap->ards[i].base_addr_l + mmap->ards[i].length_l;
		
		if(addr_start < pmm_addr_start){
			addr_start = pmm_addr_start;
		}
		if(addr_end > ZONE_HIGHMEM_ADDR){
			addr_end = ZONE_HIGHMEM_ADDR;
		}

		for(uint32_t i = PFN(addr_start); i < PFN_DOWN(addr_end); ++i){
			++p_pages_count;
		}

		pmm_addr_end = addr_end;
	}

	assert(pmm_addr_start == page2vaddr(&p_pages[0]), "");
	assert(pmm_addr_end == page2vaddr(&p_pages[p_pages_count - 1]), "");

	return;
}

void init_pages(page_t *pages, uint32_t n){
	manager->init_pages(pages, n);
}

uint32_t alloc_pages(uint32_t){

}

void free_pages(uint32_t addr, uint32_t n){

}
