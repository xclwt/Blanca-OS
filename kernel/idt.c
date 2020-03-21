#include <idt.h>
#include <pic.h>

#define INTR_MAX 256

idt_entry_t idt_entries[INTR_MAX];

idt_ptr_t idt_ptr;

extern void load_idt(uint32_t idt_ptr);

intr_handler_t intr_handler[INTR_MAX];

intr_func_t intr_func[INTR_MAX] = {
    &isr0,  &isr1,  &isr2,  &isr3,  &isr4,  &isr5,  &isr6,  &isr7, 
    &isr8,  &isr9,  &isr10, &isr11, &isr12, &isr13, &isr14, &isr15, 
    &isr16, &isr17, &isr18, &isr19, &isr20, &isr21, &isr22, &isr23, 
    &isr24, &isr25, &isr26, &isr27, &isr28, &isr29, &isr30, &isr31,
    &irq0,  &irq1,  &irq2,  &irq3,  &irq4,  &irq5,  &irq6,  &irq7,
    &irq8,  &irq9,  &irq10, &irq11, &irq12, &irq13, &irq14, &irq15
};

static const char * intr_name[] = {
	"Devide By Zero",
	"Debug",
	"Non-Maskable Interrupt",
	"BreakPoint",
	"Into Detected Overflow",
	"Out Of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception"
};

void init_idt(void){
    init_pic();
    
    idt_ptr.limit = 8 * INTR_MAX - 1;
    idt_ptr.base = (uint32_t)idt_entries;
    
    for(int i = 0; i < 48; ++i){
        set_intr_gate(i, (uint32_t)intr_func[i], 0x08, 0x8e);
    }
    
    set_intr_gate(255, (uint32_t)isr255, 0x08, 0x8e);
    
    load_idt((uint32_t) &idt_ptr);
}

void set_intr_gate(uint8_t index, uint32_t base, uint16_t selector, uint8_t flags){
    idt_entries[index].l_base = base;
    idt_entries[index].h_base = (base >> 16);
    idt_entries[index].selector = selector;
    idt_entries[index].section_0 = 0;
    idt_entries[index].flags = flags;
}

/*
void pagefault(){
	int pagefault_addr = 0;
	asm volatile ("mov %%cr2, %0" : "=r" (pagefault_addr));
	printk("page fault address : 0x%x\n", pagefault_addr);
}
*/

void isr_handler(regs_t *regs){
	intr_handler_t handler = intr_handler[regs->intr_num];
	if(handler){
		handler(regs);
	}
	else{
		printk_color(COL_BLACK, COL_RED, "Unhandled interrupt: %d %s\n:", regs->intr_num, intr_name[regs->intr_num]);
		while(1);
	}
}

void irq_handler(regs_t *regs){
	intr_handler_t handler = intr_handler[regs->intr_num];
	if(handler){
		handler(regs);
	}

	reset(regs->intr_num);
}

void c_isr_stub(regs_t *regs){
	if(regs->intr_num < ISR_IRQ0 || regs->intr_num == ISR_UNKNOWN){
		isr_handler(regs);
	}else if(regs->intr_num < 16 + ISR_IRQ0){
		irq_handler(regs);
	}
}

void register_intr_handler(uint8_t intr_num, intr_handler_t handler){
	intr_handler[intr_num] = handler;
}
