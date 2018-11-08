#ifndef WRESTD_STACK_H
#define WRESTD_STACK_H

#include "wrenodes.h"
#include <iostream>
#include <memory> // std::shared_ptr

using wrestd::collections::nodes::single_link_node;

namespace wrestd {
	namespace collections {
		template <typename T>
		class stack
		{
		private:
			// the snode class to be used in linked applications
			typedef single_link_node<T> snode;
			std::shared_ptr<snode> _top; // shouldn't change or we lose the list
			size_t _numItems = 0;

		public:
			// constructors
			stack() {
				_top = nullptr; // set _top to nullptr
			};
			stack(T firstVal) {
				_top.reset();
			};

			// push a new value to the stack
			void push(T val) {
				if (_top == nullptr)
				{
					_top = std::shared_ptr<snode>(new snode(val));
				}
				else
				{
					std::shared_ptr<snode> newNext = _top;
					_top = std::shared_ptr<snode>(new snode(val, newNext));
				}
				_numItems++;
			};

			// pop a value from the stack
			T pop() {
				if (_top == nullptr)
				{
					return static_cast<T>(NULL);
				}
				else
				{
					std::shared_ptr<snode> old = _top;
					_top = _top->getChild();
					_numItems--;
					T rval = old->getValue();
					return rval;
				}
			};

			// remove all the items from the stack
			void popAll() {
				std::shared_ptr<snode> curr = _top;
				while (curr != nullptr)
				{
					std::shared_ptr<snode> next = curr->getChild();
					curr = next;
				}
				_top = nullptr;
				_numItems = 0;
			};

			// peek at the top of the stack
			T peek() {
				return _top->getValue();
			};

			// for printing the stack out
			void print() {
				if (isEmpty())
				{
					std::cout << "Stack is empty." << std::endl;
				}
				else
				{
					std::shared_ptr<snode> curr = _top;
					while (curr != nullptr)
					{
						std::cout << curr->getValue() << ' ';
						curr = curr->getChild();
					}
					std::cout << std::endl;
				}
			};

			// if you want to loop through and apply an operation to each value in the stack
			void doForEach(T (*op)(T)) {
				std::shared_ptr<snode> curr = _top;
				while (curr != nullptr)
				{
					curr->setValue(op(curr->getValue()));
					curr = curr->getChild();
				}
			};

			// getSize and isEmpty are pretty self-explanatory
			size_t getSize() { return _numItems; };
			bool isEmpty() { return !_numItems; };

			// destructor because we like having memory amirite
			~stack();
		};
	};
};

#endif