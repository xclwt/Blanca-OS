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

#define SEMA_FREE 1
#define SEMA_BUSY 0

/*初始化信号量*/
void init_semaphore(semaphore *sig);

/*初始化互斥锁*/
void init_mutex(mutex_lock* mutex);

/*信号量设为忙碌*/
void sema_busy(semaphore* sig);

/*信号量设为空闲*/
void sema_free(semaphore* sig);

/*获取互斥锁*/
void acquire_mutex(mutex_lock* mutex);

/*释放互斥锁*/
void release_mutex(mutex_lock* mutex);

#endif
