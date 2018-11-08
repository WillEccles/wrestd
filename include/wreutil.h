#ifndef WRESTD_UTIL_H
#define WRESTD_UTIL_H

#include <algorithm>
#include <vector>

namespace wrestd {
	namespace util {
		template<typename T>
		T clamp(T val, T min, T max) {
			if (val > max) return max;
			if (val < min) return min;
			return val;
		};

		template<typename T>
		T upper_limit(T val, T max) {
			return (val > max ? max : val);
		};

		template<typename T>
		T lower_limit(T val, T min) {
			return (val < min ? min : val);
		};

		// swap two integral values in-place, using no extra memory (no temporary value)
		// using this on non-integral types will result in some fun things so don't do that
		template<typename T>
		void in_place_swap(T &i1, T &i2) {
			i1 ^= i2;
			i2 ^= i1;
			i1 ^= i2;
		};

		// todo: make this work for any type of collection so long as the algorithms work on it
		template <class T>
		bool v_contains(std::vector<T> &v, T item) {
			return std::find(v.begin(), v.end(), item) != v.end();
		};
	};
};

#endif