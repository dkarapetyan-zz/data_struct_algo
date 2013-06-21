#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// stack implementation using singly linked list (non-circular)
//

// singly linked list
typedef struct node {
    struct node *next;
    int key;
} node;

node *push(node *head, int key);
node *pop(node *head);
node *addafter(node *head, int key, int afterkey);
node *addbefore(node *head, int key, int beforekey);

node *mbefore(node *head, int m);


node *search(node *head, int key);
node *delete(node *head, int key);
node *traverse(node *head);

void print_list(node *head);

int main()
{
    void *head = NULL;
    head = push(head, 3);
    /*head = push(head, 25);*/
    /*addafter(head, 25, 17);*/
    /*addbefore(head, 17, 5);*/
    /*addbefore(head, 3, 20);*/
    /*delete(head, 5);*/

    print_list(head);
    /*printf("%d\n", mbefore(head, 2)->key); */
    return 0;
}



node *push(node *head, int key)
{

    if (head==NULL) {
	head = (node *) malloc(sizeof(node));
	head->key=key;
	head->next=NULL;
	return head; 
    }
    else {
	node *p = malloc(sizeof(node));
	p->next=head;
	p->key=key;
	return p; //returning new head
    }


}

node *pop(node *head)
{
    if (head == NULL) {
	return head;
    }
    node *p = head;
    head = head->next;
    free(p); // free memory that still has data from old popped head
    p = NULL; // avoid program having any dangerous unassigned pointers
    return head; //return new head
}

node *addafter(node *head, int key, int afterkey)
{
    node *s = search(head, key);

    if (s == NULL) {
	return NULL;
    }

    node *p = malloc(sizeof(node));

    p->next = s->next;
    s->next = p;
    p->key=afterkey;

    return p; 
}

node *addbefore(node *head, int key, int beforekey) //non trivially different from dlinked case
{
    node *s = search(head, key);

    if (s == NULL) {
	return NULL;
    }

    node *hb = head;

    while(hb->next != s ) {
	hb = hb->next;  
    }



    node *p = malloc(sizeof(node));

    p->next = s;
    hb->next = p; 

    p->key=beforekey;




    return p; 
}


node *mbefore(node *head, int m)
{
    node *last = head;
    int i;
    for (i = 0; i < m; ++i) {
	if (last->next != NULL)
	    last = last->next;
	else
	    return NULL;
    }
    node *mbptr = head;
    while(last->next != NULL) {
	last = last->next;
	mbptr = mbptr->next;  
    }
    return mbptr;


}





node *search(node *head, int key)
{
    node *p = head;
    if (p == NULL) {
	return NULL;
    }
    for (; ;) {
	if (p->key == key) {

	    return p;
	}
	else if (p->next == NULL)
	    return NULL;

	else
	    p = p->next;

    }
}

node *delete(node *head, int key) //again, bit different from dlinked case
{
    node *p = search(head, key);

    node *hb = head;
    while( hb->next != p ) { //find element immediately before p
	hb = hb->next;  
    }

    if (p == NULL) //don't find node with key
	return NULL;

    else if (p == head) { // handle head of list
	head=p->next;
	free(p);
	return head;
    }


    else if (p->next == NULL) //handle tail of list 
    {


	hb->next = NULL;   
	free(p);
	return head;
    }

    else // handle inside of list
    {
	hb->next = p->next;  
	free(p);
	return head;
    }
}


node *traverse(node *head)

{
    while(head->next != NULL) {
	head = head->next;
    }
    return head;  //now at tail node

}

void print_list(node *head)
{
    if (head == NULL)
    {
	printf("\n\n" "%s\n", "Printing done homie");
	return;
    }
    printf("%d ", head->key);
    head = head->next;
    print_list(head);
}
