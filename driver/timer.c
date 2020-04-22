#include <timer.h>

uint32_t tick = 0;

void timer_handler(regs_t *regs){
	task_struct* cur_thread = cur_thread();
	
	assert(cur_thread->stack_boundary == 0x20000521, "thread stack overflow ！！！");
	++tick;

	if(cur_thread->run_time == 0){
		schedule();
	}else{
		--cur_thread->run_time;
	}
	
	
	//printk_color(COL_BLACK, COL_RED, "%d\n", tick);
}

void init_timer(){
	register_intr_handler(IRQ0, timer_handler);

	outb(COUNTER_PORT, (uint8_t)(COUNTER_NUM << 6 | RW << 4 | COUNTER_MODE << 1 | BCD));
	outb(COUNTER_PORT, (uint8_t)COUNTER_VALUE);
	outb(COUNTER_PORT, (uint8_t)COUNTER_VALUE >> 8);

	printk("timer init...");
}
