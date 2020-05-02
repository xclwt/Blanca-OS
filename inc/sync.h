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

/*根据IF位决定是否要关中断*/
bool _temp_disable_intr(void);

/*根据flag决定是否开中断*/
void enable_intr(bool flag);

#define temp_disable_intr(x) x = _temp_disable_intr()

#endif
