#include "baseStructureInterface.h"

template <typename T> struct Node {
	T data;
	Node* next;
	Node* prev;

	Node<T>();

	T getData() const;
	void setData(const T* data);

	Node<T>* getNext() const;
	void setNext(const Node<T>* next);

	Node<T>* getPrevious() const;
	void setPrevious(const Node<T>* prev);

	void print() const;
};
template <typename T> Node<T>::Node<T>() {
	next = prev = nullptr;
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

template <typename T> Node<T>* Node<T>::getPrevious() const {
	return prev;
}
template <typename T> void Node<T>::setPrevious(const Node<T>* prev) {
	if (this == nullptr) return;
	this->prev = (Node<T>*)prev;
}
template <typename T> void Node<T>::print() const {
	if (this == nullptr) return;
	std::cout << data << ' ';
}

template <typename T> class DoublyLinkedList : public structuresInterface<T> {
	Node<T>* head;
	Node<T>* tail;
	size_t size;

	void erase();
	void copyFrom(const DoublyLinkedList<T>& other);

	void getAtIndex(size_t index, Node<T>*& ptr); //for operato[] so can return a reference
	bool isEmpty() const;
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
	~DoublyLinkedList();

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
template <typename T> void DoublyLinkedList<T>::erase() {
	if (isEmpty()) return;
	while (head != tail) { //more than 1 element
		head = head->getNext();
		delete head->getPrevious();
	}
	delete head; //1 element left to delete
	head = tail = nullptr;
}
template <typename T> void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {
	short diff = size - other.size;
	//other is larger
	if (diff < 0)
		for (short i = diff; i < 0; i++)
			this->pushBack((T)0);
	//other is smaller or equal
	else
		for (short i = 0; i < diff; i++)
			this->popBack();
	//copy data from the other list
	Node<T>* cursor = head;
	Node<T>* otherCursor = other.head;
	while (cursor != nullptr) {
		cursor->setData(&otherCursor->data);
		cursor = cursor->getNext();
		otherCursor = otherCursor->getNext();
	}
}

template <typename T> DoublyLinkedList<T>::DoublyLinkedList() {
	head = tail = nullptr;
	size = 0;
}
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) {
	copyFrom(other);
}
template <typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
	if (this != &other)
		copyFrom(other);
	return *this;
}
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
	erase();
}

template <typename T> void DoublyLinkedList<T>::getAtIndex(size_t index, Node<T>*& ptr)
{
	if (index > size / 2) {
		Node<T>* iterator = tail;
		for (size_t i = size - 1; i >= index; i--)
			iterator = iterator->getPrevious();
		ptr = iterator;
	}
	else {
		Node<T>* iterator = head;
		for (size_t i = 0; i < index; i++)
			iterator = iterator->getNext();
		ptr = iterator;
	}
}
template <typename T> void DoublyLinkedList<T>::addAt(const T& element, size_t index) {
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
		current->getNext()->setPrevious(add);
		add->setPrevious(current);
		size++;
	}
}
template <typename T> T DoublyLinkedList<T>::removeAt(size_t index) {
	if (index > size)
		throw std::out_of_range("");
	else if (index == 0)
		pop();
	else if (index == size - 1)
		popBack();
	else {
		Node<T>* current = head;
		for (size_t i = 0; i < index; i++)
			current = current->getNext();
		current->getNext()->setPrevious(current->getPrevious());
		current->getPrevious()->setNext(current->getNext());
		T data = current->getData();
		delete current;
		size--;
		return data;
	}
}

template <typename T> void DoublyLinkedList<T>::push(const T& element) {
	Node<T>* add = new Node<T>;
	add->setData(&element);
	if (isEmpty())
		head = tail = add;
	else
	{
		add->setNext(head);
		head->setPrevious(add); 
		head = add;
	}	
	size++;
}
template <typename T> T DoublyLinkedList<T>::pop() {
	if (isEmpty()) 
		throw std::length_error("");
	T data = head->getData();
	if (size > 1) {
		head = head->getNext();
		delete head->getPrevious();
		head->setPrevious(nullptr);
	}
	else {		
		delete head;
		head = tail = nullptr;
	}
	size--;
	return data;
}

template <typename T> void DoublyLinkedList<T>::pushBack(const T& element) {
	Node<T>* add = new Node<T>;
	add->setData(&element);
	if (isEmpty())
		head = tail = add;
	else {
		add->setPrevious(tail);
		tail->setNext(add);
		tail = add;
	}	
	size++;
}
template <typename T> T DoublyLinkedList<T>::popBack() {
	if (isEmpty())
		throw std::length_error("");
	T data = tail->getData();
	if (size > 1) {
		tail = tail->getPrevious();
		delete tail->getNext();
		tail->setNext(nullptr);
	}
	else {
		delete tail;
		head = tail = nullptr;
	}
	size--;
	return data;
}

template <typename T> T DoublyLinkedList<T>::getAt(size_t index) {
	if (index == 0) return peak();
	else if (index < size) {
		if (index > size / 2) {
			Node<T>* iterator = tail;
			for (size_t i = size - 1; i >= index; i--)
				iterator = iterator->getPrevious();
			return iterator->getData();
		}
		else {
			Node<T>* iterator = head;
			for (size_t i = 0; i < index; i++)
				iterator = iterator->getNext();
			return iterator->getData();
		}
	}
	else throw std::length_error("");
}
template <typename T> T DoublyLinkedList<T>::peak() const {
	if (isEmpty()) throw std::length_error("");
	return head->getData();
}

template <typename T> T& DoublyLinkedList<T>::operator[] (size_t index) { 
	if (index >= size) throw std::out_of_range("");
	Node<T>* ptr;
	getAtIndex(index, ptr);
	return ptr->data;
}
template <typename T> const T& DoublyLinkedList<T>::operator[] (size_t index) const { 
	if (index >= size) throw std::out_of_range("");
	if (index > size / 2) {
		Node<T>* iterator = tail;
		for (size_t i = size - 1; i >= index; i--)
			iterator = iterator->getPrevious();
		return iterator->getData();
	}
	else {
		Node<T>* iterator = head;
		for (size_t i = 0; i < index; i++)
			iterator = iterator->getNext();
		return iterator->getData(); // getData() is const so cant return a reference to it
	}
}

template <typename T> bool DoublyLinkedList<T>::isEmpty() const {
	return size == 0;
}
template <typename T> size_t DoublyLinkedList<T>::getSize() const{
	return size;
}
template <typename T> void DoublyLinkedList<T>::print() const {
	if (isEmpty()) return;
	Node<T>* current = head;
	while (current != tail) {
		current->print();
		current = current->getNext();	
	}
	current->print();
	std::cout << std::endl;
}
template <typename T> void DoublyLinkedList<T>::reverse() {
	if (isEmpty()) return;
	Node<T>* helper = head;
	head = tail;
	tail = helper;
}
