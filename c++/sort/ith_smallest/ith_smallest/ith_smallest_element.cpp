#include <iostream>
#include <ctime>

// ith_smallest recursive algorithm
//
//
int rand_partition(int *array, int left, int right);
int ith_smallest(int *array, int left, int right, int i);

int main()
{
    int seed = time(nullptr);
    srand(seed);
    int my_array[]={1, 7, 4, 12, 9, 2};
    std::cout << ith_smallest(my_array, 0, 5, 4) << "\n";

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

int rand_partition(int *array, int left, int right)
{
    // we partition using the pivot element of the array
    // base step
    int last;
    // pivot is between left and right--have to be careful, as right-left can be negative in algorithm
    int pivot = rand()%(right-left +2 ) + left - 1 ; 

    if (left - right > 1) // error checking--negative array length
    {
        std::cout << "You have supplied an array of negative length. Please try again\n";
        return -1;
    }

    else if (left - right ==  1) // array of length 0;
    return -1;

    else if (left - right == 0) // array of length 1
        return left;

    else { // array of length greater than 1
        //inductive (i.e. recursive) step
        swap(array, left, pivot); // make partition element first element of array
        last = left;
        for (int i=left +1 ; i <= right ; ++i) {
            if (array[i] < array[left]) 
                swap(array, i, ++last);
        }
        // have all elements less than array[left]
        // immediately following it--once this list terminates,
        // have all ellements greater than array[left]. Now we restore partition element
        swap(array, left, last); //done partitioning--last is our partition element
        return last;
    }
}

int ith_smallest(int *array, int left, int right, int i) {

    int last = rand_partition(array, left, right);
    if (i == last - left + 1)
        return array[last];

    else if (i < last - left +1) 
        return ith_smallest(array, left, last-1, i);
    else
        return ith_smallest(array, last+1, right, i);  
}




