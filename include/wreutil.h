#ifndef WRESTD_UTIL_H
#define WRESTD_UTIL_H

#include <algorithm>
#include <vector>
#include <random>
#include <cstdio>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>

namespace wrestd {
	namespace util {
		// swap two integral values in-place, using no extra memory (no temporary value)
		// this is very efficient for algorithms, etc.
		// using this on non-integral types will result in some fun things so don't do that
		template<typename T>
		inline void in_place_swap(T &i1, T &i2) {
			i1 ^= i2;
			i2 ^= i1;
			i1 ^= i2;
		};

		// todo: make this work for any type of collection so long as the algorithms work on it
		template <class T>
		bool v_contains(std::vector<T> &v, T item) {
			return std::find(v.begin(), v.end(), item) != v.end();
		};

		// generate random integral type in range [min, max]
		template <typename numType = int>
		numType rand_in_range(numType min, numType max) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<numType> dist(min, max);
			return dist(gen);
		};

#ifndef __WIN32
		// runs a command and returns the output
		// this likely doesn't include stderr by default, so you must manually add
		// something like 2>&1 yourself if you want it
		// throws a std::runtime_error if something goes wrong with popen()
		std::string exec(const std::string& cmd) {
			std::array<char, 128> buff;
			std::string res;
			std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
			if (!pipe) {
				throw std::runtime_error("popen() failed!");
			}
			while (fgets(buff.data(), buff.size(), pipe.get()) != nullptr) {
				res += buff.data();
			}
			return res;
		}
#endif
	};
};

#endif
