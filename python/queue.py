class Queue:
    def __init__(self, *args):
        self.list = list(args)

    def dequeue(self):
        val = self.list[0]
        self.list = self.list[1:]
        return val

    def enqueue(self, val):
        self.list.append(val)


if __name__ == '__main__':
    queue = Queue(3, -1, 20)
    queue.enqueue(30)
    print(queue.dequeue())
    print(queue.dequeue())
