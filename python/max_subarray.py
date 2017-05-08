from __future__ import division
from math import floor


def _midpoint_cross(arr):
    length = len(arr)
    mid = int(length / 2)
    start = mid
    start2 = mid
    sum = arr[start]

    while start + 1 <= length - 1 and arr[start] + arr[start + 1] > arr[start]:
        sum += arr[start + 1]
        start += 1

    while start2 - 1 >= 0 and arr[start2 - 1] + sum > sum:
        sum += arr[start2 - 1]
        start2 -= 1

    return arr[start2: start + 1], sum


def max_div_conquer(arr):
    # base case
    if len(arr) == 1:
        return (arr, arr[0])
    else:
        length = len(arr)
        mid = int(length / 2)
        middle = _midpoint_cross(arr)
        left_sub = max_div_conquer(arr[:mid])
        right_sub = max_div_conquer(arr[mid:])
        return max((left_sub, right_sub, middle), key=lambda x: x[1])


def max_subarray_lin(arr):
    max_so_far = max_ending_here = 0
    max_arrays = []
    start = 0
    for i, x in enumerate(arr):
        if max_ending_here + x >= 0:
            max_ending_here += x
            end = i
            if max_ending_here > max_so_far:
                max_so_far = max_ending_here
                max_arrays.append((arr[start: end + 1], max_so_far))
        else:
            max_ending_here = 0
            start = i + 1

    if len(max_arrays) == 0:
        return [], 0
    else:
        return max_arrays[-1]


if __name__ == "__main__":
    print(max_subarray_lin([-1, -3, -5, -40, -5, -2, -4, -3, -20]))
