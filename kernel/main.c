#include <printk.h>
#include <vga.h>
#include <timer.h>
#include <idt.h>

int main(){
	init_idt();
	vga_cls();
	//asm volatile("int $0x3");
	//asm volatile("int $0x4");
    init_timer();
	asm volatile("sti");
	while(1);
	//vga_cls();
    //printk("%d%d%d%d-%d%d-%d%d:\nHello,world!",2,0,2,0,0,3,0,6);
}
