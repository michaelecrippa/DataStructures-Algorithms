#include "vector.h"
template <typename T>
bool vector<T>::empty() const{
	return this == nullptr;
}
template <typename T>
void vector<T>::erase() {
	if (this->empty())
		return;
	delete[] container;
	container = nullptr;
	size = 0;
	capacity = 0;
}
template <typename T>
void vector<T>::copyFrom(const vector& other) {
	if (other.empty()){
		erase();
		return;
	}
	this->size = other.size;
	this->capacity = other.capacity;
	delete[] container;
	container = new T[capacity];
	for (size_t i = 0; i < size; i++){
		container[i] = other.container[i];
	}
}
template <typename T>
void vector<T>::resize() {
	//if empty -> create base vector
	if (empty())
		vector();
	this->capacity *= 2;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T>
void vector<T>::resizeDown() {
	//if empty -> create base vector
	if (this->container == 8) 
		throw "Resize unavalible! Minimum size reached!"	
	this->capacity /= 2;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T>
vector<T>::vector() {
	size = 0;
	capacity = 8;
	T* container = new T[capacity];
}
template <typename T>
vector<T>::vector(const vector& other) {
	copyFrom(other);
}
template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
	if (this != &other)
	{
		erase();
		copyFrom(other);
	}
	return *this;
		
}
template <typename T>
vector<T>::~vector() {
	if (!empty())
		erase;
}
template <typename T>
size_t vector<T>::getSize() const{
	return size;
}
template <typename T>
void vector<T>::print() const {
	if (empty())
		throw "Empty vector!";
	for (size_t i = 0; i < size; i++)
		std::cout << container[i] << ' ';
}
template  <typename T>
T* vector<T>::peak() const {
	return this->getAt(this->size);
}
template  <typename T>
T* vector<T>::getAt(size_t index) {
	if (index <= size)
		return container[index];
	throw "Invalid index!";
}
template <typename T>
void vector<T>::addAt(const T& element, size_t index) {
	if (index >= capacity)
		throw "Invalide index!";
	if (size == capacity)
		resize();
	capacity[index] = element;
	size++;
}
template <typename T>
void vector<T>::push(const T& element) {
	this->addAt(element, 0);
}
template <typename T>
void vector<T>::pushBack(const T& element) {
	this->addAt(element , (this->size) - 1);
}
template <typename T>
T* vector<T>::removeAt(size_t index){
	if (index > this->size)
		throw "Invalide index!";
	container[index] = nullptr;
	size--;
	if (size <= capacity)
		this->resizeDown();
}
template <typename T>
T* vector<T>::pop() {
	this->removeAt(0);
}
template <typename T>
T* vector<T>::popBack() {
	this->removeAt(this->size);
}
