from itertools import product
import numpy as np
from Queue import Queue
import datetime

INF = float('inf')


class VERTEX:
    def __init__(self, name=None, parent=None, dist=INF, color='white',
                 disc=None, term=None):
        self.name = name
        self.parent = parent
        self.dist = dist
        self.color = color
        # for dfs
        self.disc = disc
        self.term = term


class GRAPH:
    def __init__(self, matrix):
        self.adj_list = self._adj_mat_to_list(matrix)
        self.vertices = {key: VERTEX(name=key) for key in self.adj_list.keys()}

    def bfs(self, source):
        # initialize
        for vertex in self.vertices.values():
            vertex.color = 'white'

        # process source first
        source_obj = self.vertices[source]
        source_obj.dist = 0
        source_obj.parent = None
        source_obj.color = 'black'
        Q = Queue()
        Q.put(source_obj)
        # process remaining vertices
        while not Q.empty():
            u = Q.get()
            for vertex in self.adj_list[u.name]:
                if vertex.color == 'white':
                    vertex.dist = u.dist + 1
                    vertex.parent = u
                    vertex.color = 'black'
                    Q.put(vertex)

    def _dfs_visit(self, vertex):
        vertex.color = 'black'
        vertex.disc = datetime.datetime.utc.now()
        for child_vertex in self.adj_list[vertex.name]:
            if child_vertex.color == 'white':
                child_vertex.parent = vertex
                self._dfs_visit(child_vertex)
        vertex.term = datetime.datetime.utc.now()

    def dfs(self):
        # initialize
        for vertex in self.vertices.values():
            vertex.color = 'white'

        for vertex in self.vertices:
            if vertex.color == 'white':
                self._dfs_visit(vertex)

    def _adj_mat_to_list(self, matrix):
        final = {str(i): [] for i in range(matrix.shape[0])}

        for i, j in product(range(matrix.shape[0]), range(1, matrix.shape[1])):
            if matrix[i, j] == 1:
                final[str(i)].append(str(j))

        return final

    def _adj_list_to_matrix(self, adj_list):
        the_matrix = np.random.randint(0, 1,
                                       size=(len(adj_list), len(adj_list)))
        for row in adj_list.keys():
            for column in adj_list[row]:
                the_matrix[int(row), int(column)] = 1
        return the_matrix


if __name__ == '__main__':
    the_matrix = np.random.randint(0, 2, size=(5, 5))
    for i in zip(range(the_matrix.shape[0]), range(the_matrix.shape[0])):
        the_matrix[i, i] = 0
        # print(adj_mat_to_list(the_matrix))
        # bobo = adj_mat_to_list(the_matrix)
        # print(adj_list_to_matrix(bobo))
