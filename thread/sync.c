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


