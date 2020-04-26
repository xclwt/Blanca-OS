#include <thread.h>

task_struct* idle_thread;
list2d ready_list;
list2d all_list;

extern void switch_to(task_struct* cur, task_struct* new);

void kernel_thread(thread_func* func, void* func_arg){
	func(func_arg);
}

void init_thread(task_struct* thread, char* name, uint8_t priority){
	memset(thread, 0, sizeof(*thread));
	strcpy(thread->name, name);
	thread->status = TASK_RUNNING;
	thread->priority = priority;
	thread->context = (uint32_t*)((uint32_t)thread + PAGE_SIZE);
}

void create_thread(task_struct* thread, thread_func* func, void* func_arg){
	thread->context -= sizeof(regs_t);
	thread->context -= sizeof(context);
	context* kthread_stack = (context*)thread->context;
	kthread_stack->ebp = 0;
	kthread_stack->ebx = 0;
	kthread_stack->edi = 0;
	kthread_stack->esi = 0;
	kthread_stack->eip = kernel_thread;
	kthread_stack->func = func;
	kthread_stack->func_arg = func_arg;
}

task_struct* cur_thread(){
	return NULL;
}
