#ifndef STACK_H
#define STACK_H

#include "collections.h"
#include "nodes.h"
#include <iostream>
#include <vector>
#include <memory> // std::shared_ptr

using namespace wrestd::collections;

template<class T>
class wrestd::collections::stack {
private:
	// the snode class to be used in linked applications
	typedef single_link_node<T> snode;
	std::shared_ptr<snode> _top; // shouldn't change or we lose the list
	size_t _numItems = 0;
public:
	// constructors
	stack();
	stack(T firstVal);

	// push a new value to the stack
	void push(T val);
	
	// pop a value from the stack
	T pop();
	
	// remove all the items from the stack
	void popAll();

	// peek at the top of the stack
	T peek();

	// for printing the stack out
	void print();

	// if you want to loop through and apply an operation to each value in the stack
	void doForEach(T (*op)(T));

	// getSize and isEmpty are pretty self-explanatory
	size_t getSize() { return _numItems; };
	bool isEmpty() { return !_numItems; };

	// destructor because we like having memory amirite
	~stack();
};

#endif
