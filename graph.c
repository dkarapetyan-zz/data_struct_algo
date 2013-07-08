// graph implementation with array--suboptimal but quick

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int num;
    struct node *next;
} node;

typedef struct graph {

    node **AdjArray;
    int TotalVertices;
} graph;


graph *create_graph(int v);
void add_vertex(graph *MyGraph);
void add_edge(graph *MyGraph, int src, int dest);
void print_graph(graph *MyGraph);
void print_list(graph *MyGraph, int num);
int main()

{
    graph *MyGraph=create_graph(5);
    add_edge(MyGraph, 3, 4);
    add_vertex(MyGraph);
    print_graph(MyGraph);
    return 0;
}



graph *create_graph(int v) { // put graph on heap

    graph *MyGraph = (graph *)  malloc(sizeof(graph));

    // initialize array of structures (array going downwards), each with possible adjency linked list going to right
    MyGraph->AdjArray = malloc(sizeof(node *) * v);

    for (int i = 0; i < v; ++i) {
        MyGraph->AdjArray[i] = malloc(sizeof(node));
    }

    for (int i = 0; i < v; ++i) {
        MyGraph->AdjArray[i]->num = i;
        MyGraph->AdjArray[i]->next = NULL;
    }
    MyGraph->TotalVertices = v;

    return MyGraph;
}
void add_vertex(graph *MyGraph) {
    int k = MyGraph->TotalVertices;
    MyGraph->AdjArray[k] = malloc(sizeof(node));
    MyGraph->AdjArray[k]->next=NULL;
    MyGraph->AdjArray[k]->num=k;
    MyGraph->TotalVertices+=1;
}



void add_edge(graph *MyGraph, int src, int dest) {

    // add new dest node at start of linked list for vertex 'src'
    node *temp = MyGraph->AdjArray[src]->next;
    MyGraph->AdjArray[src]->next = malloc(sizeof(node));
    MyGraph->AdjArray[src]->next->next = temp; 
    MyGraph->AdjArray[src]->next->num = dest;   

    // by symmetry, must do same for linked list for vertex 'dest'
    temp = MyGraph->AdjArray[dest]->next;
    MyGraph->AdjArray[dest]->next = malloc(sizeof(node));
    MyGraph->AdjArray[dest]->next->next = temp;
    MyGraph->AdjArray[dest]->next->num = src;   
}


void print_list(graph *MyGraph, int num) {
    if (num >= MyGraph->TotalVertices || !MyGraph) 
        printf("%s\n","Error: Vertex does not exist");
    else { // standard for loop for traversing linked list
        for (node *p = MyGraph->AdjArray[num]; p; p = p->next) {
            if (p->next) 
                printf("%d""%s", p->num, "->");
            else
                printf("%d\n", p->num);
        }

    }
}
void print_graph(graph *MyGraph) {

    if (MyGraph) {
        for (int i = 0; i < MyGraph->TotalVertices; ++i) {
            print_list(MyGraph, i);
        }

    }
    else
        printf("%s\n", "Graph does not exist");
}
