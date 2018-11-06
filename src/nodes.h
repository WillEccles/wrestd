#ifndef WRESTD_NODES_H
#define WRESTD_NODES_H

#include <memory>

namespace wrestd {
	namespace collections {
		namespace nodes {
			// a basic node class, mostly used to derive other node types
			template<class T, class nType>
				class node {
					protected:
						T _value;
						std::shared_ptr<nType> _child;
					public:
						node(T value): _value(value) { _child = 0; };
						T getValue() { return _value; };
						void setValue(T val) { _value = val; };
						void setChild(std::shared_ptr<nType> c) { _child = c; };
						auto getChild() { return _child; };
				};

			// general-purpose singly-linked node:
			// has 1 value (of type T)
			// keeps a reference to 1 child
			template<class T>
				class single_link_node : protected node<T, single_link_node<T>> {
					public:
						single_link_node(T value,
								std::shared_ptr<single_link_node<T>> child = 0): node<T, single_link_node<T>>(value) {
							this->_child = child;
						};
				};

			// general-purpose doubly-linked node:
			// has 1 value (of type T)
			// keeps a reference to 1 child
			// keeps a reference to 1 parent
			template<class T>
				class double_link_node : protected node<T, double_link_node<T>> {
					private:
						std::shared_ptr<double_link_node<T>> _parent;
					public:
						double_link_node(T value,
								std::shared_ptr<double_link_node<T>> parent = 0,
								std::shared_ptr<double_link_node<T>> child = 0): node<T, double_link_node<T>>(value) {
							_parent = parent;
							this->_child = child;
						};
						auto getParent() {
							return _parent;
						};
						void setParent(std::shared_ptr<double_link_node<T>> newParent) {
							_parent = newParent;
						};
				};

			// general-purpose tree node:
			// has 1 value (of type T)
			// has a left child and a right child
			// does not keep a reference to its parent
			template<class T>
				class tree_node : protected node<T, tree_node<T>> {
					private:
						// the inherited _child will be used as the left child
						std::shared_ptr<tree_node<T>> _rchild;
					public:
						tree_node(T value,
								std::shared_ptr<tree_node<T>> leftchild = 0,
								std::shared_ptr<tree_node<T>> rightchild = 0): node<T, tree_node<T>>(value) {
							this->_child = leftchild;
							_rchild = rightchild;
						};
						auto getLeftChild() {
							return this->_child;
						};
						auto getRightChild() {
							return _rchild;
						};
						void setLeftChild(std::shared_ptr<tree_node<T>> lchild) {
							this->_child = lchild;
						};
						void setRightChild(std::shared_ptr<tree_node<T>> rchild) {
							_rchild = rchild;
						};
				};
		};
	};
};

#endif