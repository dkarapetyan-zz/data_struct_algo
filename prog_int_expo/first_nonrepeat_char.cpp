// Write an efficient function to find the first nonrepeated character in a string
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 128 //ASCII table size

int hash_array[MAXSIZE];

char first_nonrepeated_char(char *string);

int main()
{
    char *string = NULL;
    size_t lencap = 0;

    // initialize array
    for (size_t i=0 ; i < MAXSIZE-1 ; ++i) {
        hash_array[i] = 0;
    }
    hash_array[MAXSIZE-1]=0;

    while(!string) {
        puts("Please enter a line of text");
        getline(&string, &lencap, stdin);
        if (strlen(string) > MAXSIZE) {
            puts("The string is too long. Enter a string with fewer than 128 characters.");
            free(string);
            string=NULL;
        }
        else if (string[0]=='\n' ) {
            puts("You hit 'return' without entering other characters.");
            free(string);
            string=NULL;
        }

        else 
            printf("\n%s %s%c%s\n", "The first nonrepeating character in the inputted string is",
                    "\"", first_nonrepeated_char(string), "\".");
    }

    free(string);

    return 0;
}

char first_nonrepeated_char(char *string){

    // count occurences of each character in string

    for (size_t i = 0 ; string[i]; ++i ) {
        ++hash_array[(int)string[i]];
    }

    // Go along string again, 
    // and find first array element greater than 1

    size_t j;
    for (j=0 ; j < MAXSIZE; ++j ) {
        if (hash_array[j] > 1)
            break;
    }
    return (char) j;
}


