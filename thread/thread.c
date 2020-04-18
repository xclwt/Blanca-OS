#include <thread.h>

void init_thread(task_struct* pthread, char* name, uint8_t priority){
	memset(pthread, 0, sizeof(*pthread));
	strcpy(pthread->name, name);
	pthread->status = TASK_RUNNING;
	pthread->priority = priority;
	pthread->context = (uint32_t*)((uint32_t)pthread + PAGE_SIZE);
}
