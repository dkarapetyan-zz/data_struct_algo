// graph implementation with array of pointers to linked lists

#include <stdio.h>
#include <stdlib.h>

struct adjnode;

typedef struct vertex {
    int num;
    char *color;
    struct vertex *parent;
    struct adjnode *AdjList;
    struct vertex *down;

} vertex;


typedef struct adjnode{
vertex *vertexptr;
struct adjnode *right;
}
adjnode;



typedef struct graph {

    vertex *VertexList;
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
    if (v <=0) 
        return NULL;

    else {
        graph *MyGraph = malloc(sizeof(graph));

        // initialize linked list of vertices (linked list going downwards), each with possible adjency linked list going to right
        vertex *p = MyGraph->VertexList = malloc(sizeof(vertex)); 
        for (int i = 1; i < v; ++i, p = p->down) {
            p->down = malloc(sizeof(vertex));
            p->down->num = i;
            p->down->AdjList = NULL;
            p->down->parent = NULL;
            p->down->color = "white"; 
        }
        MyGraph->TotalVertices = v;

        return MyGraph;
    }
}
int max_vertex(graph *MyGraph){
vertex *p = MyGraph->VertexList;
int k=0;
while(p) {
if (k < (p->num)) 
k = p->num;
}
return k;
}

vertex *search_vertex(graph *MyGraph, int num) {
 vertex *p = MyGraph->VertexList;
    while(p) { // traverse to end of linked list
    if (p->num ==num)
        return p;
    }
    return NULL;
}

void add_vertex(graph *MyGraph) {
    int k = max_vertex(MyGraph) +1;
    vertex *p;
    p  = MyGraph->VertexList;
    while(p->down) { // traverse to end of linked list
    p = p->down; 
    }
    p->down = malloc(sizeof(vertex));
    p->down->num = k;
    p->down->AdjList = NULL;
    p->down->parent = NULL;
    p->down->color = "white"; 
    MyGraph->TotalVertices+=1;
}



void add_edge(graph *MyGraph, int src, int dest) {

    vertex *vs = search_vertex(MyGraph, src);
    vertex *vd = search_vertex(MyGraph, dest);

    if (vs && vd ) {

        // add new dest node at start of linked list for vertex 'src'
      adjnode *temp =  vs->AdjList;
      vs->AdjList = malloc(sizeof(adjnode));
      vs->AdjList->right = temp;
      vs->AdjList->vertexptr = vd;   

       
        // by symmetry, must do same for linked list for vertex 'dest'
      temp =  vd->AdjList;
      vd->AdjList = malloc(sizeof(adjnode));
      vd->AdjList->right = temp;
      vd->AdjList->vertexptr = vs;   
    }
}

void delete_edge(graph *MyGraph, int src, int dest) {
    vertex *vs = search_vertex(MyGraph, src);
    vertex *vd = search_vertex(MyGraph, dest);

    if (vs && vd) { // go along linked list, and delete a node
        adjnode *p, *c;  
        for (p = c = vs->AdjList; c; p=c, c=c->right) {
            if (c->vertexptr->num == dest ) {
                if (c == vs->AdjList) { 
                    vs->AdjList = c->right;
                    free(c);
                    break;
                }
                else { 
                    p->right = c->right;
                    free(c);
                    break;
                }
            }
        }
        // by symmetry, repeat above code
        for (p = c = vd->AdjList; c; p=c, c=c->right) {
            if (c->vertexptr->num == src ) {
                if (c == vd->AdjList) { 
                    vd->AdjList = c->right;
                    free(c);
                    break;
                }
                else { 
                    p->right = c->right;
                    free(c);
                    break;
                }
            }
        }            
    }
}


void print_list(graph *MyGraph, int num) {
    vertex *p = search_vertex(MyGraph, num);
    if (p && !MyGraph) { // standard for loop for traversing linked list
        printf("%d", p->num);
        for (adjnode *adj = p->AdjList; adj; adj = adj->right) {
                printf("%s%d", "->", adj->vertexptr->num);
        }

    }
}
void print_graph(graph *MyGraph) {

    if (MyGraph) {
        vertex *p = MyGraph->VertexList;
        for (int i = 0; p; ++i, p = p->down) {
            print_list(MyGraph, i);
                printf("\n");
        }

    }
    else
        printf("%s\n", "Graph does not exist");
}


void delete_list(graph *MyGraph, int num) {
    vertex *p = search_vertex(MyGraph, num);
    if (p) {
        adjnode *c, *temp;
        for (c = temp = p->AdjList; c; c=temp ) {
            temp = c->right;
            free(c);
        }
        p->AdjList=NULL;
    }
}

void delete_graph(graph *MyGraph) {
    vertex *p, *temp;
    p=temp=MyGraph->VertexList;
    for (int i = 0; p; ++i, p=temp) {
            delete_list(MyGraph, i);
            // aren't using delete_vertex because it changes TotalVertices variable,
            // causing complications in code
            temp = p->down; 
            free(p);
        }
    free(MyGraph);
}

void delete_vertex(graph *MyGraph, int num)
{
    if (!MyGraph) 
        printf("%s\n", "Graph does not exist");

    else {
        vertex *p = MyGraph->VertexList;
        // delete all edges of vertex
        for (int i = 0; p; ++i, p = p->down) {
            delete_edge(MyGraph, num, i);
        }
        delete_list(MyGraph, num);
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
    /*head->right=NULL;*/
    /*tail = head;*/
  /*}*/
  /*else {*/
    /*node *p = malloc(sizeof(node));*/
    /*p->right=tail;*/
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
  /*head = head->right;*/
  /*free(p); // free memory that still has data from old dequeueed head*/
  /*p = NULL; // avoid program having any dangerous unassigned pointers*/
  /*return head; //return new head*/
/*}*/
