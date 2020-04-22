#ifndef _INC_TIMER_H
#define _INC_TIMER_H

#include <idt.h>
#include <printk.h>
#include <asm.h>
#include <debug.h>
#include <thread.h>

#define FREQUENCY 100
#define COUNTER_PORT 0x40
#define COUNTER_NUM 0
#define COUNTER_MODE 2
#define COUNTER_VALUE 1193180/FREQUENCY
#define BCD 0
#define RW 3

/*时钟中断处理函数*/
void timer_handler(regs_t *regs);
/*初始化时钟*/
void init_timer();

#endif
