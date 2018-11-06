#ifndef WRESTD_COLLECTIONS_H
#define WRESTD_COLLECTIONS_H

#include <algorithm>
#include <vector>

namespace wrestd {
	namespace collections {
		namespace util {
			// todo: make this work for any type of collection so long as the algorithms work on it
			template <class T>
			bool contains(std::vector<T> &v, T item)
			{
				return std::find(v.begin(), v.end(), item) != v.end();
			};
		};
	};
};

#endif
