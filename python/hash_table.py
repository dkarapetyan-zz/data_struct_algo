class HashTable:
    def __init__(self, the_list):
        self.hash_func = hash
        self.table = {self.hash_func(item): item for item in the_list}

    def get(self, val):
        self.table.get([self.hash_func(val), 'None'])

    def push(self, val):
        self.table[self.hash_func(val)] = val

    def delete(self, val):
        self.table.pop(self.hash_func(val), 'None')


if __name__ == '__main__':
    hashtable = HashTable(['bobo', 3, 'string'])
    print(hashtable.table)
