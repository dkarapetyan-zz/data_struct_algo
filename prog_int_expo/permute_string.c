#include <stdlib.h>
#include <stdio.h>

// program to print out all possible permutations of a string

void swap(char *x, char *y);
void permute(char string[], int start, int end);


int main()
{
char string[] = "xyz";
permute(string, 0, 2);
return 0;
}

void swap(char *x, char *y) {

    char temp = *x;
    *x = *y;
    *y = temp;
}


// This function takes three parameters: String, starting index of the string, ending index of the string.

void permute(char string[], int start, int end) { // pnum must be less than or equal to total num of permutations

    int j;

    if (start == end)
        printf("%s\n", string);

    else {
        for (j = start ; j <=end; j++) {
            swap(string + start, string + j);
            permute(string, start + 1, end);
            swap(string + start, string + j);

        }
    }

}











