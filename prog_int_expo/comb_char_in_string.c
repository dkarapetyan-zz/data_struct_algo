#include <stdio.h>
#include <stdlib.h>



void comb(char *string, int start, int end);



int main()
{
char string[2] = "he";
comb(string, 0, 1);
return 0;
}


void comb(char *string, int start, int end) {
if (start > end) {
    printf("%c", string[start]);
}
else
    comb(string, i, end);
    }


}


