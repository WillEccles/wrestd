#ifndef WRESTD_QUEUE_H
#define WRESTD_QUEUE_H

#include "wrenodes.h"
#include <iostream>
#include <memory> // std::shared_ptr
#include <mutex>
#include <exception>
#include <thread>

using wrestd::collections::nodes::single_link_node;

namespace wrestd {
	namespace collections {
		// Exception thrown when an attempt is made to dequeue something from an empty queue.
		struct DequeueEmptyQueueException : public std::exception
		{
			const char *what() const throw()
			{
				return "Attempted to dequeue item from empty queue.";
			};
		};

		struct AlreadyWaitingException : public std::exception {
			const char *what() const throw() {
				return "This concurrent_queue is already awaiting dequeue.";
			};
		};
		
		template <class T>
		class queue // A simple FIFO queue implementation.
		{
		private:
			// the qnode class to be used in the queue
			typedef single_link_node<T> qnode;

			std::shared_ptr<qnode> _front; // shouldn't change or we lose the list
			std::shared_ptr<qnode> _back;  // since we wanna be able to get to the end of the list quickly
			std::size_t _numItems = 0;

		protected:
			std::mutex lock_obj; // used to lock the queue
		public:
			// constructors
			queue()
			{
				_front = nullptr;
				_back = nullptr;
			};

			// push a new value to the queue
			void enqueue(T val)
			{
				if (_front == nullptr)
				{
					_front = std::shared_ptr<qnode>(new qnode(val, _back));
				}
				else
				{
					if (_back == nullptr)
					{
						_back = std::shared_ptr<qnode>(new qnode(val, nullptr));
						_front->setChild(_back);
					}
					else
					{
						std::shared_ptr<qnode> newNext(new qnode(val, nullptr));
						_back->setChild(newNext);
						_back = _back->getChild();
					}
				}
				_numItems++;
			};

			// pop a value from the queue
			// can throw a DequeueEmptyQueueException
			T dequeue()
			{
				if (_front == nullptr)
				{
					throw wrestd::collections::DequeueEmptyQueueException();
				}
				else
				{
					T val = _front->getValue();
					_front = _front->getChild();
					_numItems--;
					return val;
				}
			};

			// remove all the items from the queue
			void dequeueAll()
			{
				std::shared_ptr<qnode> curr = _front;
				while (curr != nullptr)
				{
					std::shared_ptr<qnode> next = curr->getChild();
					curr = next;
				}
				_front = nullptr;
				_numItems = 0;
			};

			// peek at the front of the queue
			T peek()
			{
				return _front->getValue();
			};

			// for printing the queue out (mainly for debug)
			void print()
			{
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
						curr = curr->getChild();
					}
					std::cout << std::endl;
				}
			};

			// if you want to loop through and apply an operation to each value in the queue
			void doForEach(T (*op)(T))
			{
				std::shared_ptr<qnode> curr = _front;
				while (curr != nullptr)
				{
					curr->setValue(op(curr->getValue()));
					curr = curr->getNext();
				}
			};

			// getSize and isEmpty are pretty self-explanatory
			std::size_t getSize() { return _numItems; };
			bool isEmpty() { return !_numItems; };

			// destructor because we like having memory amirite
			~queue(){/* Should automatically delete all pointers. */};
		};

		template<typename T>
		class concurrent_queue : protected wrestd::collections::queue<T> { // A version of the queue type that is thread-safe.
		private:
			bool isWaitingForDequeue = false;
			bool shouldAwaitDequeue = false;
			std::thread await_thread;
		public:
			concurrent_queue(): wrestd::collections::queue<T>() {};

			// enqueue a value
			void enqueue(T val) {
				std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj);
				wrestd::collections::queue<T>::enqueue(val);
			};

			// dequeue the top of the queue
			// use try_dequeue instead!
			T dequeue() {
				std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj);
				return wrestd::collections::queue<T>::dequeue();
			};

			// returns a bool indicating whether or not an item was found
			// if true, output's value is set to the found item.
			bool try_dequeue(T &output) {
				if (wrestd::collections::queue<T>::isEmpty()) return false;
				else {
					std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj);
					output = wrestd::collections::queue<T>::dequeue();
					return true;
				}
			};

			// awynchronously wait for an item in the queue, and when there is one, perform callback.
			// can only be running once for a given instance of concurrent_queue
			// will throw AlreadyWaitingException if called multiple times
			// this can be cancelled with stop_waiting()
			template<typename Functor>
			void await_dequeue(Functor callback) {
				if (isWaitingForDequeue) throw AlreadyWaitingException();
				isWaitingForDequeue = true;
				shouldAwaitDequeue = true;
				await_thread = std::thread([&] {
					T o;
					while (shouldAwaitDequeue) {
						if (try_dequeue(o))
							callback(o);
					}
				});
			};
			
			// stop the queue from awaiting dequeue.
			void stop_waiting() {
				if (!isWaitingForDequeue) return;
				shouldAwaitDequeue = false;
				await_thread.join();
				isWaitingForDequeue = false;
			};

			// dequeue all of the items in the queue
			void dequeueAll() {
				std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj);
				wrestd::collections::queue<T>::dequeueAll();
			};

			// print all queue values mainly for debug purposes
			void print() {
				std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj); // lock because we use std::cout which will get mangled if we did it at the same time
				wrestd::collections::queue<T>::print();
			};

			// if you want to loop through and apply an operation to each value in the queue
			void doForEach(T (*op)(T)){
				std::lock_guard<std::mutex> lock(wrestd::collections::queue<T>::lock_obj);
				wrestd::collections::queue<T>::doForEach(op);
			};

			~concurrent_queue() {
				stop_waiting();
			};
		};
	};
};

#endif