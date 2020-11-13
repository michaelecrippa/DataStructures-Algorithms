#include <iostream>

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


//using the structure of SinglyLinkedList to implement the stack
template <typename T> class Stack {
	Node<T>* head;
	size_t size;

	void erase();
	void copyFrom(const Stack<T>&);
	bool isEmpty() const;
public:
	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();

	void push(const T& element);
	T pop();
	T peak();

	size_t getSize() const;

	void print() const;
};
template <typename T> void Stack<T>::erase(){
	if (isEmpty()) return;
	Node<T>* helper;
	while (head != nullptr) {
		helper = head->getNext();
		delete head;
		head = helper;
	}
	head = nullptr;
	size = 0;
}
template <typename T> void Stack<T>::copyFrom(const Stack<T>& other){
	if (other.isEmpty()) erase();
	short diff = this->size - other.size;
	if (diff > 0)
		for (short i = 0; i < diff; i++)
			 pop();
	else
		for (short i = 0; i > diff; i--)
			push((T)0);
	Node<T>* cursor = head;
	Node<T>* otherCursor = other.head;
	while (cursor != nullptr){
		cursor->setData(&otherCursor->data);
		cursor = cursor->getNext();
		otherCursor = otherCursor->getNext();
	}
}

template <typename T> Stack<T>::Stack() {
	head = nullptr;
	size = 0;
}
template <typename T> Stack<T>::Stack(const Stack<T>& other) {
	copyFrom(other);
}
template <typename T> Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	if (this != &other)
		copyFrom(other);
	return *this;
}
template <typename T> Stack<T>::~Stack() {
	erase();
}

template <typename T> void Stack<T>::push(const T& element){
	Node<T>* add = new Node<T>;
	add->setData(&element);
	add->setNext(head);
	head = add;
	size++;
}
template <typename T> T Stack<T>::pop(){
	if (isEmpty()) throw std::out_of_range("");
	T data = head->getData();
	Node<T>* toDelete = head;
	head = head->getNext();
	delete toDelete;
	size--;
	return data;
}
template <typename T> T Stack<T>::peak() {
	if (isEmpty()) throw std::out_of_range("");
	return head->getData();
}

template <typename T> bool Stack<T>::isEmpty() const {
	return head == nullptr;
}
template <typename T> size_t Stack<T>::getSize() const {
	return size;
}
template <typename T> void Stack<T>::print() const {
	if (isEmpty()) throw std::out_of_range("");
	Node<T>* iter = head;
	std::cout << "Head -> ";
	while (iter != nullptr) {
		iter->print();
		iter = iter->getNext();
	}
}
