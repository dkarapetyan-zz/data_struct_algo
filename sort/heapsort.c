#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct heapnode {
    int left;
    int right;
    int parent;
    int key;
} heapnode;

void my_heapsort(heapnode *array[], int start, int end);
void max_heapify(heapnode *array[], int index);
void build_max_heap(heapnode *array[], int start, int end);


int main()
{
    heapnode *my_array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        my_array[i] = malloc(sizeof(heapnode));
        my_array[i]->key = rand()%35; 
    }

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", my_array[i]->key); 
        free(my_array[i]);
    }

    return 0;
}

void swap(heapnode *ptr1, heapnode *ptr2) {
    heapnode *temp = ptr1;
    ptr1 = ptr2;
    ptr2= temp;
}


void max_heapify(heapnode *array[], int index) {

    heapnode *largest;
    if (array[index] == NULL) {
        printf("%s\n", "No heapnode there. Please try again");
        return;
    }

    else {

        if (array[index]->left && array[index]->right  ) {

            if (array[index]->left->key < array[index]->right->key) 
                largest = array[index]->right;

            else
                largest = array[index]->left; 

        }
        else if (array[index]->left)
            largest = array[index]->left;

        else if (array[index]->right)
            largest = array[index]->right;

        else
            largest = array[index];
    }

    if (largest != array[index]) 
        swap(largest, array[index]);

}



