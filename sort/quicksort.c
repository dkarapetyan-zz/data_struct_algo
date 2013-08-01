#include <stdio.h>
#include <stdlib.h>

// Quicksort recursive algorithm
//
//

void quicksort(int *array, int k, int m);

int main()
{
    int my_array[]={1, 7, 4, 12, 9, 2};
    quicksort(my_array, 0, 5);
    for (int i=0; i < 6; i++) {
        printf("%d ", my_array[i]);
    }
    return 0;
}


// swap function
//

void swap(int *array, int k, int m)
{

    int temp;
    temp = array[k];
    array[k] = array[m];
    array[m]= temp;
}


void quicksort(int *array, int left, int right) {
    // we partition using the pivot element of the array
    // base step
    int last;
    int pivot = (left + right)/2;

    if (left - right > 1) // error checking--negative array length
        printf("%s\n", "You have supplied an array of negative length. Please try again");

    else if (left - right ==  1) // array of length 0;
    return;

    else if (left - right == 0) // array of length 1
        return;

    else { // array of length greater than 1
        //inductive (i.e. recursive) step
        swap(array, left, pivot); // make partition element first element of array
        last = left;
        for (int i=left +1 ; i <= right ; ++i) {
            if (array[i] < array[left]) 
                swap(array, i, ++last);
        }
        // have all elements less than array[left] immediately following it--once this list terminates, have all ellements greater than array[left]. Now we restore partition element
        swap(array, left, last); //done partitioning--last is our partition element
        quicksort(array, left, last-1);
        quicksort(array, last+1, right);  
    }
}




