#include "baseStructureInterface.h"

template <typename T> struct Node {
	T data;
	Node* next;

	Node<T>();

	T getData() const;
	void setData(const T* data);

	Node<T>* getNext() const;
	void setNext(const Node<T>* next);

	void print() const;
};
template <typename T> Node<T>::Node() {
	next = nullptr;
}
template <typename T> T Node<T>::getData() const {
	if (this == nullptr) throw std::invalid_argument("");
	return data;
}
template <typename T> void Node<T>::setData(const T* data) {
	this->data = *data;
}
template <typename T> Node<T>* Node<T>::getNext() const {
	return next;
}
template <typename T> void Node<T>::setNext(const Node<T>* next) {
	if (this == nullptr) return;
	this->next = (Node<T>*)next;
}
template <typename T> void Node<T>::print() const {
	if (this == nullptr) return;
	std::cout << data << ' ';
}

template <typename T> class SinglyLinkedList : public structuresInterface<T> {
	Node<T>* head;
	Node<T>* tail;
	size_t size;

	void erase();
	void copyFrom(const SinglyLinkedList<T>& other);

	void getAtIndex(size_t index, Node<T>*& ptr); //for operato[] so can return a reference
	bool isEmpty() const;
public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

	void addAt(const T& element, size_t index);
	T removeAt(size_t index);

	void push(const T& element); //pushFront 
	T pop(); //popFront

	void pushBack(const T& element);
	T popBack();

	T getAt(size_t index);
	T peak() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const; //peek at position

	size_t getSize() const;
	void print() const;
	void reverse();
};
template <typename T> void SinglyLinkedList<T>::erase() {
	if (isEmpty()) return;
	Node<T>* toDelete = head;
	while (head != tail) { //more than 1 element
		head = head->getNext();
		delete toDelete;
		toDelete = head;
	}
	delete head; //1 element left to delete
	head = tail = nullptr;
}
template <typename T> void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other) {
	short diff = size - other.size;
	//other is larger
	if (diff < 0)
		for (short i = diff; i < 0; i++)
			this->push((T)0);
	//other is smaller or equal
	else
		for (short i = 0; i < diff; i++)
			this->pop();
	//copy data from the other list
	Node<T>* cursor = head;
	Node<T>* otherCursor = other.head;
	while (cursor != nullptr) {
		cursor->setData(&otherCursor->data);
		cursor = cursor->getNext();
		otherCursor = otherCursor->getNext();
	}
}
template <typename T> SinglyLinkedList<T>::SinglyLinkedList() {
	head = tail = nullptr;
	size = 0;
}
template <typename T> SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
	copyFrom(other);
}
template <typename T> SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
	if (this != &other)
		copyFrom(other);
	return *this;
}
template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
	erase();
}

template <typename T> void SinglyLinkedList<T>::getAtIndex(size_t index, Node<T>*& ptr)
{
	Node<T>* iterator = head;
	for (size_t i = 0; i < index; i++)
		iterator = iterator->getNext();
	ptr = iterator;
}
template <typename T> void SinglyLinkedList<T>::addAt(const T& element, size_t index) {
	if (index > size)
		throw std::out_of_range("");
	else if (index == 0)
		push(element);
	else if (index == size)
		pushBack(element);
	else {
		Node<T>* current = head;
		for (size_t i = 1; i < index; i++)
			current = current->getNext();
		Node<T>* add = new Node<T>;
		add->setData(&element);
		add->setNext(current->getNext());
		current->setNext(add);
		size++;
	}
}
template <typename T> T SinglyLinkedList<T>::removeAt(size_t index) {
	if (index > size)
		throw std::out_of_range("");
	else if (index == 0)
		pop();
	else if (index == size - 1)
		popBack();
	else {
		Node<T>* current = head;
		for (size_t i = 0; i < index - 1; i++)
			current = current->getNext();
		T data = current->getNext()->getData();
		Node<T>* toDelete = current->getNext();
		current->setNext(current->getNext()->getNext());
		delete toDelete;
		size--;
		return data;
	}
}

template <typename T> void SinglyLinkedList<T>::push(const T& element) {
	Node<T>* add = new Node<T>;
	add->setData(&element);
	if (isEmpty())
		head = tail = add;
	else
	{
		add->setNext(head);
		head = add;
	}
	size++;
}
template <typename T> T SinglyLinkedList<T>::pop() {
	if (isEmpty())
		throw std::length_error("");
	T data = head->getData();
	if (size > 1) {
		Node<T>* toDelete = head;
		head = head->getNext();
		delete toDelete;
	}
	else {
		delete head;
		head = tail = nullptr;
	}
	size--;
	return data;
}

template <typename T> void SinglyLinkedList<T>::pushBack(const T& element) {
	Node<T>* add = new Node<T>;
	add->setData(&element);
	if (isEmpty())
		head = tail = add;
	else {
		tail->setNext(add);
		tail = add;
	}
	size++;
}
template <typename T> T SinglyLinkedList<T>::popBack() {
	if (isEmpty())
		throw std::length_error("");
	T data = tail->getData();
	if (size > 1) {
		Node<T>* current = head;
		while (current->getNext() != tail)
			current = current->getNext();
		delete tail;
		tail = current;
	}
	else {
		delete tail;
		head = tail = nullptr;
	}
	size--;
	return data;
}

template <typename T> T SinglyLinkedList<T>::getAt(size_t index) {
	if (index == 0) return peak();
	else if (index < size) {
		Node<T>* iterator = head;
		for (size_t i = 0; i < index; i++)
			iterator = iterator->getNext();
		return iterator->getData();
	}
	else throw std::length_error("");
}
template <typename T> T SinglyLinkedList<T>::peak() const {
	if (isEmpty()) throw std::length_error("");
	return head->getData();
}

template <typename T> T& SinglyLinkedList<T>::operator[] (size_t index) {
	if (index >= size) throw std::out_of_range("");
	Node<T>* ptr;
	getAtIndex(index, ptr);
	return ptr->data;
}
template <typename T> const T& SinglyLinkedList<T>::operator[] (size_t index) const {
	if (index >= size) throw std::out_of_range("");
	Node<T>* iterator = head;
	for (size_t i = 0; i < index; i++)
		iterator = iterator->getNext();
	return iterator->getData(); // getData() is const so cant return a reference to it
}

template <typename T> bool SinglyLinkedList<T>::isEmpty() const {
	return size == 0;
}
template <typename T> size_t SinglyLinkedList<T>::getSize() const {
	return size;
}
template <typename T> void SinglyLinkedList<T>::print() const {
	if (isEmpty()) return;
	Node<T>* current = head;
	while (current != tail) {
		current->print();
		current = current->getNext();
	}
	current->print();
	std::cout << std::endl;
}
template <typename T> void SinglyLinkedList<T>::reverse() {
	//1: convert toDoublyLinked and convertBack to singlyLinked from tail to head
	//recursive???
	//push(popBack) * size -> verySlow;
}



