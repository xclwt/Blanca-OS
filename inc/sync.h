#ifndef _INC_SYNC_H
#define _INC_SYNC_H

#include <asm.h>
#include <types.h>
#include <processor.h>
#include <list.h>
#include <thread.h>
#include <idt.h>

typedef struct{
	uint8_t value;
	list2d in_waiting;
}semaphore;

typedef struct{
	task_struct* holder;
	semaphore sig;
	uint32_t request_num;
}mutex_lock;

#define elem2entry(entry_type, elem_name, elem) ((entry_type*)((char*)(elem) - (uint32_t)&(((entry_type*) 0)->elem_name)))

#endif
