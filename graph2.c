// graph implementation with array of pointers to linked lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sentinel -1

struct adjnode;

typedef struct vertex {
    int num;
    int distroot;
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


typedef struct qnode {
    struct qnode *right;
    vertex *vertexptr;
} qnode;


qnode *head = NULL; // head of queue
qnode *tail = NULL; // tail of queue

graph *create_graph(int v);
void add_vertex(graph *MyGraph);
void add_edge(graph *MyGraph, int src, int dest);
void delete_edge(graph *MyGraph, int src, int dest);
void delete_vertex(graph *MyGraph, int num);
void print_graph(graph *MyGraph);
void print_list(graph *MyGraph, int num);
void delete_list(graph *MyGraph, int num);
void delete_graph(graph *MyGraph);
void bfs(graph *MyGraph, int r);
vertex *search_vertex(graph *MyGraph, int num); 
void print_path(graph *MyGraph, int num, int num2);
int main()

{
    graph *MyGraph=create_graph(5);
    add_edge(MyGraph, 3, 4);
    add_edge(MyGraph, 2, 1);
    add_edge(MyGraph, 2,4);
    add_edge(MyGraph, 0,3);
    add_vertex(MyGraph);
    add_edge(MyGraph, 3, 5);
    /*delete_edge(MyGraph, 3, 5);*/
    /*delete_edge(MyGraph, 3, 4);*/
    /*delete_vertex(MyGraph, 0);*/
    print_graph(MyGraph);
    bfs(MyGraph, 2);
    /*print_path(MyGraph, 2, 4);*/
    delete_graph(MyGraph);
    /*MyGraph=NULL;*/
    return 0;
}



graph *create_graph(int v) { // put graph on heap
    if (v <=0) 
        return NULL;

    else {
        graph *MyGraph = calloc(1,sizeof(graph));

        // initialize linked list of vertices (linked list going downwards), each with possible adjency linked list going to right
        vertex *p = MyGraph->VertexList = calloc(1,sizeof(vertex)); 
        for (int i = 1; i < v; ++i, p = p->down) {
            p->down = calloc(1, sizeof(vertex));
            p->down->num = i;
            p->down->color = "white"; 
        }
        MyGraph->TotalVertices = v;

        return MyGraph;
    }
}

int max_vertex(graph *MyGraph){
    int k=0;
    for (vertex *p = MyGraph->VertexList; p; p = p->down) {
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
        else
            p = p->down;
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
    p->down = calloc(1,sizeof(vertex));
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
        vs->AdjList = calloc(1,sizeof(adjnode));
        vs->AdjList->right = temp;
        vs->AdjList->vertexptr = vd;   


        // by symmetry, must do same for linked list for vertex 'dest'
        temp =  vd->AdjList;
        vd->AdjList = calloc(1,sizeof(adjnode));
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
    if (p && MyGraph) { // standard for loop for traversing linked list
        printf("%d", p->num);
        for (adjnode *adj = p->AdjList; adj; adj = adj->right) {
            printf("%s%d", "->", adj->vertexptr->num);
        }

    }
}
void print_graph(graph *MyGraph) {

    if (MyGraph) {
        for (vertex *p = MyGraph->VertexList; p; p = p->down) {
            print_list(MyGraph, p->num);
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

void delete_graph(graph *MyGraph) { // delete each vertex
    vertex *p, *temp;
    for (temp = p = MyGraph->VertexList; p;  p = temp) {
        temp = p->down; 
        delete_vertex(MyGraph, p->num);
    }
    free(MyGraph); //vertices aree all now recursively freed--
    // so now can free MyGraph struct
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
        p = MyGraph->VertexList;
        if (p->num == num) { // if start of linked list is to be deleted
            MyGraph->VertexList = p->down;
            free(p);
        }

        else {
            for (; p; p = p->down) { // find vertex before one to be deleted
                if (p->down->num == num) {
                    break;
                }
            }
            if (p) {
                vertex *temp = p->down;
                p->down = p->down->down;
                free(temp);
            }
        }
        MyGraph->TotalVertices-=1;
    }
}

void enqueue(vertex *v)
{

    if (head==NULL) {
        head = calloc(1,sizeof(qnode));
        head->vertexptr = v;
        tail = head;
    }
    else {
        qnode *p = calloc(1,sizeof(qnode));
        tail->right = p; // insert p 
        tail = p; // p is the new tail
    }


}

vertex *dequeue()
{
    if (head == NULL) {
        return NULL;
    }
    qnode *p = head;
    vertex *v = head->vertexptr;
    p = head;    
    v = head->vertexptr;
    head = head->right;
    free(p); // free memory that still has data from old dequeueed head
    return v; //return popped vertex 
}

void bfs(graph *MyGraph, int r) {

    vertex *root, *v;
    root = v = NULL;
    for (v = MyGraph->VertexList; v  ; v = v->down) {
        if (v->num != r) { // change attributes of all non-root vertices

            v->color = "white";
            v->distroot = sentinel;
            v->parent = NULL;
        }
        else
            root  = v; // store root vertex
    }
    if (root) { // don't return anything if root doesn't exist

        root->color = "black"; // change attributes of root vertex
        root->distroot = 0;
        root->parent = NULL;

        enqueue(root);

        while(head) {
            vertex *v = dequeue();

            for (adjnode *adj = v->AdjList; adj; adj = adj->right) {

                if (strcmp(adj->vertexptr->color,"white")) {

                    adj->vertexptr->distroot=v->distroot +1;
                    adj->vertexptr->parent = v;
                    enqueue(adj->vertexptr);

                }

                v->color = "black";
            }
        }


    }
}

void print_path(graph *MyGraph, int num, int num2) {
    vertex *s = search_vertex(MyGraph, num);
    vertex *v = search_vertex(MyGraph, num2);
    if (v == s) {
        printf("%d", s->num);
    }
    else if (v->parent == NULL)
        printf("%s\n", "No path to this vertex exists");

    else {

        print_path(MyGraph, s->num, v->parent->num);
        printf("%d", v->num);
    }

}

