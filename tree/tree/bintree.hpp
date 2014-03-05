#include <string>
#include <iostream>
#include <cmath>
// binary tree implementation
//

class node {
    friend class tree;

    private:

    node *left;
    node *right;
    node *parent;
    float data;

    public:
    node(): left(nullptr), right(nullptr), parent(nullptr), data(NAN){};
    node(node* _left, node* _right, node* _parent, int _data):
        left(_left), right(_right), parent(_parent), data(_data){};
};

class tree
{
    private:
        static size_t tree_size;
        node * root;
        void insert_node(node * __root, int _data);
        node *search(node *__root, int __data);
        void print_inorder(node* __root);
        void print_postorder(node* __root);
        void print_preorder(node* __root);
        void transplant(node *u, node *v);
        node *tree_max(node * __root);
        node *tree_min(node * __root);


    public:
        tree(int __data)
        {
            root = new node(nullptr, nullptr, nullptr, __data);
        }
        void insert_node(int _data);
        void delete_node(int _data);
        node *search(int _data);
        void print_inorder();
        void print_postorder();
        void print_preorder();
        node *tree_max();
        node *tree_min();
        node *tree_successor(int _data);
        node *tree_predecessor(int _data);
        bool is_ancestor(node *u, node *v);
        node *low_com_ancestor(node *u, node *v);

};

void tree::insert_node(node *__root, int __data)
{

    if (__data == __root->data)
        return;

    else if (__data < __root->data )
    {

        if (__root->left == nullptr ) //base case--either __root->left does not exist...
            __root->left = new node(nullptr, nullptr, __root, __data);
        else
            insert_node(__root->left, __data);  //inductive step
    }

    //by symmetry, rest of algorithm is very similar 

    else 
    {
        if (__root->right == nullptr )  //base case--either __root->right does not exist...
            __root->right = new node(nullptr, nullptr, __root, __data);
        else
            insert_node(__root->right, __data);  //inductive step
    }
}

void tree::insert_node(int __data)
{
    insert_node(root, __data);
}


node *tree::search(node *__root, int __data)
{

    if (!__root) //trivial case of no tree--also handles not finding a __data and no right or left subtree
        return nullptr;

    else if (__data < __root->data  )  // search left subtree
        return search(__root->left, __data );

    else if (__data > __root->data )  // search right subtree
        return search(__root->right, __data);

    else  //aha, found __data
        return __root;
}

node *tree::search(int __data)
{
    return search(root, __data);
}


void tree::delete_node(int data) {
    node *nodetodel = search(data);



    //trivial case of no tree or node not existing in tree. Don't do anything

    // if nodetodel has no children
    if (!(nodetodel->left ) && !(nodetodel->right)) 
        transplant(nodetodel, nullptr);

    // if nodetodel has one child, we replace nodetodel with its child

    else if (!(nodetodel->left ) && nodetodel->right ) //only child nodetodel has is right
        transplant(nodetodel, nodetodel->right);

    else if (nodetodel->left  && !(nodetodel->right) )  //only child nodetodel has is left
        transplant(nodetodel, nodetodel->left);



    // if nodetodel has two children--complicated. 
    // Two cases: 

    // 1) nodetodel's successor is it's right child. If so, we delete nodetodel 
    // and replace it with it's right child subtree

    else if (nodetodel->right && !(nodetodel->right->left)) // implies right child of NodetoDel is successor
    {
        node *replacement = nodetodel->right;
        transplant(nodetodel, replacement);
        replacement->left = nodetodel->left; // replacement node assigned left child of nodetodel   
    }    

    // 2) nodetodel's successor is in the left subtree of it's right child.
    // If so, replace successor position in tree with its right subtree, and replace nodetodel position with successor  
    else if (nodetodel->right && nodetodel->right->left  ) {


        node *y = tree_successor(nodetodel->data); // find successor of nodetodel

        // replace successor position in tree with its only subtree
        transplant(y , y->right);



        // replace nodetodel with y
        transplant(nodetodel, y);
        nodetodel->left->parent = y;
        y->left = nodetodel->left;  // y has no left subtree by design--now assign nodetodel's left tree to it
        y->right = nodetodel->right;
    }
}






void tree::print_inorder(node *__root)
{
    if (!__root) //trivial case--don't have a tree
        return;  

    print_inorder(__root->left); //inductive step
    std::cout << __root->data <<"\n"; // base case
    print_inorder(__root->right);

}

void tree::print_inorder()
{
    print_inorder(root);
}

void tree::print_postorder(node *__root) {
    if (!__root) //trivial case--don't have a tree
        return;  

    print_postorder(__root->left ); //inductive step
    print_postorder(__root->right );
    std::cout << __root->data << "\n"; // base case

}

void tree::print_postorder()
{
    print_postorder(root);
}

void tree::print_preorder(node *__root)
{
    if (!__root) //trivial case--don't have a tree
        return;  

    std::cout << __root->data << "\n"; // base case
    print_preorder(__root->left ); //inductive step
    print_preorder(__root->right );

}

void tree::print_preorder()
{
    print_preorder(root);
}


node *tree::tree_max()
{
    node *__root = root;
    while(__root->right != nullptr )
        __root=__root->right;
    return __root;

}

node *tree::tree_max(node *__root)
{

    while(__root->right != nullptr )
        __root=__root->right;

    return __root;
}

node *tree::tree_min()
{
    node *__root = root;
    while(__root->left != nullptr )
        __root=__root->left;

    return __root;
}

node *tree::tree_min(node *__root)
{
    while(__root->left != nullptr )
        __root=__root->left;

    return __root;
}


node *tree::tree_successor(int data)
{
    node *x = search(root, data);

    if (x ==nullptr)
        return nullptr;

    /*if x has a right member, then the min member of its right subtree is its successor--easy case*/

    else if (x->right ) 
        return tree_min(x->right);

    // now we handle the case where x doesn't have a right member.
    // Its successor will be the first ancestor of x with a left child.
    else
    {
        if (x == root)
            return x;

        else
        {
            for (;  x->parent->left==nullptr; x = x->parent)
                ;

            return x->parent;
        }
    }
}





node *tree::tree_predecessor(int data)
{
    node *x = search(root, data);

    if (x ==nullptr)
        return nullptr;

    /*if x has a left member, then the max member of its left subtree is its successor--easy case*/

    else if (x->left ) 
        return tree_max(x->left);

    // now we handle the case where x doesn't have a left member.
    // Its predecessor will be the first ancestor of x with a right child.
    else
    {
        if (x == root)
            return x;

        else
        {
            for (;  x->parent->right==nullptr; x = x->parent)
                ;

            return x->parent;
        }
    }
}




void tree::transplant(node *u, node *v) {

    if (u == root)  // u is root of tree
        root = v;
    else //u isn't root 
    {     
        if (v && v->parent) 
            v->parent = u->parent;

        if (u->parent->left == u) 
            u->parent->left = v;
        else 
            u->parent->right = v;
    }
}





bool tree::is_ancestor(node *u, node *v)
{

    for (; v; v = v->parent)
        if (v == u ) return true;

    return false;

}

node *tree::low_com_ancestor(node *u, node *v) {
    if(!u || !v)
        return nullptr;

    while( (u->data < root->data && v->data < root->data)  || (u->data > root->data && v->data > root->data)) {
        if ((u->data < root->data && v->data < root->data) )
            root=root->left;
        else
            root=root->right; 
    }
    return root;
}
