#include <iostream>
#include "wreutil.h"
#include <cstdio>

using namespace wrestd::util;

int main(void) {
	int a = 5;
	int b = 10;

	std::printf("Before swap:\na: %d\nb: %d\n", a, b);
	in_place_swap(a, b);
	std::printf("After swap:\na: %d\nb: %d\n", a, b);

	return 0;
}