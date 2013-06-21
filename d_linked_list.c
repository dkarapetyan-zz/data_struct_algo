#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// stack implementation using doubly linked list (non-circular)
//

// doubly linked list
typedef struct node {
  struct node *next;
  struct node *prev;
  int key;
} lnode;

lnode *push(lnode *head, int key);
lnode *pop(lnode *head);
lnode *after(lnode *head, int key, int afterkey);
lnode *before(lnode *head, int key, int beforekey);

lnode *search(lnode *head, int key);
lnode *delete(lnode *head, int key);
lnode *traverse(lnode *head);

void print_list(lnode *head);

int main()
{
  void *head = NULL;
  head = push(head, 3);
  head = push(head, 25);
  after(head, 25, 17);
  before(head, 3, 6);
  before(head, 6, 5);
 
  print_list(head);
  
  return 0;
}



lnode *push(lnode *head, int key)
{

  if (head==NULL) {
    head = (lnode *) malloc(sizeof(lnode));
    head->key=key;
    head->next=NULL;
    head->prev = NULL;
    return head; 
  }
  else {
    lnode *p = malloc(sizeof(lnode));
    p->next=head;
    p->prev=NULL;
    head->prev =p;
    p->key=key;
    return p; //returning new head
  }


}

lnode *pop(lnode *head)
{
  if (head == NULL) {
    return head;
  }
  lnode *p = head;
  head = head->next;
  head->prev = NULL;
  free(p); // free memory that still has data from old popped head
  p = NULL; // avoid program having any dangerous unassigned pointers
  return head; //return new head
}

lnode *after(lnode *head, int key, int afterkey)
{
  lnode *s = search(head, key);

  if (s == NULL) {
  return NULL;
  }

  lnode *p = malloc(sizeof(lnode));
  
  p->next = s->next;
  p->prev = s;
  
  s->next->prev = p;
  s->next = p;

  p->key=afterkey;
  return p; 
}

lnode *before(lnode *head, int key, int beforekey)
{
  lnode *s = search(head, key);

  if (s == NULL) {
  return NULL;
  }

  lnode *p = malloc(sizeof(lnode));

  p->next = s;
  p->prev = s->prev;

  s->prev->next = p;
  s->prev = p;

  p->key=beforekey;
  



  return p; 
}


lnode *search(lnode *head, int key)
{
  int i;
  lnode *p = head;
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

lnode *delete(lnode *head, int key)
{
  lnode *p = search(head, key);

  if (p == NULL) //don't find node with key
    return NULL;

  else if (p == head) { // handle head of list
    head=p->next;
    if (p->next != NULL) //otherwise, head is the only element 
    { 
      p->next->prev = NULL; // would cause a segfault is p->next == NULL
      free(p);
    } 
    return head;
  }
  else if (p->next == NULL) //handle tail of list 
  {
    p->prev->next=p->next;
    free(p);
    return head;
  }

  else // handle inside of list
  {
    p->prev->next=p->next;
    p->next->prev= p->prev;   
    free(p);
    return head;
  }


}


lnode *traverse(lnode *head)

{
  while(head->next != NULL) {
    head = head->next;
  }
  return head;  //now at tail node

}

void print_list(lnode *head)
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
