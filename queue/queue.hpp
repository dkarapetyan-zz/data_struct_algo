#include <iostream>
#include <cassert>
#include <cmath>
// queue implementation using singly linked list (non-circular)
// singly linked list

class node {
    friend class queue;

    node *next;
    double data;

    public:
    // constructors and deconstructors
    node();
    node(double);
    node(double, node*);
    ~node();


};
node::node() : next(nullptr), data(NAN){};
node::node(double __data) : next(nullptr), data(__data){};
node::node(double __data, node *__next) : next(__next), data(__data){};

// queue class 
class queue
{
    node *head;
    static size_t qsize;

    public:
    // constructors and deconstructors
    queue();

    // member functions
    size_t size();
    void push(double);
    void pop();
    void after(double,double);
    void before(double,double);
    node *search(double);
    void erase(double);
    void print_list();

};

queue::queue() : head(nullptr) {};
size_t queue::qsize = 0;
size_t queue::size() {return qsize;}

void queue::push(double __data)
{
    if (qsize ==0) {
        head = new node(__data, nullptr);
    }

    else {
        head=new node(__data, head);
        ++qsize;
    }
    qsize++;


}

void queue::pop()
{
    assert(qsize!=0);
    head = head->next;
    qsize--;
}

void queue::after(double __data, double __afterdata)
{
    node *s = search(__data);
    if (s !=nullptr)
    {
        node *p = new node(__afterdata, s->next);
        s->next = p;
        qsize++;
    }
}

void queue::before(double __data, double __beforedata) //non trivially different from dlinked case
{
    node *s = search(__data);
    if(s!=nullptr)
    {
        if (s == head)
        {
            head = new node(__beforedata, head); // new head
        }
        else
        {
            node *hb = head;

            while(hb->next != s && hb->next != nullptr )
            {
                hb = hb->next;  
            }
            node *p = new node(__beforedata, s);
            hb->next = p; 
        }
        qsize++;
    }

}


node *queue::search(double __data)
{
    for (node *p=head; p!=nullptr; p=p->next)
    {
        if (p->data == __data) return p;
    }
    return nullptr;
}

void queue::erase(double __data) //again, bit different from dlinked case
{
    node *p = search(__data);
    if (p!=nullptr)
    { 
        qsize--;
        node *hb = head;
        while( hb->next != p && hb->next != nullptr ) hb = hb->next;
        //find element immediately before p

        if (p == head) head=p->next; //handle head of list 
        else if (p->next == nullptr) hb->next = nullptr;  // handle tail of list 
        else hb->next = p->next;  // handle inside of list 
    }
}


void queue::print_list()
{
    for (auto i = head; i!= nullptr; i = i->next)
    {
        std::cout << i->data << " ";
    }
}
