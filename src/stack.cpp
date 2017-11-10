#include "stack.h"

using wrestd::collections::stack;

// default constructor
template<class T>
stack<T>::stack() {
	_top = nullptr; // set _top to nullptr
}

// overloaded constructor
template<class T>
stack<T>::stack(T firstVal) {
	_top(new snode(firstVal));
	_numItems = 1;
}

// destructor because we like having memory amirite
template<class T>
stack<T>::~stack() {
	_top.reset();
}

// push a new value to the stack
template<class T>
void stack<T>::push(T val) {
	if (_top == nullptr) {
		_top = std::shared_ptr<snode>(new snode(val));
	} else {
		std::shared_ptr<snode> newNext = _top;
		_top = std::shared_ptr<snode>(new snode(val, newNext));
	}
	_numItems++;
}

// pop a value from the stack
template<class T>
T stack<T>::pop() {
	if (_top == nullptr) {
		return static_cast<T>(NULL);
	} else {
		std::shared_ptr<snode> old = _top;
		_top = _top->getChild();
		_numItems--;
		T rval = old->getValue();
		return rval;
	}
};

// remove all the items from the stack
template<class T>
void stack<T>::popAll() {
	std::shared_ptr<snode> curr = _top;
	while (curr != nullptr) {
		std::shared_ptr<snode> next = curr->getChild();
		curr = next;
	}
	_top = nullptr;
	_numItems = 0;
}

// peek at the top of the stack
template<class T>
T stack<T>::peek() {
	return _top->getValue();
};

// for printing the stack out
template<class T>
void stack<T>::print() {
	if (isEmpty()) {
		std::cout << "Stack is empty." << std::endl;
	} else {
		std::shared_ptr<snode> curr = _top;
		while (curr != nullptr) {
			std::cout << curr->getValue() << ' ';
			curr = curr->getChild();
		}
		std::cout << std::endl;
	}
}

// if you want to loop through and apply an operation to each value in the stack
template<class T>
void stack<T>::doForEach(T (*op)(T)) {
	std::shared_ptr<snode> curr = _top;
	while (curr != nullptr) {
		curr->setValue(op(curr->getValue()));
		curr = curr->getChild();
	}
};
