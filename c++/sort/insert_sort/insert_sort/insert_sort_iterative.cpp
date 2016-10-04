#include <vector>
#include <iostream>

using std::vector;
using std::cout;

// iterative insertion sort

template <typename T>
void insertion_sort (vector<T> &my_vec, int start, int end); 


int main()
{
    vector<int> my_vec = {20, 17, 1, 5, 4, 3};
    int start = 0;
    int end = 5;
    insertion_sort(my_vec, start, end);
    for (int i=start ; i <=end ;i++ ) 
        cout << my_vec[i] << " ";

    return 0;
}





    template <typename T>
void insertion_sort(vector<T> &my_vec, int start, int end) 
{
    if (start == end) 
        return;
    else if (start > end)
        printf("%s\n", "Array start value is greater than its end value. Try again");
    else 
    {
        for (int i = start +1; i <= end; i++) 
        {
            for (int j = start; j < i; j++)
            {
                if (my_vec[i] < my_vec[j]) 
                {
                    int temp = my_vec[i];  // about to overwrite this
                    // shift my_vec elements to right, with my_vec[i] treated as empty slot 
                    for (int k = i; k > j; k--)  
                        my_vec[k] = my_vec[k-1];
                    // insert value of my_vec[i] into empty space we just created
                    my_vec[j] = temp;
                }
            }
        } 
    }
}










