from max_heap import MaxHeap


def heap_sort(the_list):
    max_heap = MaxHeap(the_list)
    for i in range(max_heap.size):
        max_heap.swap(0, max_heap.size - 1)
        max_heap.size -= 1
        max_heap.max_heapify(0)
    return max_heap.list


if __name__ == '__main__':
    print(heap_sort([5, -3, 20, -50, 24, 37, 10, 4]))
