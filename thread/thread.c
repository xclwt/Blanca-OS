#include <thread.h>

task_struct* main_thread;
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
	thread->kstack = (uint8_t*)((uint32_t)thread + PAGE_SIZE);
	thread->stack_boundary = 0x20000521;
}

void init_kcontext(task_struct* thread, thread_func* func, void* func_arg){
	thread->kstack -= sizeof(regs_t);
	thread->kstack -= sizeof(context);
	context* kcontext = (context*)thread->kstack;
	kcontext->ebp = 0;
	kcontext->ebx = 0;
	kcontext->edi = 0;
	kcontext->esi = 0;
	kcontext->eip = kernel_thread;
	kcontext->func = func;
	kcontext->func_arg = func_arg;
}

task_struct* start_thread(char* name, uint8_t priority, thread_func* func, void* func_arg){
	task_struct *thread = alloc_pages(STACK_SIZE / PAGE_SIZE);
	init_thread(thread, name, priority);
	init_kcontext(thread, func, func_arg);

	list2d_append(&ready_list, &(thread->ready_list_node));
	list2d_append(&all_list, &(thread->all_list_node));
}

void create_main_thread(){
	main_thread = cur_thread();
	init_thread(main_thread, "main", );
	list2d_append(&all_list, &(main_thread->all_list_node));
}

void schedule(){
	return;
}

task_struct* cur_thread(){
	uint32_t esp;
	asm volatile ("mov %%esp, %0":"=r"(esp));
	esp &= ~(STACK_SIZE - 1);
	return (task_struct*)esp;
}

void block_thread(uint8_t status){
	assert((status == TASK_BLOCKED || 
			status == TASK_HANGING || 
			status == TASK_WAITING), 
			"BLOCK_THREAD: STATUS ERROR!!!");
	
	bool flag;
	temp_disable_intr(flag);
	
	task_struct* thread = cur_thread();
	thread->status = status;
	schedule();

	enable_intr(flag);
}

void unblock_thread(task_struct* thread){
	bool flag;
	temp_disable_intr(flag);

	assert((thread->status == TASK_BLOCKED || 
			thread->status == TASK_HANGING ||
			thread->status == TASK_WAITING), 
			"UNBLOCK_THREAD: STATUS ERROR");

	list2d_push(&ready_list, &thread->ready_list_node);

	enable_intr(flag);
}
