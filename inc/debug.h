#ifndef _INC_DEBUG_H
#define _INC_DEBUG_H

#include <types.h>


typedef struct{
    const char *eip_file;		// Source code filename for EIP
	int eip_line;			// Source code linenumber for EIP

	const char *eip_func_name;	// Name of function containing EIP

	int eip_func_namelen;		// Length of function name
	uintptr_t eip_func_addr;		// Address of start of function
	int eip_func_narg;		// Number of function arguments
}debug_info;


/*二分法查找函数名*/
void binsearch_symbol(const Stab *stab, uint32_t *left, uint32_t *right, uint32_t type, uintptr_t addr);

/*利用eip中的地址确定函数名*/
const char* elf_debug(uintptr_t eip, debug_info *info);

/*打印调用栈信息*/
void print_stack_trace(void);

/*内核发生致命错误后调用*/
void panic(const char *msg);

#endif
