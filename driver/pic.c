#include <pic.h>

#define MASTER_IO1 0x20
#define SLAVE_IO1 0xa0
#define MASTER_IO2 0x21
#define SLAVE_IO2 0xa1

/*设置8259A芯片*/
void init_pic(void){

    outb(MASTER_IO1, 0x11); //初始化主片：10001
    outb(MASTER_IO2, 0x20); //主片IRQ从0x20开始
    outb(MASTER_IO2, 0x04); //主片IR2引脚连接从片
    outb(MASTER_IO2, 0x01); //主片按x86方式工作
    
    outb(SLAVE_IO1, 0x11); //初始化从片：10001    
    outb(SLAVE_IO2, 0x28); //从片IRQ从0x28开始
    outb(SLAVE_IO2, 0x02); //从片输出引脚和主片IR2引脚连接
    outb(SLAVE_IO2, 0x01); //从片按x86方式工作
    
    outb(MASTER_IO2, 0x0); //主片允许中断
    outb(SLAVE_IO2, 0x0); //从片允许中断
}

/*重新设置8259A芯片*/
void reset_pic(uint32_t intr_num){
	if(intr_num >= 40){
		outb(SLAVE_IO1, 0x20); //向从片发送EOI
	}

	outb(MASTER_IO1, 0x20); //向主片发送EOI  
}
