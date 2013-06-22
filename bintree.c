#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// binary tree implementation
//

typedef struct node  {

    struct node *left;
    struct node *right;
    struct node *parent;
    int key;
} node;

typedef enum bool {FALSE, TRUE} bool;

void insert_node(node *root, int key);
void delete_node(node **proot, int key);
node *search(node *root, int key);
void free_tree(node *root);
void print_inorder(node *root);
void print_postorder(node *root);
void print_preorder(node *root);
node *tree_max(node *root);
node *tree_min(node *root);
node *tree_successor(node *root, int key);
node *tree_predecessor(node *root, int key);
void transplant(node **proot, node *u, node *v);
bool ancestor(node *root, node *u, node *v);
int main()
{

    node *root = calloc(1, sizeof(node)); // initialization of root struct
    node **proot = &root;
    root->key=22;
    insert_node(root, 19);
    insert_node(root, 20);
    insert_node(root, 31);
    insert_node(root, 25);
    delete_node(proot, 25);
    print_inorder(root);
    if (root) {
    free_tree(root);
    root = NULL;
    }

    return 0;
}


void insert_node(node *root, int key)
{

    if (root == NULL){ // trivial case of no tree to start
	root = calloc(1, sizeof(node));
	root->key = key;
	return;
    }

    // start of algorithm for non-empty tree

    if (key < root->key ) {

	if (root->left == NULL ) { //base case--either root->left does not exist...
	    root->left = calloc(1, sizeof(node));
	    root->left->key = key;
	    root->left->parent = root;
	}
	else
	    insert_node(root->left, key);  //inductive step
    }

    //by symmetry, rest of algorithm is very similar 

    if (key > root->key) {

	if (root->right == NULL ) { //base case--either root->left does not exist...
	    root->right = calloc(1, sizeof(node));
	    root->right->key = key;
	    root->right->parent = root;   
	}
	else 
	    insert_node(root->right, key);  //inductive step

    }
    //equal case don't do anything

}

node *search(node *root, int key) {

    if (!root){ //trivial case of no tree--also handles not finding a key and no right or left subtree
	return NULL;
    }

    if (key < root->key  )  // search left subtree
	return search(root->left, key );

    else if (key > root->key )  // search right subtree
	return search(root->right, key);

    else if (key == root->key) { //aha, found key
	return root;
    }

    else
	return NULL; //haven't found key and have traversed whole tree

    /*else if (key != root->key && root->left == NULL && root->right == NULL) */
    /*return NULL; //haven't found key--and no right or left subtree*/
}


void free_tree(node *root)
{
    // base case
    if (root->left) 
	free_tree(root->left);

    if (root->right) 
	free_tree(root->right);

    root->left =NULL;
    root->right = NULL;
    root->parent = NULL;
    free(root);
}


void delete_node(node **proot, int key) {
    node *root = *proot;
    // we will need a pointer to pointer to later on set nodetoDel to NULL, 
    //due to variables being passed by value in C
    node *nodetoDel = search(root, key);



    //trivial case of no tree or node not existing in tree. Don't do anything

    // if nodetoDel has no children
    if (!(nodetoDel->left ) && !(nodetoDel->right)) {
	if (root != nodetoDel) {
	transplant(proot, nodetoDel, NULL);
	}
	// we will be freeing nodetoDel at the
	// end of code--don't want root to be set to NULL here if it's only element
    }

    // if nodetoDel has one child, we replace nodetoDel with its child

    else if (!(nodetoDel->left ) && nodetoDel->right ) //only child nodetoDel has is right
	transplant(proot, nodetoDel, nodetoDel->right);

    else if (nodetoDel->left  && !(nodetoDel->right) )  //only child nodetoDel has is left
	transplant(proot, nodetoDel, nodetoDel->left);



    // if nodetoDel has two children--complicated. 
    // Two cases: 

    // 1) nodetoDel's successor is it's right child. If so, we delete nodetoDel 
    // and replace it with it's right child subtree

    else if (nodetoDel->right && !(nodetoDel->right->left)) { // implies right child of NodetoDel is successor
	transplant(proot, nodetoDel, nodetoDel->right);
	nodetoDel->right->left = nodetoDel->left; // replacement node assigned left child of nodetoDel   
    }    

    // 2) nodetoDel's successor is in the left subtree of it's right child.
    // If so, replace successor position in tree with its right subtree, and replace nodetoDel position with successor  
    else if (nodetoDel->right && nodetoDel->right->left  ) {


	node *y = tree_successor(root, nodetoDel->key); // find successor of nodetoDel

	// replace successor position in tree with its only subtree
	transplant(proot, y , y->right);



	// replace nodetoDel with y
	transplant(proot, nodetoDel, y);
	y->left = nodetoDel->left;  // y has no left subtree by design--now assign nodetoDel's left tree to it
	y->left->parent=y;
      if (nodetoDel->right)  // we transferred a single node--now attach nodetoDel's right tree to it
	  y->right = nodetoDel->right;
      else 
	    y->right = NULL;   
      
      }
      	
    // setting pointer to NULL doesn't do anything--nodetoDel is passed by value to calling function
    free(nodetoDel);
    nodetoDel=NULL;
}






void print_inorder(node *root) {
    if (!root) //trivial case--don't have a tree
	return;  

    print_inorder(root->left ); //inductive step
    printf("%d\n", root->key); // base case
    print_inorder(root->right );

}


void print_postorder(node *root) {
    if (!root) //trivial case--don't have a tree
	return;  

    print_postorder(root->left ); //inductive step
    print_postorder(root->right );
    printf("%d\n", root->key); // base case

}


void print_preorder(node *root) {
    if (!root) //trivial case--don't have a tree
	return;  

    printf("%d\n", root->key); // base case
    print_preorder(root->left ); //inductive step
    print_preorder(root->right );

}


node *tree_max(node *root)
{
    while(root->right != NULL ) {
	root=root->right;
    }
    return root;
}


node *tree_min(node *root)
{
    while(root->left != NULL ) {
	root=root->left;
    }
    return root;
}


node *tree_successor(node *root, int key)
{
    node *x = search(root, key);


    /*if x has a right member, then the max member of its left subtree is its successor--easy case*/

    if (x->right ) {
	if (x->right->left)
	    return tree_max(x->right->left);

	else 
	    return x->right;  
    }

    // now we handle the case where x doesn't have a right member.
    // Its successor will be the first ancestor of x with a left child.

    node * y = x->parent;
    while(y != NULL && y->left != x  ) { 

	x = y;
	y = y->parent; 
    }
    if (y == NULL) {

	printf("%s\n", "This is the maximal element of the tree---no successor. Program may crash");
	return NULL;
    }
    else
	return y;
}





node *tree_predecessor(node *root, int key)
{
    node *x = search(root, key);

    // if x has a left member, then the min member of its subtree is its predecessor--easy case

    if (x->left ) { 

	return tree_min(x->left);  
    }

    // now we handle the case where x doesn't have a left member.
    // Its predecessor will be the first ancestor of x with a right child.

    node * y = x->parent;
    while(y != NULL && y->right != x  ) { 

	x = y;
	y = y->parent; 
    }
    if (y == NULL) {

	printf("%s\n", "This is the least element of the tree---no predecessor. Program may crash");
	return NULL;
    }
    else
	return y;
}

void transplant(node **root, node *u, node *v) {

    if (!u) {} 

    else if (!(u->parent )) { // u is root of tree
	*root = v;
    }
    else  {     //u isn't root
	if (v && v->parent) {
	    v->parent = u->parent;
	}
    if (u->parent->left == u) 
	u->parent->left = v;
    else 
	u->parent->right = v;
}
}





bool ancestor(node *root, node *u, node *v) {


    while(v) {
	if (v->parent == u ) 
	    return TRUE;
	else
	    v = v->parent; 
    } 

    return FALSE;

}


