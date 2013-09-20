#include <vector>
#include <iostream>
using std::vector;
// Quicksort recursive algorithm

template <typename T>
void quicksort(vector<T> &my_vec, int left, int right);

template <typename T>
T partition(vector<T> &my_vec, int left, int right);




int main()
{
    vector<double> my_vec = {1, 7.5, 4.3, 12, 9, 2};
    quicksort<double>(my_vec, 0, my_vec.size() -1);
    for (auto i = my_vec.cbegin() ; i != my_vec.cend(); i++)
    {
        std::cout << *i << " ";
    }

}


// swap function
//
template <typename T>
void swap(vector<T> &my_vec, int k, int m)
{
    T temp;
    temp = my_vec[k];
    my_vec[k] = my_vec[m];
    my_vec[m]= temp;
}

template <typename T>
T partition(vector<T> &my_vec, int left, int right)
{
    int last;
    int pivot = (left + right)/2;

    // my_vec of length greater than 1
    //inductive (i.e. recursive) step
    swap<T>(my_vec, left, pivot); // make partition element first element of my_vec
    last = left;
    for (int i=left +1 ; i <= right ; ++i) {
        if (my_vec[i] < my_vec[left]) 
            swap<T>(my_vec, i, ++last);
    }
    // have all elements less than my_vec[left] immediately following
    // it--once this list terminates, have all ellements greater than my_vec[left].
    // Now we restore partition element
    swap<T>(my_vec, left, last); //done partitioning--last is our partition element
    return last;
}

template <typename T>
void quicksort(vector<T> &my_vec, int left, int right)
{
    if (right - left < -1) // error checking--negative my_vec length
    {
        std::cout << "You have supplied an my_vec of negative length. Please try again. \n";
        return;
    }

    else if (right - left ==  -1  || right - left == 0) // my_vec of length 0 or 1;
    return;

    else {
        T last = partition<T>(my_vec, left, right);
        quicksort<T>(my_vec, left, last-1);
        quicksort<T>(my_vec, last+1, right);
    }
}




