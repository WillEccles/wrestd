#include <iostream>
#include "wreutil.h"
#include <cstdio>

using namespace wrestd::util;

int main(void) {
	int a = 5;
	int b = 10;
	int c = 0;

	std::printf("Before swap:\na: %d\nb: %d\n", a, b);
	in_place_swap(a, b);
	std::printf("After swap:\na: %d\nb: %d\n", a, b);

	a = 5555;
	b = 124;
	c = -5;

	std::printf("Before clamp (0-255):\na: %d\nb: %d\nc: %d\n", a, b, c);
	a = clamp(a, 0, 255);
	b = clamp(b, 0, 255);
	c = clamp(c, 0, 255);
	std::printf("After clamp (0-255):\na: %d\nb: %d\nc: %d\n", a, b, c);

	return 0;
}