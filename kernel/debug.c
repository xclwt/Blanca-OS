#include <stab.h>
#include <debug.h>
#include <printk.h>

extern const Stab _STAB_BEGIN_[];
extern const Stab _STAB_END_[];
extern const char _STABSTR_BEGIN_[];
extern const char _STABSTR_END_[];

void binsearch_symbol(const Stab *stab, int *left, int *right, int type, uintptr_t addr){
    int l = *left, r = *right, l_matched = 0, r_matched = 0
    
    while(l <= r){
        int mid = (l + r) / 2, mid_copy = mid;
        
        while(mid >= l){
            if(stab[mid].type != type){
                mid--;
            }else if(stab[mid].value > addr){
                r = mid - 1;
                *right = mid - 1;
                r_matched = 1;
                break;
            }else{
                l = mid + 1;
                *left = mid;
                l_matched = 1;
                break;
            }
        }
        
        if(mid < l){
            l = mid_copy + 1;
        }
    }
    
    if(!l_matched || !r_matched){
        *right = *left - 1;
    }
}

int elf_debug(uintptr_t eip, debug_info *info){
    
}

/*打印调用栈信息*/
void print_stack_trace(void){
    
}

/*内核发生致命错误后调用*/
void panic(const char *msg){
    printk("!!! System Panic: %s\n !!!", msg);
    print_stack_trace();
    
    while(1);
}
