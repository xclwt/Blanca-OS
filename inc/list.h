#ifndef _INC_LIST_H
#define _INC_LIST_H

#include <types.h>
#include <idt.h>

struct list_node{
	struct list_node *prev, *next;
};

typedef struct list_node list_node;

void init_list_head(list_node* head);

void list_insert_before(list_node* new, list_node* cur);

void list_insert_after(list_node* new, list_node* cur);

void list_del(list_node* cur);

bool list_empty(list_node* head);

/*双向链表结构*/
typedef struct{
	list_node head;
	list_node tail;
}list2d;

void init_list2d(list2d* list);

/*添加元素到链表首*/
void list2d_push(list2d* list, list_node* new);

/*添加元素到链表尾*/
void list2d_append(list2d* list, list_node* new);

/*弹出链表的第一个元素*/
list_node* list2d_pop(list2d* list);

bool find_elem(list2d* list, list_node* obj);

uint32_t list2d_len(list2d* list);

#endif

