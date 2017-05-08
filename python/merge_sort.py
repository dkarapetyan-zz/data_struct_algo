import numpy as np
from math import floor


def merge_sort(arr, start, end):
    # base case:

    if start >= end:
        return [arr[end]]

    mid = (start + end) / 2
    left_sort = merge_sort(arr, start, mid)
    right_sort = merge_sort(arr, mid + 1, end)
    merged = _merge(left_sort, right_sort)
    return merged


def _merge(arr1, arr2):
    merged = []

    i1 = 0
    i2 = 0
    len1 = len(arr1)
    len2 = len(arr2)

    while i1 < len1 and i2 < len2:
        if arr1[i1] < arr2[i2]:
            merged.append(arr1[i1])
            i1 += 1
        else:
            merged.append(arr2[i2])
            i2 += 1

    if i2 == len2:
        merged.extend(arr1[i1:])
    elif i1 == len1:
        merged.extend(arr2[i2:])

    return merged


if __name__ == '__main__':
    print(merge_sort([-2, -10, 4, 20, 10], 0, 4))
