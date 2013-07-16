#include <stdio.h>
#include <string.h>


/*#ifndef swap*/
/*#define swap(T, a,b) { \*/
/*T temp=a; \*/
/*a=b; \*/
/*b=temp; \*/
/*}*/
/*#endif*/


void reverse_string(char *string, int len);
void reverse_words_string(char *string);



int main()
{
    /*char *string = NULL;*/
    /*size_t lencap=0;*/
    /*puts("Please enter a string");*/
    /*getline(&string, &lencap, stdin);*/

    // if use string pointer, get error --pointer points to read-only string constant. Must copy
    // string into stack, then manipulate the copy

    char string[]="Do or do not, there is no try."; 
    reverse_string(string, strlen(string));
    reverse_words_string(string);
    puts(string);
    /*free(string);*/
    return 0;
}








void reverse_string(char *string, int len)
{
    int temp, i, j;
    for (i = 0, j = len-1; i < j; i++, j--) { 
        temp = string[i];
        string[i] = string[j];
        string[j] = temp; 
    }
}

void reverse_words_string(char *string) {

    char *src =string;
    int len = 0;

    for ( ; ; src++ ) {

        if (*src == ' ' || *src == '\0') {
            reverse_string(src-len, len);
            len = 0;
            if (!*src) 
                break;

        }
        else
            len++;





    }



}


