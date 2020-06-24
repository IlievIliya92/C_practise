#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct node {
	char ckey[100];
	struct node *next;
} Node, *NodePtr;

int list_length(NodePtr head);
void list_free(NodePtr head_ref);
int list_add_element(NodePtr *head_ref, char *value);
void list_append_element(NodePtr *head_ref, char *value);
void list_print_elements(NodePtr head_ref);
int list_count_occurence(NodePtr head_ref, char *key);
char *list_get_nth(NodePtr head, int index);

int list_test(void);

#endif /* _LINKEDLIST_H_ */