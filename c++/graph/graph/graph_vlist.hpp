// graph implementation with array of pointers to linked lists

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using std::string;
using std::vector;
using std::list;
using std::deque;
using std::cout;

const int SENTINEL = -1;

class vertex
{
	friend class graph;
	int num;
	int distroot;
	string color;
	vertex *parent;
	list<vertex *> AdjList;

public:
	// constructors
	vertex(int __num, int __distroot, string __color, vertex *__parent) :
			num(__num), distroot(__distroot), color(__color), parent(__parent)
	{
	}
	vertex(int __num) :
			num(__num), distroot(SENTINEL), color("white"), parent(nullptr)
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
	void dfs_visit(vertex &__v);
	void dfs();
	int max_vertex();
	list<vertex>::iterator search_vertex(int __num);
	void print_path(int __num, int __num2);
};

int graph::TotalVertices = 0;

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
			cout << "->" << (*adj)->num;
		}

	}
}
void graph::print_graph()
{
	for (auto p = vertices.begin(); p != vertices.end(); p++)
	{
		print_list(p->num);
		cout << "\n";
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

	deque<vertex *> my_deque(1,&*root);

	while (my_deque.empty() == false)
	{
		vertex *v = my_deque.front();
		my_deque.pop_front();

		for (auto adj = v->AdjList.begin(); adj != v->AdjList.end(); ++adj)
		{

			if ((*adj)->color == "white")
			{

				(*adj)->distroot = v->distroot + 1;
				(*adj)->parent = v;
				my_deque.push_front(*adj);

			}

			v->color = "black";
		}
	}

}

void graph::print_path(int num, int num2)
{
	auto s = search_vertex(num);
	auto v = search_vertex(num2);

	if (v == s)
		cout << s->num;

	else if (v == vertices.end() || v->parent == nullptr)
		cout << "No path to this vertex exists";

	else
	{
		print_path(s->num, v->parent->num);
		cout << "->" << v->num;
	}

}

void graph::dfs_visit(vertex &v)
{
	v.color = "black";
	for (auto n = v.AdjList.begin(); n != v.AdjList.end(); n++)
	{
		if ((*n)->color == "white")
		{
			(*n)->parent = &v;
			dfs_visit(**n);
		}
	}
}

void graph::dfs()
{
	// initialize all vertices
	for (auto p = vertices.begin(); p != vertices.end(); ++p)
	{
		p->color = "white";
		p->parent = nullptr;
	}

	for (auto p = vertices.begin(); p != vertices.end(); ++p)
	{
		if (p->color == "white")
			dfs_visit(*p);
	}

}

