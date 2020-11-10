#include "baseStructureInterface.h"
template <typename T>
class vector : public structuresInterface<T> {
private:
	T* container;
	size_t size;
	size_t capacity;

	void erase();
	void copyFrom(const vector& other);
	void resize();
	void resizeDown();
	bool isEmpty() const;
	T getAt(size_t index);

public:
	vector();
	vector(const vector& other);
	vector& operator=(const vector& other);
	~vector();
	
	
	void push(const T& element);
	void pushBack(const T& element);
	void addAt(const T& element, size_t index);
	T pop();
	T popBack();
	T removeAt(size_t index);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T peak() const;
	size_t getSize() const;
	void print() const;
};
