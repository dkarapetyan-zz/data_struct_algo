#include <iostream>
#define SIZE 10

void my_heapsort(int array[], int len);
void max_heapify(int array[], int len, int index);
void build_max_heap(int array[], int len);
void swap(int array[], int x, int y);
int left(int x);
int right(int x);


int main()
{
    int my_array[SIZE];

    for (int i = 0; i < SIZE; i++)
        my_array[i]= rand()%32;

    my_heapsort(my_array, SIZE);

    for (int i = 0; i < SIZE; i++)
        std::cout << my_array[i];

    return 0;
}




void swap(int array[], int x, int y)
{
    int temp = array[x];
    array[x] = array[y];
    array[y]= temp;
}

int left(int x)
{
    return 2*x + 1;
}

int right(int x)
{
    return 2*x + 2;
}


void max_heapify(int array[], int len, int index)
{

    int largest;
    // error checking
    if (index >= len )
    {
        std::cout << "No int there. Please try again\n";
        return;
    }

    else
    {
        // check left and right children of index
        if (left(index) < len  && right(index) < len  )
        {

            if (array[left(index)] < array[right(index)]) 
                largest = right(index);

            else
                largest = left(index); 

        }
        else if (left(index) < len)
            largest = left(index);

        else if (right(index) < len)
            largest = right(index);

        else
            largest = index;
    }

    if (largest != index && array[index] < array[largest])
    {
        // percolate down a node, and repeat 
        swap(array, largest, index);
        max_heapify(array, len, largest);
    }
}

void build_max_heap(int array[], int len)
{
    // non-leaves are one row up from bottom row.
    // leaves are already 1-node heaps
    for (int i=(len-2)/2; i >=0; i--) 
        max_heapify(array, len, i);
}
void my_heapsort(int array[], int len)
{
    build_max_heap(array, len);
    // First element is now largest of array. Exchange with last
    // then "heapify" new first element. Everything below it is a heap
    for (int i = len -1; i >= 1; i--)
    {
        swap(array, 0, i);
        if (i > 0)
            max_heapify(array, i, 0);
    }
}

