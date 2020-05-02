#ifndef _INC_SYNC_H
#define _INC_SYNC_H

#include <asm.h>
#include <types.h>
#include <processor.h>
#include <list.h>
#include <thread.h>

typedef struct{
	uint8_t value;
	list2d in_waiting;
}semaphore;

typedef struct{
	task_struct* holder;
	semaphore sig;
	uint32_t request_num;
}mutex_lock;

#endif
