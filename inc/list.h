#ifndef _INC_LIST_H
#define _INC_LIST_H

#include <types.h>

struct list_node{
	struct list_node *prev, *next;
};

typedef struct list_node list_node;

void init_list_head(list_node* head){
	head->prev = head;
	head->next = head;
}

void list_insert_before(list_node* new, list_node* cur){
	new->prev = cur->prev;
	(cur->prev)->next = new;
	new->next = cur;
	cur->prev = new;
}

void list_insert_after(list_node* new, list_node* cur){
	new->next = cur->next;
	(cur->next)->prev = new;
	new->prev = cur;
	cur->next = new;
}

void list_del(list_node* cur){
	(cur->prev)->next = cur->next;
	(cur->next)->prev = cur->prev;
}

bool list_empty(list_node* head){
	return head->next == head;
}

#endif

