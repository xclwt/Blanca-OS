#ifndef _INC_THREAD_H
#define _INC_THREAD_H

#include <types.h>
#include <idt.h>
#include <string.h>
#include <vmm.h>
#include <pmm.h>
#include <debug.h>

typedef void thread_func(void*);

#define STACK_SIZE 0x1000

#define TASK_RUNNING 0
#define TASK_READY   1
#define TASK_BLOCKED 2
#define TASK_WAITING 3
#define TASK_HANGING 4
#define TASK_DIED    5

typedef struct{
	uint32_t ebp;
	uint32_t ebx;
	uint32_t edi;
	uint32_t esi;
	void (*eip)(thread_func* func, void* func_arg);
	uint32_t retaddr;
	thread_func* func;
	void* func_arg;
}context;

typedef struct{
	uint8_t* kstack;
	uint8_t status;
	uint8_t priority;
	uint32_t run_time;
	list_node ready_list_node;
	list_node all_list_node;
	char name[16];
	uint32_t* pgdir;
	uint32_t stack_boundary;
}task_struct;

/*开启一个内核线程*/
void kernel_thread(thread_func* func, void* func_arg);

/*线程初始化*/
void init_thread(task_struct* thread, char* name, uint8_t priority);

/*初始化线程上下文，如果新线程是已经在运行中，则不需要初始化*/
void init_kcontext(task_struct* thread, thread_func* func, void* func_arg);

/*线程调度*/
void schedule();

/*返回当前线程*/
task_struct* cur_thread();

#endif
