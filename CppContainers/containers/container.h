#pragma once

using size_type = int;

template <typename T>
class sequence_container {
public:
	// Capacity methods
	virtual size_type size() = 0;

	// Access methods
	virtual T& at(int index) = 0;

	// Modifier methods
	virtual void push_front(T data) = 0;
	virtual void push_back(T data) = 0;
	virtual T pop_front() = 0;
	virtual T pop_back() = 0;

	// Operator overloads
	virtual T& operator[](int index) = 0;
	
	virtual ~sequence_container() = 0;
};
