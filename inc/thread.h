#ifndef _INC_THREAD_H
#define _INC_THREAD_H

#include <types.h>
#include <idt.h>
#include <string.h>
#include <vmm.h>

#define TASK_RUNNING 0
#define TASK_READY   1
#define TASK_BLOCKED 2
#define TASK_WAITING 3
#define TASK_HANGING 4
#define TASK_DIED    5

typedef struct{
	uint32_t esp;
	uint32_t ebp;
	uint32_t ebx;
	uint32_t edi;
	uint32_t esi;
	uint32_t eip;
}context;

typedef struct{
	uint32_t* context;
	uint8_t status;
	uint8_t priority;
	char name[16];
	uint32_t stack_boundary;
}task_struct;

#endif
