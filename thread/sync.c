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
