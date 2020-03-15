#ifndef _INC_PIC_H
#define _INC_PIC_H

#include <types.h>
#include <reg_io.h>

/*设置8259A芯片*/
void init_interrupt_chip(void);

/*重置8259A芯片*/
void clear_interrupt_chip(uint32_t intr_num);

#endif
