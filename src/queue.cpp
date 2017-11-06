#include "queue.h"

using wrestd::collections::queue;

// default constructor
template<class T>
queue<T>::queue() {
	_front = nullptr; // set _front to nullptr
	_back = nullptr;
}

// overloaded constructor
template<class T>
queue<T>::queue(T firstVal) {
	_front = std::shared_ptr<node<T>>(new node<T>(firstVal, _back));
	_numItems = 1;
}

// push a new value to the queue
template<class T>
void queue<T>::enqueue(T val) {
	if (_front == nullptr) {
		_front = std::shared_ptr<node<T>>(new node<T>(val, _back));
	} else {
		if (_back == nullptr) {
			_back = std::shared_ptr<node<T>>(new node<T>(val, nullptr));
			_front->setNext(_back);
		} else {
			std::shared_ptr<node<T>> newNext(new node<T>(val, nullptr));
			_back->setNext(newNext);
			_back = _back->getNext();
		}
	}
	_numItems++;
}

// pop a value from the queue
template<class T>
T queue<T>::dequeue() {
	if (_front == nullptr) {
		return static_cast<T>(NULL);
	} else {
		T val = _front->getValue();
		_front = _front->getNext();
		_numItems--;
		return val;
	}
}

// remove all the items from the queue
template<class T>
void queue<T>::dequeueAll() {
	std::shared_ptr<node<T>> curr = _front;
	while (curr != nullptr) {
		std::shared_ptr<node<T>> next = curr->getNext();
		delete curr;
		curr = next;
	}
	_front = nullptr;
	_numItems = 0;
}

// peek at the front of the queue
template<class T>
T queue<T>::peek() {
	return _front->getValue();
}

// for printing the queue out
template<class T>
void queue<T>::print() {
	if (isEmpty()) {
		std::cout << "Queue is empty." << std::endl;
	} else {
		std::shared_ptr<node<T>> curr = _front;
		while (curr != nullptr) {
			std::cout << curr->getValue() << ' ';
			curr = curr->getNext();
		}
		std::cout << std::endl;
	}
}

// if you want to loop through and apply an operation to each value in the queue
template<class T>
void queue<T>::doForEach(T (*op)(T)) {
	std::shared_ptr<node<T>> curr = _front;
	while (curr != nullptr) {
		curr->setValue(op(curr->getValue()));
		curr = curr->getNext();
	}
}
