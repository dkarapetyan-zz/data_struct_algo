# insert jth value in ith spot, and push everything over to the right
def _insert(A, j, i):
    key = A[j]
    for k in reversed(range(i, j)):
        A[k + 1] = A[k]
    A[i] = key
    return A


def insertion_sort(A):
    for k in range(1, len(A)):
        key = k
        key_val = A[k]
        for i in range(k):
            if i == 0:
                if key_val <= A[i]:
                    _insert(A, key, i)
                    break
            elif A[i - 1] <= key_val <= A[i]:
                _insert(A, key, i)
                break
    return A


if __name__ == '__main__':
    print(insertion_sort([4, -10, -13, 3, 20, 5]))
