class Node:
    def __init__(self, data=None, the_next=None):
        self.data = data
        self.the_next = the_next


class LinkedList:
    def __init__(self, *list_nodes):
        self.root = list_nodes[0]
        self.length = len(list_nodes)
        for i in range(self.length):
            if i < self.length - 1:
                list_nodes[i].the_next = list_nodes[i + 1]

    def printer(self):
        array = []
        p = self.root
        while p is not None:
            array.append(p.data)
            p = p.the_next
        print(array)


if __name__ == '__main__':
    ll = LinkedList(Node(-1), Node(3), Node(1))
    ll.printer()
