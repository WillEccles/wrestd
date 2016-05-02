#include <thread>
#include <ctime>
#include "wrestd.h"

using namespace wrestd::threading;
using namespace std;

/* Ascertain the time it takes to run function 'fn', optionally with arguments. */
template<class _Fn,
	class... _Args,
	class = typename enable_if<
	!is_same<typename decay<_Fn>::type, thread>::value>::type>
clock_t wrestd::threading::timeToDo(_Fn&& fn, _Args&&... args) {
	clock_t start = clock();
	fn(args...);
	return clock() - start;
}