// Given a string, print out N most common characters in string
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
// global variables
//
//
char word[MAXWORD];


//typedefs
//
typedef struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
} Treenode;

typedef Treenode * TreeNodePtr;


// function prototypes

TreeNodePtr addtree(TreeNodePtr, char *); //addtree takes root and word to be added
int  getword(char * word, int n); // get new word from input
void treeprint(TreeNodePtr); //print tree recursive down from parameter node
int getch(void);/*get a (possibly pushed back) character*/
void ungetch(int c);/*push character back on input*/


// main routine
//

int main()
{
  TreeNodePtr root = NULL;
  while (getword(word, MAXWORD) != EOF)
    /*addtree(root, word);*/

  return 0;
}


//function implementations

//addree: add a node with our word, at or below node p (parent), and return pointer to it

TreeNodePtr addtree(TreeNodePtr p, char *w)
{
  int cond;

  if (p = NULL) { //we recurse through the tree, not finding a word--eventually hit a null pointer. Hence, a new word has arrived 
    p = (TreeNodePtr) malloc (sizeof(Treenode));
    p->word = w;
    p->count=1;
    p->left = p->right = NULL;  
  }
  else if ((cond = strcmp(w, p->word) == 0)) 
    p->count++;  //repeated word

  else if ((cond = strcmp(w, p->word) < 0)) 
    p->left = addtree(p->left, w);
  else if  ((cond = strcmp(w, p->word) > 0)) 
    p->right = addtree(p->right, w);
  return p;
}

void treeprint(TreeNodePtr r) 
{
  treeprint(r->left);
  printf("%4d %s \n", r->count, r->word);
  treeprint(r->right); 
}


int getword(char *word, int lim) {

    char *w = word;
    int c;

    while (isspace(c = getch())) {
    }
    if (c != EOF) {
        *w++ = c;
    }
    // This point is reached
    if (!isalpha(c)) {
        // This point is never reached before Ctrl+D
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

  int getch(void) /*get a (possibly pushed back) character*/
{
return (bufp>0) ? buf[--bufp] : getchar();
}


void ungetch(int c)/*push character back on input*/
{
if(bufp>BUFSIZE)
printf("ungetch: too many characters.\n");
else
buf[bufp++] = c;
}



