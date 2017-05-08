from __future__ import division
from math import ceil


def _swap(arr, index1, index2):
    arr[index1], arr[index2] = arr[index2], arr[index1]


def _partition(arr, start, end):
    pivot_index = int(ceil(start + end / 2))
    pivot = arr[pivot_index]
    final_index = start

    for right_i in range(start, end + 1):
        if arr[right_i] < pivot:
            _swap(arr, right_i, start)
            final_index += 1
    _swap(arr, pivot_index, final_index)
    return final_index


def quicksort(arr, start=None, end=None):
    # base case
    if start >= end:
        return

    p = _partition(arr, start, end)
    quicksort(arr, start, p - 1)
    quicksort(arr, p + 1, end)


if __name__ == '__main__':
    array = [5, 3, -7, 10]
    quicksort(array, 0, 3)
    print(array)
