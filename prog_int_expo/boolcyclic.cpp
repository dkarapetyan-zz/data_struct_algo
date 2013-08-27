#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    struct node *next;
    int key;
} node;

typedef enum { false=0, true=1 } bool;

bool cyclic(node *head);
bool cyclicopt(node *head);


int main()
{
    node *head = malloc(sizeof(node));
    head->next = malloc(sizeof(node));
    head->next->next = head;  

    printf("%d\n", cyclic(head));
    return 0;
}

/*determine if singly linked list is cyclic*/
/*O(n^2) algorithm using single pointer--check every node before
 * node k to see if next node of k cycles back to one of k-1 nodes*/


bool cyclic(node *head)
{

    node *i = head;
    node *p = head;
    while(p) {
	if (p->next == NULL ) 
	    return false;

	else
	{	
	    for(; i != p; i = i->next ) {
		if (i->next == p )
		    return true;

	    }
	    p = p->next;

	}
    }




}


bool cyclicopt(node *head) { // check to see if list is cyclic. O(n) algorithm using two pointers
    node *slow = head;
    node *fast = head->next;

    if (head == NULL)  //trivial case of empty list
	return false;


    while (fast != slow)  // do we reach NULL first, or fast==slow
    { 

	if (fast == NULL  || fast->next == NULL )  //base case
	    return false;

	else { // advance pointers
	    slow = slow->next;
	    fast = fast->next->next;  
	}
    }
    return true; // if we exit while loop without a return, then fast == slow, which implies cyclic
}
