#include <cstdlib>
#include "Tutorial.h"
#pragma once

template <typename TElem>
class DynamicArray {
private:
	TElem* elements;
	int length;
	int capacity;
	int initialCapacity;

	void resize() {
		TElem* newElements;
		this->capacity = this->capacity * 2;
		newElements = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++) {
			newElements[i] = this->elements[i];
		}
		delete[] this->elements;
		this->elements = newElements;
	}

	void clear() {
		this->length = 0;
		TElem* newElements;
		this->capacity = this->initialCapacity;
		newElements = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++) {
			newElements[i] = this->elements[i];
		}
		delete[] this->elements;
		this->elements = newElements;
	}
public:
    DynamicArray(int capacity=20);
	DynamicArray(const DynamicArray& arrayToCopy);
	~DynamicArray();
	void addToArray(const TElem& element);
	void deleteElem(int position);
	void update(const TElem& element, int position);
	int getSize();
	TElem& operator [] (int position);
	
};

template<typename TElem>
inline DynamicArray<TElem>::DynamicArray(int capacity)
{
	this->capacity = capacity;
	this->initialCapacity = capacity;
	this->length = 0;
	this->elements = new TElem[capacity];
}

template<typename TElem>
inline DynamicArray<TElem>::DynamicArray(const DynamicArray& arrayToCopy)
{
	this->capacity = arrayToCopy.capacity;
	this->initialCapacity = arrayToCopy.capacity;
	this->length = arrayToCopy.length;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->length; i++) {
		this->elements[i] = arrayToCopy.elements[i];
	}
}

template<typename TElem>
inline DynamicArray<TElem>::~DynamicArray()
{
	delete[] this->elements;
}

template<typename TElem>
inline void DynamicArray<TElem>::addToArray(const TElem& element)
{
	if (this->length == this->capacity) {
		resize();
	}
	this->elements[this->length++] = element;
}

template<typename TElem>
inline void DynamicArray<TElem>::deleteElem(int position)
{
	if (this->length == 1)
		clear();
	else {
		for (int i = position; i < this->length - 1; i++) {
			this->elements[i] = this->elements[i + 1];
		}
		this->length--;
	}
}

template<typename TElem>
inline void DynamicArray<TElem>::update(const TElem& element, int position)
{
	this->elements[position] = element;
}

template<typename TElem>
inline int DynamicArray<TElem>::getSize()
{
	return this->length;
}

template<typename TElem>
inline TElem& DynamicArray<TElem>::operator[](int position)
{
	return this->elements[position];
}
