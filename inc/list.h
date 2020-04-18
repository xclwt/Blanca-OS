#ifndef _INC_LIST_H
#define _INC_LIST_H

#include <types.h>
#include <sync.h>

struct list_node{
	struct list_node *prev, *next;
};

typedef struct list_node list_node;

void init_list_head(list_node* head){
	head->prev = head;
	head->next = head;
}

void list_insert_before(list_node* new, list_node* cur){
	bool flag;
	temp_disable_intr(flag);
	new->prev = cur->prev;
	(cur->prev)->next = new;
	new->next = cur;
	cur->prev = new;
	enable_intr(flag);
}

void list_insert_after(list_node* new, list_node* cur){
	bool flag;
	temp_disable_intr(flag);
	new->next = cur->next;
	(cur->next)->prev = new;
	new->prev = cur;
	cur->next = new;
	enable_intr(flag);
}

void list_del(list_node* cur){
	bool flag;
	temp_disable_intr(flag);
	(cur->prev)->next = cur->next;
	(cur->next)->prev = cur->prev;
	enable_intr(flag);
}

bool list_empty(list_node* head){
	return head->next == head;
}

/*双向链表结构*/
typedef struct list{
	list_node head;
	list_node tail;
}list2d;

void init_list2d(list2d* list){
	list->head.prev = NULL;
	list->head.next = &(list->tail);
	list->tail.prev = &(list->head);
	list->tail.next = NULL;
}

/*添加元素到链表首*/
void list2d_push(list2d* list, list_node* new){
	list_insert_before(new, list->head.next);
}

/*添加元素到链表尾*/
void list2d_append(list2d* list, list_node* new){
	list_insert_after(new, list->tail.prev);
}

/*弹出链表的第一个元素*/
list_node* list2d_pop(list2d* list){
	list_node* result = list->head.next;
	list_del(result);
	return result;
}

bool find_elem(list2d* list, list_node* obj){
	list_node* cur = list->head.next;
	
	while(cur != &(list->tail)){
		if(cur == obj){
			return TRUE;
		}

		cur = cur->next;
	}

	return FALSE;
}

uint32_t list2d_len(list2d* list){
	list_node* cur = list->head.next;
	uint32_t length = 0;
	
	while(cur != &list->tail){
		++length;
		cur = cur->next;
	}

	return length;
}

#endif

