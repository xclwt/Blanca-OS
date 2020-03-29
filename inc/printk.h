#ifndef _INC_PRINTK_H
#define _INC_PRINTK_H

#include <types.h>
#include <stdarg.h>
#include <vga.h>

/*字符串转换为数字*/
int atoi(const char *s);

/*将十进制有符号数转换为不同进制字符串*/
char* itoa(int value, char *str, int radix);

/*将十六进制无符号数转换为不同进制字符串*/
char* uitoa(uint32_t value, char *str, int radix);

/*将字符串格式化存入缓冲区*/
void vsprint(char *buf, const char *fmt, va_list args);

/*打印字符串*/
void printk(const char * fmt, ...);

/*打印自定义颜色字符串*/
void printk_color(uint8_t back_color, uint8_t fore_color, const char *fmt, ...);

#endif
