//------------------------------------------------------------------------------
#pragma once
#include "MyVector.h"

//------------------------------------------------------------------------------
/*
* constructor that creates a new vector with the specified 
* size and fills it with the specified value.
*/
MyVector::MyVector(size_t size, int value) : 
	m_size(size), m_capacity(size) {
	m_arr = new int[m_capacity];
	std::fill_n(m_arr, m_size, value);
}

//------------------------------------------------------------------------------
/*
* copy constructor that creates a new vector that is
* a copy of the specified vector.
*/
MyVector::MyVector(const MyVector& other) : 
	m_size(other.m_size), m_capacity(other.m_size) {

	m_arr = new int[other.m_size];
	std::copy(other.m_arr, other.m_arr + m_size, m_arr);
}

//------------------------------------------------------------------------------
/*
* move constructor that creates a new vector by "stealing" 
* the resources of the specified vector.
*/
MyVector::MyVector(MyVector&& other) noexcept : 
	m_arr(other.m_arr), m_size(other.m_size), m_capacity(other.m_size) {

	other.m_arr = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

//------------------------------------------------------------------------------
/*
* returns a pointer to the first element in the vector.
*/
int* MyVector::data() noexcept {
	return m_arr;
}

//------------------------------------------------------------------------------
/*
* returns true if the vector is empty (i.e., has size zero), 
* and false otherwise.
*/
bool MyVector::empty() {
	return (m_size == 0);
}

//------------------------------------------------------------------------------
/*
* adds a new element to the end of the vector
* and resizes the vector if necessary.
*/
void MyVector::push_back(const int& value) {
	if (m_size >= m_capacity) {
		resize(m_capacity * 2, value);
	}

	m_arr[m_size++] = value;
}

//------------------------------------------------------------------------------
/*
* changes the size of the vector to the specified count,
* filling any new elements with zero.
*/
void MyVector::resize(std::size_t count) {
	resize(count, 0);
}

//------------------------------------------------------------------------------
/*
* changes the size of the vector to the specified count,
* filling any new elements with the specified value.
*/
void MyVector::resize(std::size_t count, const int& value) {
	if (count <= m_capacity) {
		// No need to allocate more memory
		if (count > m_size) {
			// Fill the new elements with the specified value
			std::fill(m_arr + m_size, m_arr + count, value);
		}
		m_size = count;
	}
	else {
		// Allocate more memory
		m_capacity = std::max(count, 2 * m_capacity);
		int* new_arr = new int[m_capacity];
		// Copy the elements to the new array
		std::copy(m_arr, m_arr + m_size, new_arr);
		// Fill the new elements with the specified value
		std::fill(new_arr + m_size, new_arr + count, value);
		// Update the member variables
		m_arr = new_arr;
		m_size = count;
	}
}

//------------------------------------------------------------------------------
/*
* empties the vector, setting its size to zero 
* and freeing any allocated memory.
*/
void MyVector::clear() {
	m_arr = 0;
	m_size = 0;
}

//------------------------------------------------------------------------------
/*
* swaps the contents of this vector with the specified vector.
*/
void MyVector::swap(MyVector& other) noexcept {
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_arr, other.m_arr);
}

//------------------------------------------------------------------------------
/*
* removes the last element from the vector.
*/
void MyVector::pop_back() {
	if (m_size > 0) {
		m_size--;
	}
}

//------------------------------------------------------------------------------
/*
* returns the current size of the vector.
*/
std::size_t MyVector::getSize() const {
	return m_size;
}

//------------------------------------------------------------------------------
/*
* returns the current capacity of the vector.
*/
std::size_t MyVector::getCapacity() const {
	return std::size_t();
}

//------------------------------------------------------------------------------
/*
* returns an iterator to the first element in the vector.
*/
int* MyVector::begin() {
	return m_arr;
}

//------------------------------------------------------------------------------
/*
* returns an iterator to one past the last element in the vector.
*/
int* MyVector::end() {
	return m_arr + getSize();
}

//------------------------------------------------------------------------------
/*
* inserts a new element with the specified value at the specified position in the vector.
*/
int* MyVector::insert(iterator pos, const int& val) {
	
	std::size_t index = pos - begin();
	std::size_t newSize = m_size + 1;

	if (newSize > m_capacity) {
		m_capacity = std::max(newSize, 2 * m_capacity);
		int* newArray = new int[m_capacity];
		std::copy(m_arr, m_arr + index, newArray);
		newArray[index] = val;
		std::copy(m_arr + index, m_arr + m_size, newArray + index + 1);
		delete[] m_arr;
		m_arr = newArray;
	}
	else {
		std::copy_backward(m_arr + index, m_arr + m_size, m_arr + m_size + 1);
		m_arr[index] = val;
	}

	++m_size;
	return pos;
}

//------------------------------------------------------------------------------
/*
* removes the element at the specified position in the vector.
*/
int* MyVector::erase(iterator pos) {
	auto index = pos - begin();
	std::copy(pos + 1, end(), pos);
	--m_size;
	return begin() + index;
}

//------------------------------------------------------------------------------
/*
* returns a reference to the element at the specified index in the vector.
*/
int& MyVector::operator[](std::size_t index) {
	return m_arr[index];
}

//------------------------------------------------------------------------------
/*
* returns a const reference to the element at the specified index in the vector.
*/
const int& MyVector::operator[](std::size_t index) const {
	return m_arr[index];
}

//------------------------------------------------------------------------------
/*
* copy assignment operator that assigns a copy of the specified vector to this vector.
*/
MyVector& MyVector::operator=(const MyVector& other) {

	if (this == &other) {
		return *this;
	}

	if (m_capacity < other.m_size) {
		delete[] m_arr;
		m_arr = new int[other.m_size];
		m_capacity = other.m_size;
	}

	m_size = other.m_size;
	for (int i = 0; i < m_size; i++) {
		m_arr[i] = other.m_arr[i];
	}

	return *this;
}

//------------------------------------------------------------------------------
/*
* move assignment operator that "steals" the resources of the specified vector.
*/
MyVector& MyVector::operator=(MyVector&& other)noexcept {

	if (this == &other) {
		return *this;
	}
	delete[] m_arr;
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_arr = other.m_arr;
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_arr = nullptr;
	return *this;
}

//------------------------------------------------------------------------------
/*
* returns true if vec1 and vec2 have the same size and elements,
* and false otherwise.
*/
bool operator==(const MyVector& vec1, const MyVector& vec2) {
    if (vec1.getSize() != vec2.getSize()) {
        return false;
    }
    for (std::size_t i = 0; i < vec1.getSize(); i++) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/*
* writes the contents of the specified vector to the specified output stream.
*/
std::ostream& operator<<(std::ostream& output, const MyVector& vec) {
	for (int i = 0; i < vec.getSize(); i++)
		output << vec[i] << " ";
	return output;
}