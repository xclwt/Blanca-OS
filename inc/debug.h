#ifndef _INC_DEBUG_H
#define _INC_DEBUG_H

#include <types.h>
#include <stab.h>
#include <printk.h>
#include <asm.h>

#define assert(condition, info)                           \
		if(!(condition)){                                 \
			panic(__FILE__, __LINE__, __func__, info);    \
		}                                                 \

typedef struct{
    const char *eip_file;		// eip指向的源代码文件
	int eip_line;			    // eip指向的源代码行号

	const char *eip_func_name;	// 包含eip的函数

	int eip_func_namelen;		// 函数名长度
	uintptr_t eip_func_addr;	// 函数起始地址
	int eip_func_narg;		    // 函数参数数量
}debug_info;


/*二分法查找函数名*/
void binsearch_symbol(const Stab *stab, uint32_t *left, uint32_t *right, uint32_t type, uintptr_t addr);

/*利用eip中的地址确定函数名*/
const char* elf_debug(uintptr_t eip, debug_info *info);

/*打印调用栈信息*/
void print_stack_trace(void);

/*内核发生致命错误后调用*/
void panic(const char *file, uint32_t line, const char *func, const char *msg);

#endif
