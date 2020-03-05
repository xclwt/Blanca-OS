#include <reg_io.h>

inline void outb(uint16_t port, uint8_t index){
    asm volatile ("outb %1, %0"::"d"(port),"a"(index));
}

inline uint8_t inb(uint16_t port){
    uint8_t result;
    
    asm volatile ("inb %1, %0":"=a"(result):"d"(port));
    
    return result;
}
