#include <sync.h>

void init_semaphore(semaphore *sig){
	sig->value = 1;
	init_list2d(&(sig->in_waiting));
}

void init_mutex(mutex_lock* mutex){
	mutex->holder = NULL;
	init_semaphore(&(mutex->sig));
	mutex->request_num = 0;
}

void sig_down(semaphore* sig){
	bool flag;
	temp_disable_intr(flag);

	if(sig->value == 0){
		list2d_append(&(sig->in_waiting), &(cur_thread()->ready_list_node));
		block_thread(TASK_BLOCKED);
	}

	++sig->value;
	enable_intr(flag);
}

void sig_up(semaphore* sig){
	bool flag;
	temp_disable_intr(flag);
	
	if(!list2d_empty(&(sig->in_waiting))){
		task_struct* thread_blocked = elem2entry(task_struct, ready_list_node, list2d_pop(&(sig->in_waiting)));
		unblock_thread(thread_blocked);
	}

	++sig->value;

	enable_intr(flag);
}

void acquire_mutex(mutex_lock* mutex){
	if(mutex->holder != cur_thread()){
		sig_down(&(mutex->sig));
		mutex->holder = cur_thread();
		mutex->request_num = 1;
	}else{
		++mutex->request_num;
	}
}

void release_mutex(mutex_lock* mutex){
	if(mutex->request_num > 1){
		--mutex->request_num;
		return;
	}else{
		--mutex->request_num;
		mutex->holder = NULL;
		sig_up(&(mutex->sig));
	}
}
