#include <timer.h>

uint32_t tick = 0;

void timer_handler(regs_t *regs){
	tick++;
	printk_color(COL_BLACK, COL_RED, "%d\n", tick);
}

void init_timer(){
	register_intr_handler(IRQ0, timer_handler);

	outb(COUNTER_PORT, (uint8_t)(COUNTER_NUM << 6 | RW << 4 | COUNTER_MODE << 1 | BCD));
	outb(COUNTER_PORT, (uint8_t)COUNTER_VALUE);
	outb(COUNTER_PORT, (uint8_t)COUNTER_VALUE >> 8);
}
