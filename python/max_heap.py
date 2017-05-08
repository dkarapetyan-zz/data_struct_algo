class MaxHeap:
    def __init__(self, the_list):
        self.list = the_list
        self.size = len(the_list)
        self.max_heap_gen()

    def right(self, i):
        if (2 * i + 2) <= self.size - 1:
            return 2 * i + 2
        else:
            return None

    def left(self, i):
        if (2 * i + 1) <= self.size - 1:
            return 2 * i + 1
        else:
            return None

    def val(self, i):
        return self.list[i]

    def swap(self, i, j):
        self.list[i], self.list[j] = self.list[j], self.list[i]

    def max_heapify(self, i):
        # base case
        if self.left(i) is None and self.right(i) is None:
            return

        elif self.left(i) is None:
            if self.val(i) >= self.val(self.right(i)):
                return
            else:
                largest_index = self.right(i)
        elif self.right(i) is None:
            if self.val(i) >= self.val(self.left(i)):
                return
            else:
                largest_index = self.left(i)

        elif self.val(i) >= max(self.val(self.left(i)),
                                self.val(self.right(i))):
            return
        # inductive step
        else:
            if self.val(self.left(i)) > self.val(self.right(i)):
                largest_index = self.left(i)
            else:
                largest_index = self.right(i)

        self.swap(i, largest_index)
        self.max_heapify(largest_index)

    def max_heap_gen(self):
        for i in reversed(range(self.size)):
            self.max_heapify(i)
