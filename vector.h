#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "base_structure_interface.h"

template <typename T> class Vector : public structures_interface<T> {
private:
	size_t size;
	size_t capacity;
	T* container;

	void erase();
	void copyFrom(const Vector<T>& other);

	void resize();
	void shrink_to_fit();

	bool isEmpty() const;
	bool outOfRange(size_t index) const;

	T getAt(size_t index);
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void addAt(const T& element, size_t index);
	T removeAt(size_t index);

	void push(const T& element);
	T pop();

	void pushBack(const T& element);
	T popBack();

	T peak() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	size_t getSize() const;
	void print() const;
};

template <typename T> bool Vector<T>::isEmpty() const {
	return this == nullptr;
}
template <typename T> bool Vector<T>::outOfRange(size_t index) const{
	return index >= capacity;
}

template <typename T> void Vector<T>::erase() {
	if (this->isEmpty()) return;
	delete[] container;
	container = nullptr;
	size = 0;
	capacity = 0;
}
template <typename T> void Vector<T>::copyFrom(const Vector<T>& other) {
	if (other.isEmpty()) {
		erase();
		return;
	}
	this->size = other.size;
	this->capacity = other.capacity;
	delete[] this->container;
	container = new T[capacity];
	for (size_t i = 0; i < size; i++)
		container[i] = other.container[i];
}
template <typename T> void Vector<T>::resize() {
	this->capacity << 1; // shift left 1 postion to get new capacity
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T> void Vector<T>::shrink_to_fit() {
	this->capacity >> 1 // shift right 1 postiotion to get new capacity;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}

template <typename T> Vector<T>::Vector() {
	this->size = 0;
	this->capacity = 4;
	this->container = new T[this->capacity];
}
template <typename T> Vector<T>::Vector(size_t capacity) {
	this->size = 0;
	this->capacity = capacity;
	this->container = new T[this->capacity];
}// create dynamic array with capacity closest bigger power of two to requested capacity
template <typename T> Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}
template <typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other)
	{
		erase();
		copyFrom(other);
	}
	return *this;
}
template <typename T> Vector<T>::~Vector() {
	if (!this->isEmpty()) erase();
}

template <typename T> size_t Vector<T>::getSize() const {
	return size;
}
template <typename T> void Vector<T>::print() const {
	if (this->isEmpty())
		throw "Empty Vector!";
	for (size_t i = 0; i < size; i++)
		std::cout << container[i] << ' ';
}
template  <typename T> T Vector<T>::getAt(size_t index) {
	if (!outOfRange(index))
		return container[index];
	throw std::out_of_range("");
}
template <typename T> void Vector<T>::addAt(const T& element, size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("exception");
	if (size == capacity)
		resize();
	container[index] = element;
	size++;
}
template <typename T> T Vector<T>::removeAt(size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("exception");
	size--;
	if (size < capacity / 2 && capacity > 8)
		this->shrink_to_fit();
	return container[index];
}
template <typename T> T& Vector<T>::operator[](size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("");
	T* ptr = container[index];
	return ptr;
}
template <typename T> const T& Vector<T>::operator[](size_t index) const {
	if (outOfRange(index))
		throw std::out_of_range("");
	return container[index];
}

template <typename T> void Vector<T>::push(const T& element) {
	if (size == capacity)
		resize();
	for (size_t i = size - 1; i > 0; i--)
		container[i] = container[i - 1]; //pusha all elements one position right
	container[0] = element;
	size++;
}
template <typename T> void Vector<T>::pushBack(const T& element) {
	this->addAt(element, this->size);
}
template <typename T> T Vector<T>::pop() {
	if (isEmpty()) throw std::out_of_range("");
	T el = container[0];
	for (size_t i = size - 1; i > 0; i++)
		container[i - 1] = container[i]; //push all elements one position left
	size--;
	return el;
}
template <typename T> T Vector<T>::popBack() {
	return this->removeAt(this->size - 1);
}
template <typename T> T Vector<T>::peak() const {
	if (isEmpty())
		throw std::length_error("exc");
	return container[0];
}

#endif 