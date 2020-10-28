#pragma once
#include <iostream>

template <typename T>
class structuresInterface {
	virtual void push(const T& element) = 0;
	virtual void pushBack(const T& element) = 0;
	virtual void addAt(const T& element, size_t index) = 0;
	virtual T* pop() = 0;
	virtual T* popBack() = 0;
	virtual T* getAt(size_t index) = 0;
	virtual T* peak() = 0 const;
	virtual size_t getSize() = 0 const;
	virtual void print() = 0 const;
	virtual bool empty() = 0 const;
};