#ifndef _INC_THREAD_H
#define _INC_THREAD_H

#include <types.h>
#include <idt.h>
#include <string.h>
#include <vmm.h>
#include <pmm.h>

typedef void thread_func(void*);

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
	uint8_t* context;
	uint8_t status;
	uint8_t priority;
	uint32_t run_time;
	list_node ready_list_node;
	list_node all_list_node;
	char name[16];
	uint32_t* pgdir;
	uint32_t stack_boundary;
}task_struct;

void kernel_thread(thread_func* func, void* func_arg);

void init_thread(task_struct* thread, char* name, uint8_t priority);

void create_thread(task_struct* thread, thread_func* func, void* func_arg);

task_struct* cur_thread();

#endif
