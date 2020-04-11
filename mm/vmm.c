#include <vmm.h>

//映射到0x100000
pde_t* pgd_start = (pde_t*)0xfffff000;

//映射到0x101000
pte_t* pte_start = (pte_t*)0xffc00000;

void vmm_init(){
	uint32_t pgd_index = pde_index(KERNEL_BASE);
	
	for(uint32_t i = pgd_index; i < pgd_index + PDE_COUNT; ++i){
		pgd_start[i] = ((i - pgd_index) << 22) | PAGE_P | PAGE_W | PAGE_S;
	}

	for(uint32_t i = 0; i < PDE_COUNT * PTE_COUNT; ++i){
		pte_start[i] = (i << 12) | PAGE_P | PAGE_W | PAGE_S;
	}

	switch_pgd(KERNEL_BASE);
}

void map(pde_t* cur_pgd, uint32_t vaddr, uint32_t paddr, uint32_t flag){
	uint32_t pgd_index = pde_index(vaddr);
	uint32_t pte_index = pte_index(vaddr);

	pte_t* pte = (pte_t*)(cur_pgd[pgd_index] & PAGE_ALIGN);
	if(!pte){
		if(vaddr < KERNEL_BASE){
			pte = (pte_t*)alloc_pages(1);
			memset(pte, 0, PAGE_SIZE);
			cur_pgd[pgd_index] = (uint32_t)pte | PAGE_P | flag;
		}else{
			pte = (pte_t*)(pgd_start[pgd_index] & PAGE_ALIGN);
			cur_pgd[pgd_index] = (uint32_t)pte | PAGE_P | flag;
			return;
		} 
	}

	pte[pte_index] = (paddr & PAGE_ALIGN) | flags;
	
	refresh_page(vaddr);
}

void unmap(pde_t* cur_pgd, uint32_t vaddr){
	uint32_t pgd_index = pde_index(vaddr);
	uint32_t pte_index = pte_index(vaddr);

	pte_t* pte = (pte_t*)(cur_pgd[pgd_index] & PAGE_ALIGN);
	
	if(!pte){
		return;
	}
	
	pte = (pte_t*)(paddr2kaddr(pte));
	pte[pte_index] = 0;

	refresh_page(vaddr);
}
