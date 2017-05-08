def _swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def bubble_sort(A):
    swap_count = 1
    while swap_count != 0:
        swap_count = 0
        for i in range(1, len(A)):
            if A[i - 1] > A[i]:
                _swap(A, i - 1, i)
                swap_count += 1
    return A


if __name__ == '__main__':
    print(bubble_sort([20, -4, 3, 100, -10]))
