#pragma once
#include <iostream>

template <typename T> class structuresInterface {
	virtual void push(const T& element) = 0; //pushFront 
	virtual void pushBack(const T& element) = 0;
	virtual void addAt(const T& element, size_t index) = 0;
	virtual T removeAt(size_t index) = 0;

	virtual T& operator[](size_t index) = 0;
	virtual const T& operator[](size_t index) const = 0; //peek at position


	virtual T pop() = 0; //popFront
	virtual T popBack() = 0;

	virtual T getAt(size_t index) = 0;
	virtual T peak() const = 0;

	virtual size_t getSize() const = 0;
	virtual void print() const = 0;
	virtual bool isEmpty() const = 0;
};