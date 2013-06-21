#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// queue implementation using singly linked list (non-circular)
//

// singly linked list
typedef struct node {
  struct node *next;
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
  /*after(head, 25, 17);*/
  /*head=before(head, 17, 5);*/
  /*head=before(head, 3, 20);*/
  head=pop(head);

  /*head=delete(head, 25);*/
 
  print_list(head);
  
  return 0;
}



lnode *push(lnode *head, int key)
{

  if (head==NULL) {
    head = (lnode *) malloc(sizeof(lnode));
    head->key=key;
    head->next=NULL;
    return head; 
  }
  else {
    lnode *p = malloc(sizeof(lnode));
    head->next=p;
    p->key=key;
    return head; //returning beginning of queue 
  }


}

lnode *pop(lnode *head)
{
  if (head == NULL) {
    return head;
  }
  lnode *p = head;
  head = head->next;
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
  s->next = p;
  p->key=afterkey;

  return head; 
}

lnode *before(lnode *head, int key, int beforekey) //non trivially different from dlinked case
{
  lnode *s = search(head, key);

  if (s == NULL) {
  return NULL;
  }

  if (s == head)
  {
  lnode *p = malloc(sizeof(lnode));

  p->next = s;
  p->key=beforekey;
  return p;  // new head
  }

  lnode *hb = head;

while(hb->next != s && hb->next != NULL ) {
 hb = hb->next;  
}

  lnode *p = malloc(sizeof(lnode));

  p->next = s;
  hb->next = p; 
  
  p->key=beforekey;
  
  return head; 
}


lnode *search(lnode *head, int key)
{
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

lnode *delete(lnode *head, int key) //again, bit different from dlinked case
{
  lnode *p = search(head, key);

  lnode *hb = head;
  while( hb->next != p && hb->next != NULL ) { //find element immediately before p
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
