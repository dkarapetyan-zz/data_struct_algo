#include <stdio.h>
#include <stdlib.h>


// binary tree implementation
//

typedef struct node  {

    struct node *left;
    struct node *right;
    struct node *parent;
    int key;
} node;


void insert_node(node *root, int key);
node *delete_node(node *root, int key);
node *search(node *root, int key);
void free_tree(node *root);
void print_inorder(node *root);
void print_postorder(node *root);
void print_preorder(node *root);
node *tree_max(node *root);
node *tree_min(node *root);
node *tree_successor(node *root, int key);
node *tree_predecessor(node *root, int key);
int main()
{

    node *root = calloc(1, sizeof(node)); // initialization of root struct
    root->key=22;
    insert_node(root, 19);
    insert_node(root, 20);
    insert_node(root, 31);
    insert_node(root, 25);
    root = delete_node(root, 25);
    print_inorder(root);
    if (!root) {
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




// wrong insert_node algorithm--makes a tree with root--and two branches, one to left, one to right

/*void insert_node(node *root, int key) {*/

/*if (root == NULL){ // trivial case of no tree to start*/
/*root = calloc(1, sizeof(node));*/
/*root->key = key; */
/*return;*/
/*}*/

/*if (key < root->key ) {*/

/*if (root->left == NULL ) { //base case--either root->left does not exist...*/
/*root->left = calloc(1, sizeof(node));*/
/*root->left->key = key;*/
/*root->left->parent = root;     */
/*}*/
/*else if (root->left !=NULL && key > root->left->key ) { // or node lies between root and root->left*/
/*node *newnode = calloc(1, sizeof(node));*/

/*newnode->left = root->left;*/
/*root->left->parent = newnode;*/
/*root->left = newnode;*/
/*newnode->parent = root;*/
/*newnode->key=key;  */
/*}*/
/*else*/
/*insert_node(root->left, key); //inductive step*/
/*}*/
/*if (key > root->key) {*/

/*if (root->right == NULL ) { //base case--either root->left does not exist...*/
/*root->right = calloc(1, sizeof(node));*/
/*root->right->key = key; */
/*root->right->parent = root;    */
/*}*/
/*else if (root->right!= NULL && key < root->right->key ) { // or node lies between root and root->right*/
/*node *newnode = calloc(1, sizeof(node));*/

/*newnode->right = root->right;*/
/*root->right->parent = newnode;*/
/*root->right = newnode;*/
/*newnode->parent = root;*/
/*newnode->key=key;  */
/*}*/
/*else*/
/*insert_node(root->right, key); //inductive step*/
/*}*/
/*//equal case don't do anything*/

/*}*/
node *search(node *root, int key) {

    if (!root){ //trivial case of no tree--also handles not finding a key and no right or left subtree
	return NULL;
    }

    if (key < root->key  )  // search left subtree
	return search(root->left, key );

    else if (key > root->key )  // search right subtree
	return search(root->right, key);

    else if (key == root->key) //aha, found key
	return root;

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


node *delete_node(node *root, int key) {

    node *nodetoDel = search(root, key);



    if (!root || !nodetoDel) //trivial case of no tree or node not existing in tree
	return NULL;

    // if nodetoDel has no children, we delete it and have its parent point to NULL
    if (!(nodetoDel->left) && !(nodetoDel->right)) {
	if (!(nodetoDel->parent)) { // root node
	    free(nodetoDel);
	    return NULL;
	}

	else if (nodetoDel->parent->right == nodetoDel) {
	    nodetoDel->parent->right = NULL; 
	    free(nodetoDel);
	    return root;
	}
	else {
	    nodetoDel->parent->left = NULL; 
	    free(nodetoDel);
	    return root;
	}


    }// observe that this also handles case of tree with only one element

    // if nodetoDel has one child, we replace nodetoDel with its child
    //
    else if (!(nodetoDel->left ) && nodetoDel->right ) { //only child nodetoDel has is right
	if (!(nodetoDel->parent)) { //nodetoDel is root of tree
	    nodetoDel->right->parent=NULL;
	    return nodetoDel->right; 
	}


	else if (nodetoDel->parent->left == nodetoDel  ) 
	    nodetoDel->parent->left=nodetoDel->right;

	else
	    nodetoDel->parent->right = nodetoDel->right;

	free(nodetoDel);
	return root;
    }

    else if (nodetoDel->left  && !(nodetoDel->right) ) {

	if (!(nodetoDel->parent)) {  //nodetoDel is root of tree
	    nodetoDel->left->parent=NULL;
	    return nodetoDel->left;
	}

	else if (nodetoDel->parent->right == nodetoDel  ) 
	    nodetoDel->parent->right=nodetoDel->left;

	else
	    nodetoDel->parent->left = nodetoDel->left;       


	free(nodetoDel);
	return root;
    }

    // if nodetoDel has two children--complicated. 
    // Two cases: 

    // 1) nodetoDel's successor is it's right child. If so, we delete nodetoDel 
    // and replace it with it's right child subtree

    else if (nodetoDel->right && !(nodetoDel->right->left)) { // implies right child of NodetoDel is successor
	if (nodetoDel->parent == NULL ) { // we are deleting root
	    node *newRoot  = nodetoDel->right; 
	    newRoot->left = nodetoDel->left; 
	    free(nodetoDel);
	    return root->right; 
	}
	else { //we are not deleting root
	    nodetoDel->parent->right = nodetoDel->right;
	    nodetoDel->right->parent = nodetoDel->parent;     
	    free(nodetoDel);
	    return root;
	}
    }

    // 2) nodetoDel's successor is in the left subtree of it's right child.
    // If so, replace successor position in tree with its right subtree, and replace nodetoDel position with successor  
    else if (nodetoDel->right && nodetoDel->right->left  ) {


	node *y = tree_successor(root, nodetoDel->key); // find successor of nodetoDel
	/*while(y->left != NULL ) { // find successor of nodetoDel*/
	/*y = y->left;*/
	/*}*/
	if (y->right ) {     // y has a subtree
	    y->parent->left  = y->right; // replace successor position in tree with its only subtree
	}
	else // y doesn't have a subtree
	    y->parent->left = NULL;  


	// replace nodetoDel with y
	if (!(nodetoDel->parent)) //nodetoDel is root
	    y->parent = NULL;

	else {
	    y->parent = nodetoDel->parent;

	    if (nodetoDel->parent->right == nodetoDel)
		nodetoDel->parent->right = y;

	    else
		nodetoDel->parent->left = y;
	}

	y->right = nodetoDel->right;
	y->left = nodetoDel->left;
	nodetoDel->left->parent = y;
	nodetoDel->right->parent = y;  

	if (!(nodetoDel->parent)) { //nodetoDel is root
	    free(nodetoDel);
	    return y;     
	}
	else {
	    free(nodetoDel);
	    return root;
	}

    }
    return NULL;
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


