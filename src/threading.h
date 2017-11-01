#ifndef THREADING_H
#define THREADING_H

#include <chrono>

using namespace std::chrono;

namespace wrestd {
	namespace threading {
		template<class RType = double, class _Fn, class... _Args>
		RType executionTime(_Fn&& fn, _Args&&... args) {
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			fn(args...);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<RType> timespan = duration_cast<duration<RType> >(t2-t1);
			return (RType)timespan.count() * (RType)seconds::period::num/(RType)seconds::period::den;
		}
	};
};

#endif
