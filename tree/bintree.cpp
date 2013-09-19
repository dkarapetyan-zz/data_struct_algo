#include "bintree.hpp"
int main()
{
    tree my_tree(19);
    my_tree.insert_node(19);
    my_tree.insert_node(20);
    my_tree.insert_node(31);
    my_tree.insert_node(25);
    my_tree.delete_node(20);
    my_tree.print_inorder();

    return 0;
}


