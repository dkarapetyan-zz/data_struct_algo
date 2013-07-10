// graph implementation with array of pointers to linked lists

#include <stdio.h>
#include <stdlib.h>

struct adjnode;

typedef struct vertex {
    int num;
    char *color;
    struct vertex *parent;
    struct adjnode *AdjList;

} vertex;


typedef struct adjnode{
vertex *vertexptr;
struct adjnode *next;
}
adjnode;



typedef struct graph {

    vertex **VertexArray;
    int TotalVertices;
} graph;


vertex *head = NULL; // head of queue
vertex *tail = NULL; // tail of queue

graph *create_graph(int v);
void add_vertex(graph *MyGraph);
void add_edge(graph *MyGraph, int src, int dest);
void delete_edge(graph *MyGraph, int src, int dest);
void delete_vertex(graph *MyGraph, int num);
void print_graph(graph *MyGraph);
void print_list(graph *MyGraph, int num);
void delete_list(graph *MyGraph, int num);
void delete_graph(graph *MyGraph);
void bfs(graph *MyGraph);

int main()

{
    graph *MyGraph=create_graph(5);
    add_edge(MyGraph, 3, 4);
    add_vertex(MyGraph);
    add_edge(MyGraph, 3, 5);
    /*[>delete_edge(MyGraph, 3, 5);<]*/
    /*[>delete_edge(MyGraph, 3, 4);<]*/
    delete_vertex(MyGraph, 3);
    /*print_graph(MyGraph);*/
    delete_graph(MyGraph);
    /*MyGraph=NULL;*/
    return 0;
}



graph *create_graph(int v) { // put graph on heap

    graph *MyGraph = malloc(sizeof(graph));

    // initialize array of structures (array going downwards), each with possible adjency linked list going to right
    MyGraph->VertexArray = malloc(sizeof(vertex *) * v);

    for (int i = 0; i < v; ++i) {
        MyGraph->VertexArray[i] = malloc(sizeof(vertex));
    }

    for (int i = 0; i < v; ++i) {
        MyGraph->VertexArray[i]->num = i;
        MyGraph->VertexArray[i]->AdjList = NULL;
        MyGraph->VertexArray[i]->parent = NULL;
        MyGraph->VertexArray[i]->color = "white"; 
    }
    MyGraph->TotalVertices = v;

    return MyGraph;
}
void add_vertex(graph *MyGraph) {
    int k = MyGraph->TotalVertices;
    MyGraph->VertexArray = realloc(MyGraph->VertexArray, sizeof(vertex *) * (k+1));
    MyGraph->VertexArray[k] = malloc(sizeof(vertex));
    MyGraph->VertexArray[k]->AdjList=NULL;
    MyGraph->VertexArray[k]->num=k;
    MyGraph->VertexArray[k]->color="white";
    MyGraph->VertexArray[k]->parent=NULL;
    MyGraph->TotalVertices+=1;
}



void add_edge(graph *MyGraph, int src, int dest) {

    if (MyGraph->VertexArray[src] == NULL || MyGraph->VertexArray[dest] == NULL ) {
        printf("%s\n", "One or both vertices don't exist");
    }

    else {




        // add new dest node at start of linked list for vertex 'src'
      adjnode *temp =  MyGraph->VertexArray[src]->AdjList;
      MyGraph->VertexArray[src]->AdjList = malloc(sizeof(adjnode));
      MyGraph->VertexArray[src]->AdjList->next = temp;
      MyGraph->VertexArray[src]->AdjList->vertexptr = MyGraph->VertexArray[dest];   

       
        // by symmetry, must do same for linked list for vertex 'dest'
      temp =  MyGraph->VertexArray[dest]->AdjList;
      MyGraph->VertexArray[dest]->AdjList = malloc(sizeof(adjnode));
      MyGraph->VertexArray[dest]->AdjList->next = temp;
      MyGraph->VertexArray[dest]->AdjList->vertexptr = MyGraph->VertexArray[src];   
    }
}

void delete_edge(graph *MyGraph, int src, int dest) {
    if (MyGraph->VertexArray[src] == NULL || MyGraph->VertexArray[dest] == NULL ) {
        return;
    }
    else { // go along linked list, and delete a node
        adjnode *p, *c;  
        for (p = c = MyGraph->VertexArray[src]->AdjList; c; p=c, c=c->next) {
            if (c->vertexptr->num == dest ) {
                if (c == MyGraph->VertexArray[src]->AdjList) { 
                    MyGraph->VertexArray[src]->AdjList = c->next;
                    free(c);
                    break;
                }
                else { 
                    p->next = c->next;
                    free(c);
                    break;
                }
            }
        }
        // by symmetry, repeat above code
        for (p = c = MyGraph->VertexArray[dest]->AdjList; c; p=c, c=c->next) {
            if (c->vertexptr->num == src ) {
                if (c == MyGraph->VertexArray[dest]->AdjList) { 
                    MyGraph->VertexArray[dest]->AdjList = c->next;
                    free(c);
                    break;
                }
                else { 
                    p->next = c->next;
                    free(c);
                    break;
                }
            }
        }            
    }
}


void print_list(graph *MyGraph, int num) {
    if (num >= MyGraph->TotalVertices || !MyGraph) 
        return;
    else if (MyGraph->VertexArray[num]) { // standard for loop for traversing linked list
        printf("%d", MyGraph->VertexArray[num]->num);
        for (adjnode *p = MyGraph->VertexArray[num]->AdjList; p; p = p->next) {
                printf("%s%d", "->", p->vertexptr->num);
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
    if (MyGraph->VertexArray[num]) {
        adjnode *c, *temp;
        for (c = temp = MyGraph->VertexArray[num]->AdjList; c; c=temp ) {
            temp = c->next;
            free(c);
        }
        MyGraph->VertexArray[num]->AdjList=NULL;
    }
}

void delete_graph(graph *MyGraph) {
    for (int i = 0; i < MyGraph->TotalVertices; ++i) {
            delete_list(MyGraph, i);
            // aren't using delete_vertex because it changes TotalVertices variable,
            // causing complications in code
            free(MyGraph->VertexArray[i]);
        }
    free(MyGraph->VertexArray);
    free(MyGraph);
}

void delete_vertex(graph *MyGraph, int num)
{
    if (!MyGraph) 
        printf("%s\n", "Graph does not exist");

    else if (num >= MyGraph->TotalVertices)
        printf("%s\n", "Vertex does not exist");
    else {
        // delete all edges of vertex
        for (int i = 0; i < MyGraph->TotalVertices; ++i) {
            delete_edge(MyGraph, num, i);
        }
        delete_list(MyGraph, num);
        free(MyGraph->VertexArray[num]);
        MyGraph->VertexArray[num] = NULL;
        MyGraph->TotalVertices-=1;
    }
}

/*void enqueue(node * vertex)*/
/*{*/

  /*if (head==NULL) {*/
    /*head = (node *) malloc(sizeof(node));*/
    /*head->color = vertex->color;*/
    /*head->num = vertex->num;*/
    /*head->parent = vertex->parent;*/
    /*head->next=NULL;*/
    /*tail = head;*/
  /*}*/
  /*else {*/
    /*node *p = malloc(sizeof(node));*/
    /*p->next=tail;*/
    /*tail=p; // p is the new tail*/
    /*tail->color = vertex->color;*/
    /*tail->num = vertex->num;       */
    /*tail->parent=vertex->parent;*/

  /*}*/


/*}*/

/*node *dequeue(node *head)*/
/*{*/
  /*if (head == NULL) {*/
    /*return head;*/
  /*}*/
  /*node *p = head;*/
  /*head = head->next;*/
  /*free(p); // free memory that still has data from old dequeueed head*/
  /*p = NULL; // avoid program having any dangerous unassigned pointers*/
  /*return head; //return new head*/
/*}*/
