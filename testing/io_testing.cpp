#include <iostream>
#include <cstdio>
#include <wreio.h>

using namespace wrestd;

int main(void) {
	printf("Term Height: %d\nTerm Width: %d\n", io::termHeight(), io::termWidth());
	io::printlc("This is green on black?", GREEN, BLACK);
	io::wait("Press a key to clear the console.");
	io::clear();
	std::cout << "Cleared console.\n";
	return 0;
}