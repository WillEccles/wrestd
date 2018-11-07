#ifndef WRESTD_THREADING_H
#define WRESTD_THREADING_H

#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>

using namespace std::chrono;

namespace wrestd {
	namespace threading {
		template<class RType = double, class _Fn, class... _Args>
		RType executionTime(_Fn&& fn, _Args&&... args) {
			auto t1 = steady_clock::now();
			fn(args...);
			auto t2 = steady_clock::now();
			duration<RType> timespan = duration_cast<duration<RType> >(t2-t1);
			return (RType)timespan.count() * (RType)seconds::period::num/(RType)seconds::period::den;
		};

		// use multiple threads (up to max_threads or hardware_concurrency(), whichever is lower) to apply an operation
		// to each element of a vector. the expression being run will accept two parameters:
		//  - the element of the array
		//  - the number of the thread (0-indexed)
		// it will return the new value to be stored in that location in the vector.
		template<typename iType>
		void parallel_foreach(std::vector<iType> &v, std::size_t max_threads, iType (*op)(iType, std::size_t)) {
			if (v.empty()) return; // if the user tries to perform the operation on an empty vector, return

			// threadcount
			std::size_t tcount;

			// check if the user has put in more threads than they can handle, and if so, limit to hardware max.
			if (max_threads > std::thread::hardware_concurrency()) max_threads = std::thread::hardware_concurrency();

			// if the thread max is > than the length of the vector (in which case this is FAR less efficient than using one thread),
			// use only the length worth of threads
			if (max_threads > v.size()) tcount = v.size();
			else if (max_threads <= v.size()) tcount = max_threads; // this is not exact, use mod later to fix this

			std::vector<std::thread> threads(tcount);
			std::size_t iterations_per_thread = v.size()/tcount;
			
			for (std::size_t t = 0; t < tcount; t++) { 
				std::size_t f = t * iterations_per_thread; // index of first work item for this thread
				std::size_t e = f + iterations_per_thread - 1; // index of last work item for this thread
				
				if (t == tcount - 1)
					e += v.size() % tcount; // account for inaccuracies in division, if any

				threads[t] = std::thread([=, &v, &op] {
					for (std::size_t i = f; i <= e; i++) {
						v[i] = op(v[i], t);
					}
				});
			}

			for (std::thread &t : threads) {
				t.join();
			}
		};
	};
};

#endif
