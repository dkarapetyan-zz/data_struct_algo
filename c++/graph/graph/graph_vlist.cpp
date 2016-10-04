#include "graph_vlist.hpp"
int main()

{
    graph MyGraph;
    MyGraph = graph();
	MyGraph.add_edge(3, 4);
	MyGraph.add_edge(2, 1);
	MyGraph.add_edge(2, 4);
	MyGraph.add_edge(0, 3);
	MyGraph.add_vertex();
	MyGraph.add_edge(3, 5);
	MyGraph.delete_edge(3, 5);
	MyGraph.delete_edge(3, 4);
	MyGraph.delete_vertex(0);
	MyGraph.print_graph();
	MyGraph.bfs(2);
	MyGraph.print_path(2, 5);
	return 0;
}

