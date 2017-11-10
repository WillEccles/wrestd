#include <iostream>
#include <string>
#include <wrestd/stack.h>

using namespace wrestd::collections;

int main(void) {
	stack<int> s(12);

	s.push(14);
	std::cout << s.pop() << '\n' << s.pop() << '\n';

	return 0;
}
