#include <iostream>
#include <string>
#include <wrestd/io.h>

using namespace wrestd::io;

int main(void) {
	//clear();
	printlc("This is GREEN", GREEN);
	printlc("This is DARKGREEN", DARKGREEN);
	printlc("This is RED", RED);
	printlc("This is DARKRED", DARKRED);
	printlc("This is GROSS", RED, GREEN);
	printlc("This is BLUE", BLUE);
	printlc("This is DARKBLUE", DARKBLUE);
	std::cout << "\033[39;49m";

	setFormat(BOLD);
	std::cout << "BOLD\n";
	setFormat(UNDERLINE);
	std::cout << "UNDERLINE\n";
	setFormat(RESET);
	
	printlc("WOW THIS IS COOL", WHITE, BLACK);


	return 0;
}
