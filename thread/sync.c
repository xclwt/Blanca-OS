#include <sync.h>

void init_semaphore(semaphore *sig){
	sig->value = SEMA_FREE;
	init_list2d(&(sig->in_waiting));
}

void init_mutex(mutex_lock* mutex){
	mutex->holder = NULL;
	init_semaphore(&(mutex->sig));
	mutex->request_num = 0;
}

void sema_busy(semaphore* sig){
	bool flag;
	temp_disable_intr(flag);

	if(sig->value == SEMA_BUSY){
		list2d_append(&(sig->in_waiting), &(cur_thread()->ready_list_node));
		block_thread(TASK_BLOCKED);
	}

	sig->value = SEMA_BUSY;
	enable_intr(flag);
}

void sema_free(semaphore* sig){
	bool flag;
	temp_disable_intr(flag);
	
	if(!list2d_empty(&(sig->in_waiting))){
		task_struct* thread_blocked = elem2entry(task_struct, ready_list_node, list2d_pop(&(sig->in_waiting)));
		unblock_thread(thread_blocked);
	}

	sig->value = SEMA_FREE;

	enable_intr(flag);
}

void acquire_mutex(mutex_lock* mutex){
	if(mutex->holder != cur_thread()){
		sema_busy(&(mutex->sig));		//信号量设为忙碌
		mutex->holder = cur_thread();	//将互斥锁持有者设为当前任务
		mutex->request_num = 1;			//初始化互斥锁申请次数为1
	}else{
		++mutex->request_num;			//互斥锁申请次数加1
	}
}

void release_mutex(mutex_lock* mutex){
	if(mutex->request_num > 1){
		--mutex->request_num;			//互斥锁申请次数减1
		return;
	}else{
		--mutex->request_num;			
		mutex->holder = NULL;			//清空持有者
		sema_free(&(mutex->sig));		//信号量设为空闲
	}
}
