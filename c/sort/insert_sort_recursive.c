#include <stdio.h>
#include <stdlib.h>


// recursive insertion sort

void insertion_sort (int *array, int start, int end); 


int main()
{
    int my_array[6] = {8,2,3,7,1,9};
    int start = 0;
    int end = 5;
    insertion_sort(my_array, start, end);
    for (int i=start ; i <=end ;i++ ) 
        printf("%d ", my_array[i]);

    return 0;
}






void insertion_sort(int *array, int start, int end) {
    if (start == end) 
        return;
    else if (start > end)
        printf("%s\n", "Array start value is greater than its end value. Try again");
    else {
        insertion_sort(array, start + 1, end);
        for (int i = end; i > start ; i--) {
            if (array[start] > array[i]) {
                int temp = array[start];  // about to overwrite this

                // shift array elements to left, with array[start] treated as empty slot 
                for (int k = start; k < i; k++)  
                    array[k] = array[k+1];

                // insert value of array[i] into empty space we just created
                array[i] = temp;
                break;
            }
        }
    }
} 










