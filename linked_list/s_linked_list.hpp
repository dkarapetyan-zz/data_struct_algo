// singly linked list header

#ifndef S_LINKED_LIST_HPP
#define S_LINKED_LIST_HPP 

#include <iostream>
#include <type_traits>
using std::cout;
using std::endl;
using std::string;
template <class T>
class node
{
    private:

        node *next;
        T key;

    public:
        // constructors
        node();
        node(T key, node *next);


        //destructor
        ~node();

        // accessor methods
        node * get_next(); 
        T get_key();

        // mutator methods
        void set_next(node *next);
        void set_key(T key);
};


template <class T>
class linked_list
{
    private:
        node<T> * head;

    public:

        // count of nodes
        static int size;

        // constructor 
        linked_list();

        //destructor
        ~linked_list();

        //copy constructor
        //
        linked_list(const linked_list &other);


        //accessors and mutators
        node<T> *get_head();
        node<T> *set_head();
        

        //functions
        void push(T key);
        node<T> *pop();
        node<T> *search(T key);
        void addafter(T key, T afterkey);
        void addbefore(T key, T beforekey); 
        void del(T key);
        void print_list();
};





// singly linked list implementation

template <class T>
int linked_list<T>::size = 0;

    template <class T>
node<T>::node()
{
    this->next = nullptr;
    linked_list<T>::size++;
}

    template <class T>
node<T>::node(T key, node *next)
{
    this->key = key;
    this->next = next;
    ++linked_list<T>::size;

}
    template <class T>
node<T>::~node()
{
    --linked_list<T>::size;
}




    template <class T>
node<T> * node<T>::get_next()
{
    return next;
}

    template <class T>
void node<T>::set_next(node<T> *next)
{
    this->next = next;
}

    template <class T>
T node<T>::get_key() 
{
    return key;
}

    template <class T>
void node<T>::set_key(T key)
{
    this->key = key;
}






    template <class T>
linked_list<T>::linked_list()
{
    this->head = nullptr;
    this->size = 0;
}

    template <class T>
linked_list<T>::~linked_list()
{
    for (node<T> *p = this->head, *temp; p !=nullptr; )
    {
        temp = p;
        p = p->get_next();
        delete temp;
    }
}

//template <class T>
//linked_list<T>::linked_list(const linked_list &other)
//{
//for (node<T> *p = other->get_head(); p !=nullptr; p = p->get_next())
//{
//}
//}

    template <class T>
void linked_list<T>::push(T key)
{

    if (this->head==nullptr) {
        this->head = new node<T>(key, nullptr);

    }
    else {
        node<T> *p = new node<T>(key, this->head); // create new node with next pointer pointing to current head
        this->head = p; // update head
    }


}


    template <class T>
node<T> * linked_list<T>::pop()
{
    node<T> *p = this->head;
    if (p != nullptr) {
        this->head = this->head->get_next(); // update head
    }
    return p;
}


    template <class T>
node<T> * linked_list<T>::search(T key)
{
    node<T> *p = this->head;

    if (p == nullptr)
    {
        return nullptr;
    }
    for (; p !=nullptr; p = p->get_next())
    {
        if (p->get_key() == key)
        {
            return p;
        }
    }


    return p;
}

    template <class T>
void linked_list<T>::addafter(T key, T afterkey)
{
    node<T> *s = search(key);

    if (s != nullptr)
    {

        node<T> *p = new node<T>;

        p->set_next(s->get_next());
        s->set_next(p);
        p->set_key(afterkey);
    }

}

    template <class T>
void linked_list<T>::addbefore(T key, T beforekey) //non trivially different from dlinked case
{
    node<T> *s = search(key);

    if (s == nullptr) {
        return; 
    }

    node<T> *hb = head;

    while(hb->get_next() != s ) {
        hb = hb->get_next();  
    }

    node<T> *p = new node<T>;

    p->set_next(s);
    hb->set_next(p);
    p->set_key(beforekey);


}






    template <class T>
void linked_list<T>::del(T key) //again, bit different from dlinked case
{
    node<T> *p = search(key);



    if (p != nullptr) //handle only case where we find key
    {


        if (p == this->head) // handle head of list
        { 
            this->head=p->get_next();
            delete(p);
        }


        else // handle inside of list
        {
            //find element immediately before p
            node<T> *hb;
            for(hb = this->head; hb->get_next() != p; hb = hb->get_next()) {;}

            hb->set_next( p->get_next() );  
            delete(p);
        }
    }
}



    template <class T>
void linked_list<T>::print_list()
{
    if (this->head == nullptr)
    {
        cout << "Printing done homie" << endl;
    }
    else
    {
        for (node<T> *p = this->head;  p != nullptr; p = p->get_next())
        {
            cout << p->get_key() << " ";
        }
    }
}





#endif
