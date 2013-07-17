#include <stdlib.h>
#include <stdio.h>

typedef unsigned long ulong;


ulong binary_search(int *array, ulong start, ulong end, int num);


int main()
{
    int array[5] = {1,2,5,8,9};
    printf("%lu\n", binary_search(array, 0, 4, 2));
    return 0;
}





ulong binary_search(int array[], ulong start, ulong end, int num){

    if (end < start) // base case--empty array
        return 999999;

    else
    {
        ulong mid = (end + start)/2;
        if (num < array[mid]) 
            return binary_search(array, start, mid -1, num);

        else if (num > array[mid]) 
            return binary_search(array, mid + 1, end, num);

        else 
            return mid;
    }


}
