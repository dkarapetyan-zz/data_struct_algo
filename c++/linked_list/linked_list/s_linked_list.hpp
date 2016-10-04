// singly linked list header

#include <iostream>

using std::cout;
using std::endl;
using std::string;

template<typename T>
class linked_list;

template<typename T>
class node;

template<typename T>
class node {
	friend class linked_list<T> ;

private:
	node *next;
	T key;

public:
	// constructors
	node();

	node(T __key, node *next);

	//destructor
	~node();

	// accessor methods
	node *get_next();

	T get_key();

	// mutator methods
	void set_next(node *next);

	void set_key(T __key);
};

template<typename T>
class linked_list {

private:
	node<T> *head;

public:

	// count of nodes
	static int size;

	// constructor
	linked_list();

	//destructor
	~linked_list();

	//functions
	void push(T __key);

	node<T> *pop();

	node<T> *search(T __key);

	void addafter(T __key, T afterkey);

	void addbefore(T __key, T beforekey);

	void del(T __key);

	void print_list();
};

// singly linked list implementation

template<typename T>
int linked_list<T>::size = 0;

template<typename T>
node<T>::node() {
	next = nullptr;
	++linked_list<T>::size;
}

template<typename T>
node<T>::node(T __key, node *__next) {
	key = __key;
	next = __next;
	++linked_list<T>::size;

}

template<typename T>
node<T>::~node() {
	--linked_list<T>::size;
}

template<typename T>
node<T> *node<T>::get_next() {
	return next;
}

template<typename T>
void node<T>::set_next(node<T> *__next) {
	next = __next;
}

template<typename T>
T node<T>::get_key() {
	return key;
}

template<typename T>
void node<T>::set_key(T __key) {
	key = __key;
}

template<typename T>
linked_list<T>::linked_list() {
	head = nullptr;
	size = 0;
}

template<typename T>
linked_list<T>::~linked_list() {
	for (node<T> *p = head, *temp; p != nullptr;) {
		temp = p;
		p = p->get_next();
		delete temp;
	}
}

template<typename T>
void linked_list<T>::push(T __key) {

	if (head == nullptr) {
		head = new node<T>(__key, nullptr);
	} else {
		node<T> *p = new node<T>(__key, head); // create new node with next pointer pointing to current head
		head = p; // update head
	}

}

template<typename T>
node<T> *linked_list<T>::pop() {
	node<T> *p = head;
	if (p != nullptr) {
		head = head->get_next(); // update head
		--linked_list<T>::size;
	}
	return p;
}

template<typename T>
node<T> *linked_list<T>::search(T key) {
	node<T> *p = head;

	if (p == nullptr) {
		return nullptr;
	}
	for (; p != nullptr; p = p->get_next()) {
		if (p->get_key() == key) {
			return p;
		}
	}

	return p;
}

template<typename T>
void linked_list<T>::addafter(T key, T afterkey) {
	node<T> *s = search(key);

	if (s != nullptr) {
		node<T> *p = new node<T>;

		p->set_next(s->get_next());
		s->set_next(p);
		p->set_key(afterkey);
	}

}

template<typename T>
void linked_list<T>::addbefore(T __key, T beforekey) //non trivially different from dlinked case
{
	node<T> *s = search(__key);

	if (s == nullptr) {
		return;
	}
	node<T> *hb = head;

	while (hb->get_next() != s) {
		hb = hb->get_next();
	}

	node<T> *p = new node<T>;
	p->set_next(s);
	hb->set_next(p);
	p->set_key(beforekey);
}

template<typename T>
void linked_list<T>::del(T key) //again, bit different from dlinked case
{
	node<T> *p = search(key);

	if (p != nullptr) //handle only case where we find key
	{

		if (p == head) // handle head of list
		{
			head = p->get_next();
			delete (p);
		}

		else // handle inside of list
		{
			//find element immediately before p
			node<T> *hb;
			for (hb = head; hb->get_next() != p; hb = hb->get_next()) {
				;
			}

			hb->set_next(p->get_next());
			delete (p);
		}
	}
}

template<typename T>
void linked_list<T>::print_list() {
	if (head != nullptr) {
		for (node<T> *p = head; p != nullptr; p = p->get_next()) {
			cout << p->get_key() << " ";
		}
	}
}

