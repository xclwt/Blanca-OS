#include <stdarg.h>
#include <string.h>
#include <vga.h>

#define is_digit(ch) (ch >= '0' && ch <= '9')

int atoi(const char *s){
    int i = 0;
    
    while(is_digit(*s)){
        i = i * 10 + *(s++) - '0';
    }
    
    return i;
}

char* itoa(int value, char *str, int radix){
    char reverse[32];
    char *p = reverse, *q = str;
    bool positive = (value >= 0) ? TRUE : FALSE;
    value = (value >= 0) ? value : -value;
    *p++ = '\0';
    
    while(value >= 0){
        *p++ = "0123456789abcdef"[value % radix];
        value /= radix;
        if(value == 0) break;
    }
    
    if(!positive) *p = '-';
    else p--;
    
    while(p >= reverse){
        *q++ = *p--;
    }
    
    return str;
}

char* uitoa(uint32_t value, char *str, int radix){
    char reverse[32];
    char *p = reverse, *q = str;
    
    *p++ = '\0';
    
    while(value >= 0){
        *p++ = "0123456789abcdef"[value % radix];
        value /= radix;
        if(value == 0) break;
    }
    
    p--;
    
    while(p >= reverse){
        *q++ = *p--;
    }
    
    return str;
}

void vsprint(char *buf, const char *fmt, va_list args){
    for(;*fmt;fmt++){
        if(*fmt != '%'){
            *buf++ = *fmt;
            continue;
        }
        
        fmt++;
        
        switch(*fmt){
            case 'd':
                itoa(va_arg(args, int), buf, 10);
                buf += strlen(buf);
                break;
            case 'x':
                uitoa(va_arg(args, unsigned int), buf, 16);
                buf += strlen(buf);
                break;
            case 'f':
                break;
            case 'c':
                *buf++ = va_arg(args, char);
                break;
            case 's':
                strcpy(buf, va_arg(args, char*));
                buf += strlen(buf);
                break;
        }
    }
    *buf = 0;
}

void printk(const char * fmt, ...){
    char buf[1024];
    va_list args;
    
    va_start(args, fmt);
    vsprint(buf, fmt, args);
    va_end(args);
    
    vga_write(buf);
}

void printk_color(uint8_t back_color, uint8_t fore_color, const char *fmt, ...){
	char buf[1024];
	va_list args;

	va_start(args, fmt);
	vsprint(buf, fmt, args);
	va_end(args);

	vga_write_color(buf, back_color, fore_color);
}
