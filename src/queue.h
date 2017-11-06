#ifndef QUEUE_H
#define QUEUE_H

#include "collections.h"
#include <iostream>
#include <vector>
#include <memory> // std::shared_ptr

template <class T>
class wrestd::collections::queue {
private:
	// the node class to be used in the queue
	template <class nT = T>
	class node {
		private:
			nT _value;
			std::shared_ptr<node<nT>> _next;
		public:
			node(nT value): _value(value) { _next = 0; };
			node(nT value, std::shared_ptr<node<nT>> next): _value(value), _next(next) {};
			nT getValue() { return _value; };
			void setValue(nT newValue) { _value = newValue; };
			std::shared_ptr<node<nT>> getNext() { return _next; };
			void setNext(std::shared_ptr<node<nT>> next) { _next = next; };
	};
	
	std::shared_ptr<node<T>> _front; // shouldn't change or we lose the list
	std::shared_ptr<node<T>> _back; // since we wanna be able to get to the end of the list quickly
	size_t _numItems = 0;
public:
	// constructors
	queue();
	queue(T firstVal);

	// push a new value to the queue
	void enqueue(T val);

	// pop a value from the queue
	T dequeue();
	
	// remove all the items from the queue
	void dequeueAll();

	// peek at the front of the queue
	T peek();

	// for printing the queue out
	void print();

	// if you want to loop through and apply an operation to each value in the queue
	void doForEach(T (*op)(T));

	// getSize and isEmpty are pretty self-explanatory
	size_t getSize() { return _numItems; };
	bool isEmpty() { return !_numItems; };

	// destructor because we like having memory amirite
	~queue();
};

#endif
