// algorithm to delete characters from an inputted string
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 128 // ASCII character set size

typedef enum bool {
    no, yes
} bool;

// direct address table--don't need to worry about collision chaining 
typedef struct hash_table { 
    char **hash_list; 
} hash_table;

bool search_table(hash_table mytable, char c);


int main()
{
    hash_table mytable;
    mytable.hash_list = calloc(MAXSIZE, sizeof(char*));
    char *string = NULL;
    size_t lencap = 0;


    while(1) {
        puts("Please enter some text");
        getline(&string, &lencap, stdin);
        if(string[0] == '\n')
        {
            puts("You did not enter any text.\n");
            free(string);
            string=NULL;
        }
        else
            break;
    }

    char *chars_to_del; // now want to input characters to remove
    size_t chars_to_del_cap=0;

    puts("\nPlease enter a string of characters you would like removed");
    getline(&chars_to_del, &chars_to_del_cap, stdin);

    for (size_t i = 0 ; chars_to_del[i]!= '\0'; ++i) {
        // character c is stored in ascii integer equivalent of table
        mytable.hash_list[(int)(chars_to_del[i])] = &(chars_to_del[i]); 
    }

    size_t src=0;
    size_t dest=0;
    for (; string[src]!= '\0'; ++src) {

        // check each character in string to see if is a char we want to delete

        if (search_table(mytable, string[src]) == no) {
            string[dest] = string[src]; // in place movement of character across string
            ++dest;
        }
    }

    string[dest] = '\0';
    printf("\nYour new string is \"%s\".", string);

    free(string);
    free(chars_to_del);
    free(mytable.hash_list);
    return 0;
}


bool search_table(hash_table mytable, char c) {

    if (mytable.hash_list[(int)c])  
        return yes;
    else
        return no;

}



