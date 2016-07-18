#include <thread>
#include <time.h>
#include "wrestd.h"

using namespace wrestd::threading;

/* Ascertain the time it takes to run function 'fn' in seconds, optionally with arguments. Does not compile at this time. */
template<class _Fn,
	class... _Args,
	class RType = double>
RType wrestd::threading::executionTime(_Fn&& fn, _Args&&... args) {
	clock_t start = clock();
	fn(args...);
	// CLOCKS_PER_SEC = accuracy of clock(), i.e. 1/1000s on windows, 1/1000000s on Linux, etc.
	double difference = (double)(clock() - start) / (double) CLOCKS_PER_SEC;
	return clock() - start;
}