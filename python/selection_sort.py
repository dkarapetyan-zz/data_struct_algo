import numpy as np


def _swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def selection_sort(A):
    for i in reversed(range(len(A))):
        max_index = np.argmax(A[0:i + 1])
        _swap(A, i, max_index)
    return A


if __name__ == '__main__':
    print(selection_sort([3, -1, 20, -14, 30]))
