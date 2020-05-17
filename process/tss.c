#include <gdt.h>
#include <tss.h>
#include <printk.h>

static tss_t tss;

static gdt_entry_t* gdt = (gdt_entry_t*)0xc0001100;

void gdt_refresh(gdt_ptr lgdt_op){
	asm volatile ("lgdt %0"::"m"(lgdt_op));
}

void tss_install(uint32_t sele_tss){
	asm volatile ("ltr %%ax"::"a"(sele_tss));
}

void set_tss_esp(task_struct* thread){
	tss.esp0 = ((uint32_t)thread + PAGE_SIZE);
}

void make_gdt_desc(uint32_t num, uint32_t addr, uint32_t limit, uint8_t authority, uint8_t flags){
	gdt[num].base_low = addr;
	gdt[num].limit_low = limit;
	gdt[num].base_mid = addr >> 16;
	gdt[num].authority = authority;
	gdt[num].limit_high = limit >> 16;
	gdt[num].flags = flags;
	gdt[num].base_high = addr >> 24;
}

void tss_init(){
	printk("init tss");

	memset(&tss, 0, sizeof(tss_t));
	tss.ss0 = SELE_K_STACK;
	set_tss_esp(cur_thread());
	tss.iomap_off = sizeof(tss_t);

	make_gdt_desc(SELE_TSS >> 3, (uint32_t)(&tss), sizeof(tss_t) - 1, TSS_AUTHORITY, TSS_FLAG);
	make_gdt_desc(SELE_U_CODE >> 3, 0, 0xfffff, CODE_AUTHORITY, GDT_FLAG);
	make_gdt_desc(SELE_U_DATA, 0, 0xfffff, CODE_AUTHORITY, GDT_FLAG);

	gdt_ptr lgdt_op = {8 * 7 - 1, 0xc0001100};
	gdt_refresh(lgdt_op);
	tss_install(SELE_TSS);
}
