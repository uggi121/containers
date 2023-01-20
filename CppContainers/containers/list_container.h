#pragma once
#include "container.h"

template <typename T> 
class list_node {
public:
	explicit list_node(T item) : item{ item }, next{ nullptr }, prev{ nullptr } {}
	explicit list_node(const list_node<T>& lst);
	explicit list_node(list_node<T>&& lst);

	T item;
	list_node* next;
	list_node* prev;
	~list_node();
};

template <typename T>
list_node<T>::~list_node() {
	next = nullptr;
	prev = nullptr;
}

template <typename T>
list_node<T>::list_node(const list_node<T>& lst) {
	item = lst.item;
	next = lst.next;
	prev = lst.prev;
}

template <typename T>
list_node<T>::list_node(list_node<T>&& lst) {
	item = lst.item;
	next = lst.next;
	prev = lst.prev;

	lst.next = nullptr;
	lst.prev = nullptr;
}

template <typename T>
class list_container : public sequence_container<T> {
public:
	// Constructors
	explicit list_container() : head{ nullptr }, tail{ nullptr } {}
	explicit list_container(const list_container<T>& lst);
	explicit list_container(list_container<T>&& lst);

	// Capacity methods
	size_type size();

	// Access methods
	T& at(int index);

	// Modifier methods
	void push_front(T item);
	void push_back(T item);
	T pop_front();
	T pop_back();

	// Operator overloads
	T& operator[](int index);

	~list_container();

private:
	list_node* head;
	list_node* tail;
	size_type current_size;
};

template <typename T>
list_container<T>::list_container(const list_container<T>& lst) {
	head = lst.head;
	tail = lst.tail;
	current_size = lst.current_size
}

template <typename T>
list_container<T>::list_container(list_container<T>&& lst) {
	head = lst.head;
	tail = lst.tail;
	current_size = lst.current_size;

	lst.head = nullptr;
	lst.tail = nullptr;
	lst.current_size = 0;
}

template <typename T>
list_container<T>::~list_container() {
	// Traverse the linked list from the head and delete nodes sequentially
	while (head && head != tail) {
		auto next_node = head->next;
		next_node->prev = nullptr;

		delete head;
		head = next_node;
	}

	if (head) {
		delete head;
	}
}
