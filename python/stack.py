class Stack:
    def __init__(self, *args):
        self.list = list(args)
        self.size = len(args)

    def push(self, val):
        self.list.append(val)
        self.size += 1

    def pop(self):
        val = self.list[-1]
        self.size -= 1
        self.list = self.list[0:-1]
        return val


if __name__ == '__main__':
    stack = Stack(3, -1, 20)
    stack.push(30)
    print(stack.pop())
    print(stack.pop())
