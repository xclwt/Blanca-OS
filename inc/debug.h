#ifndef _INC_DEBUG_H
#define _INC_DEBUG_H

#include <types.h>


typedef struct{
    
}debug_info;


/*二分法查找函数名*/
void binsearch_symbol(const Stab *stab, int *left, int *right, int type, uintptr_t addr);

/*利用eip中的地址确定函数名*/
int elf_debug(uintptr_t eip, debug_info *info);

/*打印调用栈信息*/
void print_stack_trace(void);

/*内核发生致命错误后调用*/
void panic(const char *msg);

#endif
