#include <iostream>


// iterative selection sort

void swap(int *array, int x, int y); 
int min_index(int *array, int start, int end);
void selection_sort(int *array, int start, int end); 


int main()
{
    int my_array[6] = {20, 17, 1, 5, 4, 3};
    int start = 0;
    int end = 5;
    selection_sort(my_array, start, end);
    for (int i=start ; i <=end ;i++ ) 
        std::cout << my_array[i];

    return 0;
}






void selection_sort(int *array, int start, int end) {
    if (start == end) 
        return;
    else if (start > end)
        std::cout << "Array start value is greater than its end value. Try again";
    else {
        swap(array, start, min_index(array, start, end));
        selection_sort(array, start + 1, end);
    }

}






int min_index(int *array, int start, int end) {

    if (start > end)
        return -1;
    else
    {
        int pos = start;

        for (int i = start; i <= end; i++) {
            if (array[i] < array[pos]) 
                pos = i;
        }

        return pos;
    }
}

void swap(int *array, int x, int y) {

    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}
