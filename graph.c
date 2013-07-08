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
void delete_edge(graph *MyGraph, int src, int dest);

void print_graph(graph *MyGraph);
void print_list(graph *MyGraph, int num);
void delete_list(graph *MyGraph, int num);
void delete_graph(graph *MyGraph);


int main()

{
    graph *MyGraph=create_graph(5);
    add_edge(MyGraph, 3, 4);
    add_vertex(MyGraph);
    add_edge(MyGraph, 3, 5);
    /*delete_edge(MyGraph, 3, 5);*/
    delete_edge(MyGraph, 3, 4);
    print_graph(MyGraph);
    delete_graph(MyGraph);
    MyGraph=NULL;
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

    if (MyGraph->AdjArray[src] == NULL || MyGraph->AdjArray[dest] == NULL ) {
        printf("%s\n", "One or both vertices don't exist");
    }

    else {




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
}

void delete_edge(graph *MyGraph, int src, int dest) {
    if (MyGraph->AdjArray[src] == NULL || MyGraph->AdjArray[dest] == NULL ) {
        printf("%s\n", "One or both vertices don't exist");
    }
    else { // go along linked list, and delete a node
        node *p, *c;  
        for (c = MyGraph->AdjArray[src]; c; p=c, c=c->next) {
            if (c && c->num == dest ) {
                p->next = c->next;
                free(c);
                break;
            }
            else if (!c) {
                printf("%s\n", "You are trying to delete an edge that doesn't exist. Enter in another edge.");
                break;
            }

        }
        // by symmetry, repeat above code
        for (c = MyGraph->AdjArray[dest]; c; p=c, c=c->next) {
            if (c && c->num == src ) {
                p->next = c->next;
                free(c);
                break;
            }
            else if (!c) {
                printf("%s\n", "You are trying to delete an edge that doesn't exist. Enter in another edge.");
                break;
            }

        }
    }
}



void print_list(graph *MyGraph, int num) {
    if (num >= MyGraph->TotalVertices || !MyGraph) 
        printf("%s\n","Error: Vertex does not exist");
    else { // standard for loop for traversing linked list
        for (node *p = MyGraph->AdjArray[num]; p; p = p->next) {
            if (p->next) 
                printf("%d""%s", p->num, "->");
            else
                printf("%d", p->num);
        }

    }
}
void print_graph(graph *MyGraph) {

    if (MyGraph) {
        for (int i = 0; i < MyGraph->TotalVertices; ++i) {
            print_list(MyGraph, i);
            if ((i+1) < MyGraph->TotalVertices) {
                printf("\n");
            }

        }

    }
    else
        printf("%s\n", "Graph does not exist");
}


void delete_list(graph *MyGraph, int num) {
    node *c;  
    for (c = MyGraph->AdjArray[num]; c; c=c->next) {
        free(c);
    }
}

void delete_graph(graph *MyGraph) {
    for (int i = 0; i < MyGraph->TotalVertices; ++i) {
        delete_list(MyGraph, i);
    }
    free(MyGraph->AdjArray);
    free(MyGraph);
}

