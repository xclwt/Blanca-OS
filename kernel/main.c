#include <printk.h>
#include <vga.h>

int main(){
	init_idt();
	asm volatile("int $0x3");
	asm volatile("int $0x4");
    while(1);
	//vga_cls();
    //printk("%d%d%d%d-%d%d-%d%d:\nHello,world!",2,0,2,0,0,3,0,6);
}
