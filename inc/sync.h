#ifndef _INC_SYNC_H
#define _INC_SYNC_H

#include <asm.h>
#include <types.h>
#include <processor.h>

/*根据IF位决定是否要关中断*/
bool _temp_disable_intr(void);

/*根据flag决定是否开中断*/
void enable_intr(bool flag);

#define temp_disable_intr(x) x = _temp_disable_intr()

#endif
