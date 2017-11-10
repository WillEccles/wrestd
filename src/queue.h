#ifndef QUEUE_H
#define QUEUE_H

#include "collections.h"
#include "nodes.h"
#include <iostream>
#include <memory> // std::shared_ptr

using wrestd::collections::single_link_node;

template <class T>
class wrestd::collections::queue {
	private:
		// the qnode class to be used in the queue
		typedef single_link_node<T> qnode;

		std::shared_ptr<qnode> _front; // shouldn't change or we lose the list
		std::shared_ptr<qnode> _back; // since we wanna be able to get to the end of the list quickly
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
