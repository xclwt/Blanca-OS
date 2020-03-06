#include <vga.h>
#include <string.h>
#include <reg_io.h>

/*光标*/
position cursor;
/*显存区域*/
vga_char* vga_memory = (vga_char*) 0xb8000;

/*移动光标*/
void move_cursor(){
    uint16_t cursor_pos = cursor.y * 80 + cursor.x;
    
    /*指定光标高8位*/
    outb(0x3d4,0xe);
    outb(0x3d5,cursor_pos >> 8);
    /*指定光标低8位*/
    outb(0x3d4,0xf);
    outb(0x3d5,cursor_pos);
}

/*滚动屏幕*/
void vga_scroll(){
    if(cursor.y >= 25){
        memmove(vga_memory, vga_memory + 80, 160 * 24);
        memset(vga_memory + 80 * 24, 0, 160);
        cursor.y = 24;
    }
}

/*打印字符*/
void vga_putchar_color(char ch, uint8_t back_color, uint8_t fore_color){
    uint8_t color = (back_color << 4) | (fore_color);
    
    if(ch == '\b'){
        cursor.y -= (cursor.x) ? 0 : 1;
        cursor.x = (cursor.x + 80 - 1) % 80;
        vga_memory[cursor.x + 80 * cursor.y].ch = ' ';
        vga_memory[cursor.x + 80 * cursor.y].color = color;
    }else if(ch == '\n'){
        cursor.x = 0;
        cursor.y++;
    }else if(ch == '\r'){
        cursor.x = 0;
    }else if(ch == '\t'){
        do{
            vga_putchar_color(' ', back_color, fore_color);
        }while(cursor.x % 4);
    }else{
        vga_memory[cursor.x + 80 * cursor.y].ch = ch;
        vga_memory[cursor.x + 80 * cursor.y].color = color;
        cursor.y += (cursor.x + 1) / 80;
        cursor.x = (cursor.x + 1) % 80;
    }
    
    vga_scroll();
    move_cursor();
}       

/*清屏*/
void vga_cls(){
    vga_char blank = {' ',(COL_BLACK << 4) | COL_L_GREY};
    
    for(int y = 0; y < 25; y++){
        for(int x = 0; x < 80; x++){
            vga_memory[x + 80 * y] = blank;
        }
    }
    
    cursor.x = 0;
    cursor.y = 0;
    move_cursor();
}

/*打印缓冲区的字符串，默认黑底灰字*/
void vga_write(char *buf){
    while(*buf){
        vga_putchar_color(*buf++, COL_BLACK, COL_L_GREY);
    }
}

/*打印缓冲区字符串，指定颜色*/
void vga_write_color(char* buf, uint8_t back_color, uint8_t fore_color){
    while(*buf){
        vga_putchar_color(*buf++, back_color, fore_color);
    }
}

position get_cursor(){
    return cursor;
}

void set_cursor(int x, int y){
    if(x < 0 || x >= 80 || y < 0 || y >= 25){
        return;
    }
    
    cursor.x = x;
    cursor.y = y;
    move_cursor();
}
