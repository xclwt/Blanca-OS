#include <debug.h>
/*
extern const Stab _STAB_BEGIN_[];
extern const Stab _STAB_END_[];
extern const char _STABSTR_BEGIN_[];
extern const char _STABSTR_END_[];

void binsearch_symbol(const Stab *stab, uint32_t *left, uint32_t *right, uint32_t type, uintptr_t addr){
    uint32_t l = *left, r = *right, l_matched = 0, r_matched = 0;
    
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

const char* elf_debug(uintptr_t eip, debug_info *info){
    return 0;
}*/

/*打印调用栈信息*/
/*void print_stack_trace(void){
    uint32_t *ebp, *eip;
    debug_info info;
    
    //asm volatile ("mov %%ebp, ebp");
    
    while(ebp){
        eip = ebp + 1;
        elf_debug((uintptr_t)eip, &info);
        printk("[0x%x] : %s\n", info.eip_func_addr, info.eip_func_name);
        ebp = (uint32_t*)*ebp;
    }
}
*/
/*内核发生致命错误后调用*/
void panic(const char *file, uint32_t line, const char * func, const char *msg){
    cli();

	printk_color(COL_BLACK, COL_RED, "!!! System Panic:!!!\n");
	printk_color(COL_BLACK, COL_RED, "filename:%s\n", file);
	printk_color(COL_BLACK, COL_RED, "line:0x%x\n", line);
	printk_color(COL_BLACK, COL_RED, "function:%s\n", func);
	printk_color(COL_BLACK, COL_RED, "condition:%s", msg);

	//print_stack_trace();
    
    while(1);
}
