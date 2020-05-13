#ifndef _INC_GDT_H
#define _INC_GDT_H

#include <types.h>

/*GDT*/
#define DESC_G_4K	1
#define DESC_D_32	1
#define DESC_L		0
#define DESC_AVL	0
#define DESC_P		1
#define DESC_S_DATA	1
#define DESC_S_SYS	0

#define DESC_TYPE_CODE	8
#define DESC_TYPE_DATA	2
#define DESC_TYPE_TSS	9

#define TI_GDT 0
#define TI_LDT 1

#define DPL_0 0
#define DPL_1 1
#define DPL_2 2
#define DPL_3 3

#define RPL_0 0
#define RPL_1 1
#define RPL_2 2
#define RPL_3 3

#define SELE_K_CODE		(1 << 3) + (TI_GDT << 2) + RPL_0		
#define SELE_K_DATA		(2 << 3) + (TI_GDT << 2) + RPL_0
#define SELE_K_STACK	SELE_K_DATA
#define SELE_K_GS		(3 << 3) + (TI_GDT << 2) + RPL_0
#define SELE_TSS		(4 << 3) + (TI_GDT << 2) + RPL_0
#define SELE_U_CODE		(5 << 3) + (TI_GDT << 2) + RPL_3
#define SELE_U_DATA		(6 << 3) + (TI_GDT << 2) + RPL_3
#define SELE_U_STACK	SELE_U_DATA

#define GDT_FLAG		(DESC_G_4K << 3) + (DESC_D_32 << 2) + (DESC_L << 1) + DESC_AVL
#define CODE_AUTHORITY	(DESC_P << 3) + (DPL_3 << 2) + (DESC_S_DATA << 1) + DESC_TYPE_CODE
#define DATA_AUTHORITY	(DESC_P << 3) + (DPL_3 << 2) + (DESC_S_DATA << 1) + DESC_TYPE_DATA

/*TSS*/
#define DESC_D_TSS		0

#define SELE_TSS		(4 << 3) + (TI_GDT << 2) + RPL_0

#define TSS_FLAG	 	(DESC_G_4K << 3) + (DESC_D_32 << 2) + (DESC_L << 1) + DESC_AVL
#define TSS_AUTHORITY	(DESC_P << 3) + (DPL_0 << 2) + (DESC_S_SYS << 1) + DESC_TYPE_TSS

typedef struct{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t authority;
    uint8_t limit_high:4;
	uint8_t flags:4;
	uint8_t base_high;
}__attribute__((packed)) gdt_entry_t;

typedef struct{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed)) gdt_ptr;

#endif
