#ifndef _INC_TYPE_H
#define _INC_TYPE_H

#define TRUE    1
#define FALSE   0
#define ERROR  -1

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
//typedef long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
//typedef unsigned long uint64_t;

typedef int8_t bool;
typedef uint32_t size_t;
typedef uint32_t uintptr_t;

//原子类型
typedef struct{
	int32_t counter;
}atomic_t;

#endif
