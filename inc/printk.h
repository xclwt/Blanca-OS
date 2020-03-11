#ifndef _INC_PRINTK_H
#define _INC_PRINTK_H

#include <types.h>
#include <stdarg.h>

int atoi(const char *s);
char* itoa(int value, char *str, int radix);
char* uitoa(uint32_t value, char *str, int radix);
void vsprint(char *buf, const char *fmt, va_list args);
void printk(const char * fmt, ...);

#endif
