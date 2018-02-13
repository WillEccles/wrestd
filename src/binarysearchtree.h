#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "collections.h"
#include <memory>

template<class T>
class wrestd::collections::binarysearchtree {
	private:
		template<class nT>
			class node {
				private:
					nT _value;
					std::shared_ptr<node<nT>> _leftchild;
					std::shared_ptr<node<nT>> _rightchild;
				public:
					node(nT value, std::shared_ptr<node<nT>> leftchild = 0, std::shared_ptr<node<nT>> rightchild = 0): _value(value), _leftchild(leftchild), _rightchild(rightchild) {};
					nT getValue() { return _value; };
					void setValue(nT val) { _value(val); };
					
			};

	public:
};

#endif
