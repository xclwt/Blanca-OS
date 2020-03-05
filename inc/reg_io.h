#ifndef INC_REG_IO_H
#define INC_REG_IO_H

#include <types.h>

/*端口写一个字节*/
inline void outb(uint16_t port, uint8_t index);

/*端口读一个字节*/
inline uint8_t inb(uint16_t port)

#endif
