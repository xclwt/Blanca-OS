#include <pmm.h>
#include <thread.h>
#include <vmm.h>
#include <tss.h>
#include <asm.h>

void load_pgdir(task_struct* thread){
	uint32_t pgdir_paddr = 0x100000;

	if(thread->pgdir){
		pgdir_paddr = vaddr2paddr((uint32_t)thread->pgdir);
	}

	switch_pgd(pgdir_paddr);
}

uint32_t* create_pgdir(void){
	uint32_t* pgdir = alloc_pages(1);

	if(!pgdir){
		printk("Failed to create_pgdir");
		return NULL;
	}

	return pgdir;
}

void load_progress(task_struct* thread){
	load_pgdir(thread);

	if(thread->pgdir){
		set_tss_esp(thread);
	}
}

void create_progress(void* func_arg, char* name){
	task_struct* thread = alloc_pages(1);
	init_thread(thread, name, 31);
	init_kcontext(thread, start_progress, func_arg);
	thread->pgdir = create_pgdir();
}
