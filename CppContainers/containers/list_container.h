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
	explicit list_container() : head{ nullptr }, tail{ nullptr }, current_size{ 0 } {}
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
	list_node<T>* head;
	list_node<T>* tail;
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
T& list_container<T>::operator[](int index) {
	auto ptr = head;
	for (int i = 0; i < index; ++i) {
		ptr = ptr->next;
	}

	return ptr->item;
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

template <typename T>
size_type list_container<T>::size() {
	return current_size;
}

template <typename T>
T& list_container<T>::at(int index) {
	if (index >= current_size) {
		throw std::out_of_range{ "The entered index is invalid" };
	}

	auto ptr = head;

	for (int i = 0; i < index; ++i) {
		ptr = ptr->next;
	}

	return ptr->item;
}

template <typename T>
void list_container<T>::push_front(T item) {
	auto node = new list_node<T>(item);
	if (head) {
		node->next = head;
		head->prev = node;
	}

	head = node;
	current_size++;

	if (!tail) {
		// Adding to empty list
		tail = head;
	}
}

template <typename T>
void list_container<T>::push_back(T item) {
	auto node = new list_node<T>(item);
	if (tail) {
		node->prev = tail;
		tail->next = node;
	}

	tail = node;
	current_size++;

	if (!head) {
		// Adding to empty list
		head = tail;
	}
}

template <typename T>
T list_container<T>::pop_front() {
	auto new_head = head->next;
	if (new_head) {
		new_head->prev = nullptr;
	}
	head->next = nullptr;

	auto item = std::move(head->item);

	delete head;
	head = new_head;
	current_size--;

	if (current_size == 0) {
		tail = nullptr;
	}

	return item;
}

template <typename T>
T list_container<T>::pop_back() {
	auto new_tail = tail->prev;
	tail->prev = nullptr;
	if (new_tail) {
		new_tail->next = nullptr;
	}

	auto item = std::move(tail->item);

	delete tail;
	tail = new_tail;
	current_size--;

	if (current_size == 0) {
		head = nullptr;
	}

	return item;
}
