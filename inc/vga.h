#ifndef _INC_VGA_H
#define _INC_VGA_H

#include <types.h>
#include <string.h>
#include <asm.h>

#define COL_BLACK   0
#define COL_BLUE    1
#define COL_GREEN   2
#define COL_CYAN    3
#define COL_RED     4
#define COL_MAGEN   5
#define COL_BROWN   6
#define COL_WHITE   7
#define COL_L_GREY  8
#define COL_L_BLUE  9
#define COL_L_GREEN 10
#define COL_L_CYAN  11
#define COL_L_RED   12
#define COL_L_MAGEN 13
#define COL_L_BROWN 14
#define COL_L_WHITE 15

typedef struct{
    uint32_t x;
    uint32_t y;
} position;

typedef struct{
    char ch;
    uint8_t color;
}vga_char;

/*移动光标*/
void move_cursor();

/*滚动屏幕*/
void vga_scroll();

/*打印字符*/
void vga_putchar_color(char ch, uint8_t back_color, uint8_t fore_color);

/*清屏*/
void vga_cls();

/*打印缓冲区的字符串，默认黑底灰字*/
void vga_write(char *buf);

/*打印缓冲区字符串，指定颜色*/
void vga_write_color(char* buf, uint8_t back_color, uint8_t fore_color);

position get_cursor();

void set_cursor(int x, int y);

#endif
