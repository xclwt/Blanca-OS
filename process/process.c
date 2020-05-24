#include <pmm.h>
#include <thread.h>
#include <vmm.h>
#include <tss.h>
#include <asm.h>
#include <gdt.h>

extern void intr_exit(void);

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

void run_process(void* usr_proc){
	task_struct* cur = cur_thread();
	cur->kstack += sizeof(context);
	regs_t* regs = (regs_t*)cur->kstack;
	regs->cs = SELE_U_CODE;
	regs->ds = SELE_U_DATA;
	regs->es = SELE_U_DATA;
	regs->fs = SELE_U_DATA;
	regs->gs = 0;
	regs->edi = 0;
	regs->esi = 0;
	regs->ebp = 0;
	regs->esp = 0;
	regs->ebx = 0;
	regs->edx = 0;
	regs->ecx = 0;
	regs->eax = 0;
	regs->eip = (uint32_t) usr_proc;
	regs->eflags = (X86_EFLAGS_IOPL0 | X86_EFLAGS_IF | X86_EFLAGS_MPS);
	regs->u_esp = alloc_pages_u(1) + PAGE_SIZE;
	regs->ss = SELE_U_STACK;
	asm volatile ("movl %0,%%esp"::"r"(regs));
	asm volatile ("jmp intr_exit");
}
