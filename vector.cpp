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