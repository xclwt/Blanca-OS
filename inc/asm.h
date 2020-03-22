#ifndef INC_REG_IO_H
#define INC_REG_IO_H

#include <types.h>

/*端口写一个字节*/
void outb(uint16_t port, uint8_t index);

/*端口读一个字节*/
uint8_t inb(uint16_t port);

/*关中断*/
void cli();

/*开中断*/
void sti();

/*暂停*/
void hlt();



#endif
