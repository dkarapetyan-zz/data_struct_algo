#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 5

typedef struct heapnode {
    int *left;
    int *right;
    int *parent;
    int *key;
} heapnode;

void my_heapsort(heapnode array[], int len, int start, int end);
void max_heapify(heapnode array[], int len, int index);
void build_max_heap(heapnode array[], int len, int start, int end);

int main()
{
    heapnode my_array[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        memset(&my_array[i], 0, sizeof(heapnode));
        *(my_array[i].key) = rand()%35;
        *(my_array[i].parent) = i/2;

        if (i < (SIZE-2)/2)
        {
            *(my_array[i].left) = 2i;
            *(my_array[i].right) = 2i+1;
        }

    }




    max_heapify(my_array, SIZE, 2);

    for (int i = 0; i < SIZE; i++)
        printf("%d ", *(my_array[i].key)); 
    
    return 0;
}

void swap_keys(heapnode x, heapnode y)
{
    heapnode temp = x;
    x = y;
    y= temp;
}


void max_heapify(heapnode array[], int len, int index) {

    int largest;
    if (index > len -1 ) {
        printf("%s\n", "No heapnode there. Please try again");
        return;
    }

    else {

        if (array[index].left && array[index].right  ) {

            if (array[index].left < array[index].right) 
                largest = *(array[index].right);

            else
                largest = *(array[index].left); 

        }
        else if (array[index].left)
            largest = *(array[index].left);

        else if (array[index].right)
            largest = *(array[index].right);

        else
            largest = index;
    }

    if (largest != index) {
        swap_keys(array[largest], array[index]);
        max_heapify(array, len, largest);
    }
}

void build_max_heap(heapnode array[], int len, int start, int end) {
    if (end > len -1 || end < start) 
        printf("%s\n", "Invalid start and end points. Please try again");

    for (int i =len/2; i >=1; i--) 
        max_heapify(array, len, i);
}

