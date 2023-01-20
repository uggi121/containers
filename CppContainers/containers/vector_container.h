#pragma once
#include "container.h"
#include <iostream>
#include <initializer_list>

template <typename T>
class vector_container : public sequence_container<T> {
public:
	// Invariant - 0 <= current_size <= max_size

	// Constructors
	explicit vector_container(int max_size = 1);
	explicit vector_container(std::initializer_list<int> size);
	explicit vector_container(const vector_container<T>& vec);
	explicit vector_container(vector_container<T>&& vec);

	// Capacity methods
	size_type size();

	// Access methods
	T& at(int index);

	// Modifier methods
	void push_front(T item);
	void push_back(T item);
	T pop_back();
	T pop_front();

	// Operator overloads
	T& operator[](int index);
	vector_container<T>& operator=(const vector_container<T>& vec) noexcept;
	vector_container<T>& operator=(vector_container<T>&& vec) noexcept;

	~vector_container();

private:
	size_type current_size;
	size_type max_size;
	T* data;

	void _resize(int new_max_size);
};

template <typename T>
sequence_container<T>::~sequence_container() { std::cout << "Destroying sequence" << std::endl; }

template <typename T>
vector_container<T>::vector_container(int max_size) : current_size{ 0 }, max_size{ max_size }, data{ new T[max_size] } {}

template <typename T>
vector_container<T>::vector_container(std::initializer_list<int> size) : current_size{ 0 }, max_size{ *size.begin() }, data{ new T[max_size] } {}

template <typename T>
vector_container<T>::vector_container(const vector_container<T>& vec) {
	std::cout << "Invoking copy ctor" << std::endl;
	current_size = vec.current_size;
	max_size = vec.max_size;
	data = new T[max_size];
	
	for (int i = 0; i < current_size; ++i) {
		data[i] = vec.data[i];
	}
}

template <typename T>
vector_container<T>::vector_container(vector_container<T>&& vec) {
	std::cout << "Invoking move ctor" << std::endl;
	current_size = vec.current_size;
	max_size = vec.max_size;
	data = vec.data;

	vec.current_size = 0;
	vec.max_size = 0;
	vec.data = nullptr;
}

template <typename T>
T& vector_container<T>::operator[](int index) {
	return data[index];
}

template <typename T>
vector_container<T>& vector_container<T>::operator=(const vector_container<T>& vec) noexcept {
	std::cout << "Invoking copy assignment op" << std::endl;
	current_size = vec.current_size;
	max_size = vec.max_size;
	data = new T[max_size];

	for (int i = 0; i < current_size; ++i) {
		data[i] = vec.data[i];
	}

	return *this;
}

template <typename T>
vector_container<T>& vector_container<T>::operator=(vector_container<T>&& vec) noexcept {
	std::cout << "Invoking move assignment op" << std::endl;
	current_size = vec.current_size;
	max_size = vec.max_size;
	auto tmp_data = vec.data;

	vec.current_size = 0;
	vec.max_size = 0;
	vec.data = nullptr;

	delete[] data;
	data = tmp_data;

	return *this;
}

template <typename T>
vector_container<T>::~vector_container() {
	std::cout << "Destroying vector "<< std::endl;
	delete[] data;
}

template <typename T>
void vector_container<T>::_resize(int new_max_size) {
	// Copy elements from current memory to newly allocated memory; free old memory
	// Assertion: current_size <= new_max_size 

	std::cout << "[Vector] - " << "Resizing to: " << new_max_size << std::endl;

	T* new_data = new T[new_max_size];
	for (int i = 0; i < current_size; ++i) {
		new_data[i] = data[i];
	}

	max_size = new_max_size;
	delete[] data;
	data = new_data;
}

template <typename T>
size_type vector_container<T>::size() {
	return current_size;
}

template <typename T>
T& vector_container<T>::at(int index) {
	if (index >= current_size) {
		throw std::out_of_range{ "Entered index is out of range" };
	}

	return data[index];
}

template <typename T>
void vector_container<T>::push_front(T item) {
	if (current_size == max_size) {
		_resize(max_size * 2);
	}

	for (int i = current_size; i >= 0; --i) {
		data[i] = data[i - 1];
	}

	data[0] = item;
	current_size++;
}

template <typename T>
void vector_container<T>::push_back(T item) {
	if (current_size == max_size) {
		_resize(max_size * 2);
	}

	data[current_size++] = item;
}

template <typename T>
T vector_container<T>::pop_front() {
	auto item = data[0];

	for (int i = 0; i < current_size - 1; ++i) {
		data[i] = data[i + 1];
	}

	current_size--;

	if (current_size <= max_size / 3) {
		_resize(max_size / 2);
	}

	return item;
}

template <typename T>
T vector_container<T>::pop_back() {
	auto item = data[--current_size];

	if (current_size <= max_size / 3) {
		_resize(max_size / 2);
	}

	return item;
}
