from copy import copy


class Node:
    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right


class BinaryTree:
    def __init__(self, args_list, kind='balanced'):
        self.root = None
        self.args = args_list
        if kind == 'balanced':
            self.balanced_build()
        elif kind == 'random':
            self.random_build()

    def insert(self, node):
        p = self.root
        if p is None:
            self.root = node
            return

        q = None
        while p is not None:
            q = p
            if node.data < p.data:
                p = p.left
            else:
                p = p.right

        if node.data < q.data:
            q.left = node
        else:
            q.right = node

    def random_build(self):
        for item in self.args:
            self.insert(Node(data=item))

    def inorder_traverse(self, root):
        if root is None or self.root is None:
            return
        self.inorder_traverse(root.left)
        print(root.data)
        self.inorder_traverse(root.right)

    def postorder_traverse(self, root):
        if root is None or self.root is None:
            return
        self.inorder_traverse(root.left)
        self.inorder_traverse(root.right)
        print(root.data)

    def preorder_traverse(self, root):
        if root is None or self.root is None:
            return
        print(root.data)
        self.inorder_traverse(root.left)
        self.inorder_traverse(root.right)

    def balanced_build(self, the_list=None):
        if the_list is None:
            the_list = copy(self.args)
            the_list.sort()
        else:
            the_list.sort()
        size = len(the_list)
        if size == 0:
            return
        mid = size / 2
        self.insert(Node(the_list[mid]))
        self.balanced_build(the_list[0:mid])
        self.balanced_build(the_list[mid + 1:])


if __name__ == '__main__':
    bintree = BinaryTree([5, 10, 3, 4, -1, 6, 7], 'balanced')
    bintree.inorder_traverse(bintree.root)
