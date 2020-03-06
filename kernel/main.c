#include <printk.h>
#include <vga.h>

int main(){
    vga_cls();
    printk("%d%d%d%d-%d%d-%d%d:\nHello,world!",2,0,2,0,0,3,0,6);
}
