#pragma once
#include <iostream>

// MyVector class definition 
class MyVector {
private:

	int* m_arr;
	std::size_t m_size;
	std::size_t m_capacity;

public:
	
	using iterator = int*;

	// c-tors
	explicit MyVector(size_t size = 0, int value = 0);
	MyVector(const MyVector&);
	MyVector(MyVector&&)noexcept;
	
	// methods
	int* data() noexcept;
	bool empty();
	void push_back(const int&);
	void resize(std::size_t);
	void resize(std::size_t, const int&);
	void clear();
	void swap(MyVector&) noexcept;
	void pop_back();

	// getters
	std::size_t getSize() const;
	std::size_t getCapacity() const;

	// iterators
	iterator begin();
	iterator end();
	iterator insert(iterator, const int&);
	iterator erase(iterator);

	// opers
	int& operator[](std::size_t index);
	const int& operator[](std::size_t index) const;
	MyVector& operator=(const MyVector&);
	MyVector& operator=(MyVector&&)noexcept;
};

// global opers
bool operator==(const MyVector&, const MyVector&);
std::ostream& operator<<(std::ostream&, const MyVector&);