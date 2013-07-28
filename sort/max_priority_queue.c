#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 100
#define SENTINEL -9999
// maximum priority queue using heap array

typedef struct node
{
    int key;
} node;


typedef struct heap
{
    node array[SIZE];
    int hlength;
    int alength;
} heap;


int heap_max(heap *my_heap);
int heap_pop_max(heap *my_heap);
void insert_key(heap *my_heap, int x);
void increase_key(heap *my_heap, int i, int k);
void max_heapify(heap *my_heap, int index);
void build_max_heap(heap *my_heap);
void swap(node array[], int x, int y);
int left(int x);
int right(int x);
int parent(int x);


int main()
{
    heap my_heap;
    memset(&my_heap, 0, sizeof(heap));
    my_heap.hlength = 5;

    for (int i = 0; i < my_heap.hlength; i++)
        my_heap.array[i].key=rand()%32;

    build_max_heap(&my_heap);

    for (int i = 0; i < my_heap.hlength; i++)
        printf("%d ", my_heap.array[i].key); 

    return 0;
}


int heap_max(heap *my_heap)
{
    return my_heap->array[0].key; 
}


int heap_pop_max(heap *my_heap)
{
    int temp = my_heap->array[0].key;
    swap(my_heap->array, 0, my_heap->hlength - 1);
    my_heap->hlength-=1;
    return temp;
}
void insert_key(heap *my_heap, int k)
{
    my_heap->hlength+=1;
    my_heap->array[my_heap->hlength-1].key = SENTINEL;
    increase_key(my_heap, my_heap->hlength-1, k);
}

void increase_key(heap *my_heap, int i, int k)
{
    if (k < my_heap->array[i].key)
        printf("%s\n", "New key is smaller than old key. Please try again");

    else
    {
        my_heap->array[i].key = k;
        while(i > 0 && my_heap->array[i].key > my_heap->array[parent(i)].key )
        {
            swap(my_heap->array, i, parent(i));
            i = parent(i);
        }
    }
}

void swap(node array[], int x, int y)
{
    int temp = array[x].key;
    array[x].key = array[y].key;
    array[y].key= temp;
}

int left(int x)
{
    return 2*x + 1;
}

int right(int x)
{
    return 2*x + 2;
}

int parent(int x)
{
    return (x-1)/2;
}


void max_heapify(heap *my_heap, int index)
{

    int largest;
    int end = my_heap->hlength - 1;
    // error checking
    if (index > end)
    {
        printf("%s\n", "No int there. Please try again");
        return;
    }

    else
    {
        // check left and right children of index
        if (left(index) <= end  && right(index) <= end  )
        {

            if (my_heap->array[left(index)].key < my_heap->array[right(index)].key) 
                largest = right(index);

            else
                largest = left(index); 

        }
        else if (left(index) <= end)
            largest = left(index);

        else if (right(index) <= end)
            largest = right(index);

        else
            largest = index;
    }

    if (largest != index && my_heap->array[index].key < my_heap->array[largest].key)
    {
        // percolate down a node, and repeat 
        swap(my_heap->array, largest, index);
        max_heapify(my_heap, largest);
    }
}

void build_max_heap(heap *my_heap)
{

    // non-leaves are one row up from bottom row.
    // leaves are already 1-node heaps
    for (int i=(my_heap->hlength-1)/2; i >=0; i--) 
        max_heapify(my_heap, i);
}

