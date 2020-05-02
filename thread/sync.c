#include <sync.h>

bool _temp_disable_intr(void){
	if(read_eflags() & X86_EFLAGS_IF){
		cli();
		return TRUE;
	}

	return FALSE;
}

void enable_intr(bool flag){
	if(flag){
		sti();
	}
}

void init_semaphore(semaphore *sig){
	sig->value = 1;
	init_list2d(&(sig->in_waiting));
}

void init_mutex(mutex_lock* mutex){
	mutex->holder = NULL;
	init_semaphore(&(mutex->sig));
	mutex->request_num = 0;
}


