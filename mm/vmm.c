#include <vmm.h>

//映射到0x100000
pde_t* pgd_start = (pde_t*)0xfffff000;

//映射到0x101000
pte_t* pte_start = (pte_t*)0xffc00000;


void vmm_init(){
	
}
