#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 1000

// hash table implementation of a dictionary
//
//


typedef struct node {
    char *word;
    char *def;
    struct node *next;
} node;

unsigned hash(char *w);
void insert_entry(node *hash_table[], char *w, char *d);
void delete_entry(node *hash_table[], char *w);
node *search_entry(node *hash_table[], char *w);
void print_entry(node *hash_table[], unsigned k);
void print_entries(node *hash_table[]);
void free_hash_table(node *hash_table[], unsigned length);


int main()
{
    node *hash_table[HASHSIZE];
    int i;
    for (i=0; i < HASHSIZE; ++i) {
	hash_table[i] = NULL;
    }

    insert_entry(hash_table, "duck", "an animal that quacks");
    insert_entry(hash_table, "dubl", "collision with duck");
    insert_entry(hash_table, "cow", "an animal that is tasty");
    delete_entry(hash_table, "duck" );

    print_entries(hash_table);
    free_hash_table(hash_table, HASHSIZE);
    /*print_entry(hash_table, 107);*/

    return 0;
}



unsigned hash(char *s) {

    unsigned hashval = 0;

    for (; *s; s++) {

	hashval = *s + hashval;

    }
    return hashval % HASHSIZE;


}


void insert_entry(node *hash_table[], char *w, char *d) {

    if (!hash_table[hash(w)])  {
	hash_table[hash(w)] = malloc(sizeof(node));
	// n and hash_table are pointing to NULL, and so n is not a pointer to hash_table
	// can't just replace hash_table with n
	hash_table[hash(w)]->word = w;
	hash_table[hash(w)]->def = d;
	hash_table[hash(w)]->next = NULL; 

    }

    // search along linked list at hash(w) element in hash_table
    else {
	node *n = hash_table[hash(w)];
	for (; n != NULL; n = (n)->next) {
	    if (strcmp((n)->word, w) == 0) {
		(n)->def=d;
		return;
	    }
	    else if ( (n)->next  == NULL)
		break;
	}

	(n)->next  = malloc(sizeof(node));
	(n)->next->word = w;
	(n)->next->def = d;
	(n)->next->next = NULL;


    }


}

void print_entry(node *hash_table[], unsigned k) {

    node *n = hash_table[k];

    for(; n; n = n->next) 
	printf("\n%s: %s", n->word, n->def);

} 




void print_entries(node *hash_table[]) {

    int i;
    for (i = 0; i < HASHSIZE; ++i) {
	if(hash_table[i]) {
	    print_entry(hash_table, i);
	}

    }

}



void free_hash_table(node *hash_table[], unsigned length)
{
    unsigned int i=0;
    for ( ; i < length; ++i) {
	if (hash_table[i]  && hash_table[i]->next == NULL)  {
	    free(hash_table[i]);
	    hash_table[i] = NULL;
	}

	else if  (hash_table[i]  && hash_table[i]->next) 
	{
	    node *n = hash_table[i];
	    node *p;

	    // frees linked list--need to store next structure data before deleting parent structure
	    //
	    for(; n->next; p=n, n=n->next) {
		p->next = NULL; 	
		free(n);
	    }

	    n->next = NULL;
	    free(n);	
	}

    }
    /*free(hash_table);*/  // unncessary--hash_table is put on the stack (it's an automatic variable in fact),
    // and will be cleaned up when  function or scope is exited.
    // If put on heap--different story. Use one free for each malloc.
}

void delete_entry(node *hash_table[], char *w) {

    node *n = hash_table[hash(w)];
    node *p = hash_table[hash(w)];

    if (hash_table[hash(w)]) {

	if (hash_table[hash(w)]->next == NULL) {
	    free(hash_table[hash(w)]);
	    hash_table[hash(w)] = NULL;
	}
	else {

	    for (; n != NULL; p=n, n = n->next) {
		if (strcmp(n->word, w) == 0) {
		    if (n == hash_table[hash(w)]) {
			hash_table[hash(w)] = n->next; 
			free(n);
			break;
		    }
		    else {
			p->next = n->next;
			free(n);
			n = NULL;	       
			break;
		    }


		}


	    }
	}
    }
}

node *search_entry(node *hash_table[], char *w) {

    if (!hash_table[hash(w)]) 
	return NULL; 


    // search along linked list at hash(w) element in hash_table
    else {
	node *n = hash_table[hash(w)];
	for (; n != NULL; n = n->next) {
	    if (strcmp(n->word, w) == 0) 
		break;
	}

	return n;	

    }


}


