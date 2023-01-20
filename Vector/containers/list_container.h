#pragma once
#include "container.h"

template <typename T> 
class list_node {
public:
	explicit list_node(T item) : item{ item }, next{ nullptr }, prev{ nullptr } {}
	explicit list_node(const T& item);
	explicit list_node(T&& item);

	T item;
	list_node* next;
	list_node* prev;
	~list_node();
};

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
