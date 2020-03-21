#ifndef _INC_PIC_H
#define _INC_PIC_H

#include <types.h>
#include <reg_io.h>

/*设置8259A芯片*/
void init_pic(void);

/*重新设置8259A芯片*/
void reset_pic(uint32_t intr_num);

#endif
