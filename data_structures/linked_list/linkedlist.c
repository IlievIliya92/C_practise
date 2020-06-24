#include "linkedlist.h"
#include "string.h"

int list_length(NodePtr head) {
	NodePtr current = NULL;
	int len = 0;
	current = head;

	while (current != NULL) {
		current = current->next;
		len++;
	}

	return len;
}

int list_add_element(NodePtr *head_ref, char *value) {
	NodePtr new_node = NULL;
	int ret = 0;

	new_node = (NodePtr)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		fprintf(stderr, "[%s] Failed to allocate memory!\n", __func__);
		ret = -1;
		goto bail;
	}

	strcpy(new_node->ckey, value);
	new_node->next = *head_ref;
	*head_ref = new_node;

bail:

	return ret;
}

void list_print_elements(NodePtr head_ref) {
	NodePtr current = NULL;

	current = head_ref;
	while (current->next != NULL) {
		fprintf(stdout, "[%s] List element %s \n", __func__, current->ckey);
		current = current->next;
	}

	return;
}

void list_append_element(NodePtr *head_ref, char *value) {
	NodePtr current = NULL;

	current = *head_ref;

	if (current == NULL) {
		list_add_element(head_ref, value);
	} else {
		while (current->next != NULL)
			current = current->next;

		list_add_element(&(current->next), value);
	}

	return;
}

int list_count_occurence(NodePtr head_ref, char *key) {
	NodePtr current = NULL;
	int n = 0;

	current = head_ref;

	while(current->next != NULL){
		if (strcmp(current->ckey, key) == 0)
			n++;

		current = current->next;
	}

	return n;
}

char *list_get_nth(NodePtr head_ref, int index) {
	NodePtr current = NULL;
	int n = 0;

	current = head_ref;

	while(current != NULL){
		if (index == n) {
			return current->ckey;
		}
		n++;

		current = current->next;
	}

	return current->ckey;
}

void list_free(NodePtr head_ref)
{
   NodePtr tmp;

   while (head_ref != NULL)
    {
       tmp = head_ref;
       head_ref = head_ref->next;
       free(tmp);
    }

    return;
}

int list_test(void)
{
	NodePtr head = NULL;

	int occurence = 0;
	char *element_nth;
	int length = 0;
	int ret = 0;
	int i = 0;

	length = list_length(head);
	fprintf(stdout, "[%s] The length of the list is %d \n",__func__, length);

	list_add_element(&head, "test");

	list_append_element(&head, "test2");
	list_append_element(&head, "test4");
	list_append_element(&head, "test5");
	list_add_element(&head, "test3");

	occurence = list_count_occurence(head, "test3");
	fprintf(stdout, "[%s] Occurence of 3 in the list %d times\n",__func__, occurence);

	element_nth = list_get_nth(head, 4);
	fprintf(stdout, "[%s] Element found on position 4 - %s\n",__func__, element_nth);

	list_print_elements(head);

	length = list_length(head);
	fprintf(stdout, "[%s] The length of the list is %d \n",__func__, length);

	list_free(head);
	if (ret == 0) {
		fprintf(stdout, "-success\n");
		return 0;
	} else {
		fprintf(stdout, "-failiure\n");
		return -1;
	}
}