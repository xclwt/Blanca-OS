#include "../inc/types.h"

#define is_digit(ch) (ch >= '0' && ch <= '9')

int atoi(const char *s){
    int i = 0;
    
    while(is_digit(*s)){
        i = i * 10 + *(s++) - '0';
        printf("%d\n",i);
    }
    
    return i;
}

char* itoa(int value, char *str, int radix){
    char reverse[36];
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

void vsprint(char *buf, const char *fmt, va_list args){
    
}
