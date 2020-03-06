#include <printk.h>

int x(char t){
    return (int)t;
}

int _start(void){
    int k = x(97);
    printk("%d\n",k);
}
