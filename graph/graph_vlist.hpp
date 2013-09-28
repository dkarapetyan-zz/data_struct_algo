// graph implementation with array of pointers to linked lists

#include <string>
#include <vector>
#include <list>
#include <queue>
using std::string;
using std::vector;
using std::list;
using std::queue;
const int SENTINEL = -1;

class vertex
{
	friend class graph;
	int num;
	int distroot;
	vertex * parent;
	string color;
	list<vertex *> AdjList;

public:
	// constructors
	vertex(int __num, int __distroot, string __color, parent __parent) :
		num(__num), distroot(__distroot), color(__color), parent(__parent), AdjList(
				new list<vertex *>)
{
}
	vertex(int __num) :
		num(__num), distroot(SENTINEL), color("white"), parent(nullptr), AdjList(
				new list<vertex *>)
	{
	}
};

class graph
{

private:
	list<vertex> vertices;
	static int TotalVertices;

public:

	void add_vertex();
	void add_edge(int __src, int dest);
	void delete_edge(int __src, int dest);
	void delete_vertex(int __num);
	void print_graph();
	void print_list(int __num);
	void delete_list(int __num);
	void delete_graph();
	void bfs(int __r);
	void dfs_visit(vertex *__v);
	void dfs();
	int max_vertex();
	list<vertex>::iterator search_vertex(int __num);
	void print_path(int __num, int __num2);
};

static int graph::TotalVertices = 0;

int graph::max_vertex()
{
	int k = 0;
	for (auto p = vertices.begin(); p != vertices.end(); p++)
	{
		if (k < (p->num))
			k = p->num;
	}
	return k;
}

list<vertex>::iterator graph::search_vertex(int __num)
{
	for (auto p = vertices.begin(); p != vertices.end(); ++p)
	{
		if (p->num == __num)
			return p;
	}

	return vertices.end();
}

void graph::add_vertex()
{
	int k = max_vertex() + 1;
	vertices.emplace_back(k);
	TotalVertices += 1;
}

void graph::add_edge(int __src, int __dest)
{
	auto vs = search_vertex(__src);
	auto vd = search_vertex(__dest);

	if (vs != vertices.end() && vd != vertices.end())
	{
		// add new dest node at start of linked list for vertex '__src'
		vs->AdjList.push_front(&*vd);

		// by symmetry, must do same for linked list for vertex '__dest'
		vd->AdjList.push_front(&*vs);
	}
}

void graph::delete_edge(int __src, int __dest)
{
	auto vs = search_vertex(__src);
	auto vd = search_vertex(__dest);

	if (vs != vertices.end() && vd != vertices.end())
		return;

	//	go along linked list, and delete a node
	for (auto p = vs->AdjList.begin(); p != vs->AdjList.end(); p++)
	{
		if ((*p)->num == __dest)
		{
			vs->AdjList.erase(p);
			break;
		}
	}
	// by symmetry, do for dest

	for (auto p = vd->AdjList.begin(); p != vd->AdjList.end(); p++)
	{
		if ((*p)->num == __src)
		{
			vd->AdjList.erase(p);
			break;
		}
	}
}

void graph::print_list(int __num)
{
	auto p = search_vertex(__num);
	if (p != vertices.end())
	{ // standard for loop for traversing linked list
		for (auto adj = p->AdjList.begin(); adj != p->AdjList.end(); ++adj)
		{
			std::cout << "->" << (*adj)->num;
		}

	}
}
void graph::print_graph()
{
	for (auto p = vertices.begin(); p != vertices.end(); p++)
	{
		print_list(p->num);
		std::cout << "\n";
	}

}

void graph::delete_list(int __num)
{
	auto p = search_vertex(__num);
	if (p != vertices.end())
	{
		for (auto c = p->AdjList.begin(); c != p->AdjList.end(); ++c)
		{
			p->AdjList.erase(c);
		}
	}
}
//
//void delete_graph(graph *MyGraph)
//{ // delete each vertex
//	vertex *p, *temp;
//	for (temp = p = MyGraph->VertexList; p; p = temp)
//	{
//		temp = p->down;
//		delete_vertex(MyGraph, p->num);
//	}
//	free(MyGraph); //vertices aree all now recursively freed--
//// so now can free MyGraph struct
//}

void graph::delete_vertex(int __num)
{

	auto p = search_vertex(__num);
	// first selete all edges of vertex
	for (auto i = p->AdjList.begin(); i != p->AdjList.end(); p++)
	{
		delete_edge(__num, (*i)->num);
	}
	// now delete vertex itself
	vertices.erase(p);
	TotalVertices -= 1;
}

void graph::bfs(int r)
{

	auto root = search_vertex(r);

	if (root == vertices.end())
		return;
	else
	{
		root->color = "black"; // change attributes of root vertex
		root->distroot = 0;
		root->parent = nullptr;

	}
	// initialize attributes of all non-root vertices
	for (auto v = vertices.begin(); v != vertices.end(); v++)
	{
		if (v->num != r)
		{

			v->color = "white";
			v->distroot = SENTINEL;
			v->parent = nullptr;
		}

	}

queue<vertex *> my_queue(&*root);

	while (my_queue.empty() == false)
	{
		vertex *v = my_queue.pop();

		for (auto adj = v->AdjList.begin(); adj !=v->AdjList.end();  ++adj)
		{

			if ((*adj)->color == "white")
			{

				(*adj)->distroot = v->distroot + 1;
				(*adj)->parent = v;
				my_queue.push(*adj);

			}

			v->color = "black";
		}
	}

}

void print_path(graph *MyGraph, int num, int num2)
{
	vertex *s = search_vertex(MyGraph, num);
	vertex *v = search_vertex(MyGraph, num2);

	if (v == s)
		printf("%d", s->num);

	else if (v == nullptr || v->parent == nullptr)
		printf("%s\n", "No path to this vertex exists");

	else
	{
		print_path(MyGraph, s->num, v->parent->num);
		printf("%s%d", "->", v->num);
	}

}

void dfs_visit(vertex *v)
{
	v->color = "black";
	for (adjnode *n = v->AdjList; n; n = n->right)
	{
		if (strcmp(n->vertexptr->color, "white") == 0)
		{
			n->vertexptr->parent = v;
			dfs_visit(n->vertexptr);
		}
	}
}

void dfs(graph *MyGraph)
{
	for (vertex *p = MyGraph->VertexList; p; p = p->down)
	{
		p->color = "white";
		p->parent = nullptr;
	}

	for (vertex *p = MyGraph->VertexList; p; p = p->down)
	{
		if (strcmp(p->color, "white") == 0)
			dfs_visit(p);
	}

}

