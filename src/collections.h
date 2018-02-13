#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <algorithm>
#include <vector>

namespace wrestd {
	namespace collections {
		template<class T>
			class queue;
		template<class T>
			class stack;
		template<class T>
			class binarysearchtree;

		// todo: make this work for any type of collection so long as the algorithms work on it
		template<class T>
			bool v_contains(std::vector<T>& v, T item) {
				return std::find(v.begin(), v.end(), item) != v.end();
			};
	};
};

#endif
