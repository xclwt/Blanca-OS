#ifndef _INC_PRINTK_H
#define _INC_PRINTK_H

#include <types.h>
#include <stdarg.h>
#include <vga.h>

int atoi(const char *s);
char* itoa(int value, char *str, int radix);
char* uitoa(uint32_t value, char *str, int radix);
void vsprint(char *buf, const char *fmt, va_list args);
void printk(const char * fmt, ...);
void printk_color(uint8_t back_color, uint8_t fore_color, const char *fmt, ...);

#endif
