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
public:
	vector();
	vector(const vector& other);
	vector& operator=(const vector& other);
	~vector();
	
	
	void push(const T& element);
	void pushBack(const T& element);
	void addAt(const T& element, size_t index);
	T* pop();
	T* popBack();
	T* removeAt(size_t index);
	T* getAt(size_t index);
	T* peak() const;
	size_t getSize() const;
	void print() const;
	bool empty() const;
};
