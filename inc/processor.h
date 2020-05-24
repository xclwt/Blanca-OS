#ifndef _INC_PROCESSOR_H
#define _INC_PROCESSOR_H

#define X86_EFLAGS_CF	 0x00000001 // Carry Flag
#define X86_EFLAGS_MPS	 0x00000010 // MPS Flag, always 1
#define X86_EFLAGS_PF	 0x00000004 // Parity Flag
#define X86_EFLAGS_AF	 0x00000010 // Auxillary carry Flag
#define X86_EFLAGS_ZF	 0x00000040 // Zero Flag
#define X86_EFLAGS_SF	 0x00000080 // Sign Flag
#define X86_EFLAGS_TF	 0x00000100 // Trap Flag
#define X86_EFLAGS_IF	 0x00000200 // Interrupt Flag
#define X86_EFLAGS_DF	 0x00000400 // Direction Flag
#define X86_EFLAGS_OF	 0x00000800 // Overflow Flag
#define X86_EFLAGS_IOPL0 0x00000000 // IOPL == 0
#define X86_EFLAGS_IOPL1 0x00001000 // IOPL == 1
#define X86_EFLAGS_IOPL2 0x00002000 // IOPL == 2
#define X86_EFLAGS_IOPL3 0x00003000 // IOPL == 3
#define X86_EFLAGS_IOPL	 0x00003000 // IOPL mask
#define X86_EFLAGS_NT	 0x00004000 // Nested Task
#define X86_EFLAGS_RF	 0x00010000 // Resume Flag
#define X86_EFLAGS_VM	 0x00020000 // Virtual Mode
#define X86_EFLAGS_AC	 0x00040000 // Alignment Check
#define X86_EFLAGS_VIF	 0x00080000 // Virtual Interrupt Flag
#define X86_EFLAGS_VIP	 0x00100000 // Virtual Interrupt Pending
#define X86_EFLAGS_ID	 0x00200000 // CPUID detection flag

#endif
