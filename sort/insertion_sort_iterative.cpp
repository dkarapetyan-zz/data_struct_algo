#include <stdio.h>
#include <stdlib.h>


// iterative insertion sort

void insertion_sort (int *array, int start, int end); 


int main()
{
    int my_array[6] = {20, 17, 1, 5, 4, 3};
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
        for (int i = start +1; i <= end; i++) {
            for (int j = start; j < i; j++) {
                if (array[i] < array[j]) {
                    int temp = array[i];  // about to overwrite this
                    // shift array elements to right, with array[i] treated as empty slot 
                    for (int k = i; k > j; k--)  
                        array[k] = array[k-1];
                    // insert value of array[i] into empty space we just created
                    array[j] = temp;
                }
            }
        } 
    }
}










