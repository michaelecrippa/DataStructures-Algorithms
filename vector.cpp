/*#include "vector.h"

template <typename T>
bool vector<T>::isEmpty() const {
	return this == nullptr || this->size == 0;
}
template <typename T>
void vector<T>::erase() {
	if (this->isEmpty()) return;
	delete[] container;
	container = nullptr;
	size = 0;
	capacity = 0;
}
template <typename T>
void vector<T>::copyFrom(const vector<T>& other) {
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
template <typename T>
void vector<T>::resize() {
	if (isEmpty())
		throw std::length_error("exc");
	this->capacity *= 2;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T>
void vector<T>::resizeDown() {
	//minimum size reached
	if (this->capacity == 8)
		throw std::length_error("exc");
	this->capacity /= 2;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T>
vector<T>::vector() {
	this->size = 0;
	this->capacity = 8;
	this->container = new T[this->capacity];
}
template <typename T>
vector<T>::vector(const vector<T>& other) {
	copyFrom(other);
}
template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
	if (this != &other)
	{
		erase();
		copyFrom(other);
	}
	return *this;

}
template <typename T>
vector<T>::~vector() {
	if (!this->isEmpty()) erase();
}
template <typename T>
size_t vector<T>::getSize() const {
	return size;
}
template <typename T>
void vector<T>::print() const {
	if (this->isEmpty())
		throw "Empty vector!";
	for (size_t i = 0; i < size; i++)
		std::cout << container[i] << ' ';
}
template  <typename T>
T vector<T>::getAt(size_t index) {
	if (index < size)
		return container[index];
	throw std::out_of_range("exception");
}
template <typename T>
void vector<T>::addAt(const T& element, size_t index) {
	if (index >= size)
		throw std::out_of_range("exception");
	if (size == capacity)
		resize();
	container[index] = element;
	size++;
}
template <typename T>
void vector<T>::push(const T& element) {
	this->addAt(element, 0);
}
template <typename T>
void vector<T>::pushBack(const T& element) {
	this->addAt(element, (this->size) - 1);
}
template <typename T>
T vector<T>::removeAt(size_t index) {
	if (index < 0 || index >= size)
		throw std::out_of_range("exception");
	size--;
	if (size < capacity / 2)
		this->resizeDown();
	return container[index];
}
template <typename T>
T vector<T>::pop() {
	return this->removeAt(0);
}
template <typename T>
T vector<T>::popBack() {
	return this->removeAt(this->size);
}
template <typename T>
T& vector<T>::operator[](size_t index) {
	if (index < 0 || index >= size)
		throw std::out_of_range("exception");
	return container[index];
}
template <typename T>
const T& vector<T>::operator[](size_t index) const {
	if (index < 0 || index >= size)
		throw std::out_of_range("exception");
	return container[index];;
}
template <typename T>
T vector<T>::peak() const {
	if (isEmpty())
		throw std::length_error("exc");
	return container[0];
}
*/