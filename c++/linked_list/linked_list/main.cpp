#include "s_linked_list.hpp"

int main() {
    linked_list<double> my_list;
    my_list.push(25.1);
    my_list.addafter(25.1, 17.3);
    my_list.addbefore(17.3, 5.7);
    my_list.pop();
    my_list.push(14.5);
    my_list.del(17.3);

    my_list.print_list();
    cout << "\nThe linked list size is: " << my_list.size << '\n' << endl;

    linked_list<string> string_list;
    string_list.push("hello");
    string_list.addafter("hello", "bye");
    string_list.addbefore("bye", "zorro");

    string_list.print_list();
    cout << "\nThe linked list size is: " << string_list.size << '\n' << endl;

    return 0;
}

