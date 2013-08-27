#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>




typedef struct node {
    struct node * next;
    struct node * prev;
    struct node * child;
    int key;
} node;


node * head;  
node * tail;



void flatten(void)
{
    if (head == NULL)
	return;

    tail = head;
    while(tail->next  !=NULL ) {
	tail = tail->next;  	 // find tail of starting linked list
    }
    while(head->next != NULL ) {
	if (head->child !=NULL ) { 
	    tail->next = head->child;  // append child node to end of tail 
	}
	while(tail->next != NULL ) {
	    tail = tail->next;  // find new tail
	}

    }
    head = head->next;  // move on to second, third, node, etc in original linked list, and repeat

}



