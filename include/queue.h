#ifndef WRESTD_QUEUE_H
#define WRESTD_QUEUE_H

#include "collections.h"
#include "nodes.h"
#include <iostream>
#include <memory> // std::shared_ptr

using wrestd::collections::nodes::single_link_node;

namespace wrestd {
	namespace collections {
		template <class T>
		class queue
		{
		private:
			// the qnode class to be used in the queue
			typedef single_link_node<T> qnode;

			std::shared_ptr<qnode> _front; // shouldn't change or we lose the list
			std::shared_ptr<qnode> _back;  // since we wanna be able to get to the end of the list quickly
			size_t _numItems = 0;

		public:
			// constructors
			queue() {
				_front = nullptr;
				_back = nullptr;
			};
			queue(T firstVal) {
				_front = std::shared_ptr<qnode>(new qnode(firstVal, _back));
				_numItems = 1;
			};

			// push a new value to the queue
			void enqueue(T val) {
				if (_front == nullptr)
				{
					_front = std::shared_ptr<qnode>(new qnode(val, _back));
				}
				else
				{
					if (_back == nullptr)
					{
						_back = std::shared_ptr<qnode>(new qnode(val, nullptr));
						_front->setNext(_back);
					}
					else
					{
						std::shared_ptr<qnode> newNext(new qnode(val, nullptr));
						_back->setNext(newNext);
						_back = _back->getNext();
					}
				}
				_numItems++;
			};

			// pop a value from the queue
			T dequeue() {
				if (_front == nullptr)
				{
					return static_cast<T>(NULL);
				}
				else
				{
					T val = _front->getValue();
					_front = _front->getNext();
					_numItems--;
					return val;
				}
			};

			// remove all the items from the queue
			void dequeueAll() {
				std::shared_ptr<qnode> curr = _front;
				while (curr != nullptr)
				{
					std::shared_ptr<qnode> next = curr->getNext();
					delete curr;
					curr = next;
				}
				_front = nullptr;
				_numItems = 0;
			};

			// peek at the front of the queue
			T peek() {
				return _front->getValue();
			};

			// for printing the queue out (mainly for debug)
			void print() {
				if (isEmpty())
				{
					std::cout << "Queue is empty." << std::endl;
				}
				else
				{
					std::shared_ptr<qnode> curr = _front;
					while (curr != nullptr)
					{
						std::cout << curr->getValue() << ' ';
						curr = curr->getNext();
					}
					std::cout << std::endl;
				}
			};

			// if you want to loop through and apply an operation to each value in the queue
			void doForEach(T (*op)(T)) {
				std::shared_ptr<qnode> curr = _front;
				while (curr != nullptr)
				{
					curr->setValue(op(curr->getValue()));
					curr = curr->getNext();
				}
			};

			// getSize and isEmpty are pretty self-explanatory
			size_t getSize() { return _numItems; };
			bool isEmpty() { return !_numItems; };

			// destructor because we like having memory amirite
			~queue();
		};
	};
};

#endif