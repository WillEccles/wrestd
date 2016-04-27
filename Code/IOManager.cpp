#include "IOManager.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <fstream>

// this is here because on VS2010 I have to change how this works to make it work properly
#define TO_STRING(i) (to_string(i))

// windows defined max, and I want to use a different one later on, meaning I have to undef this one
#ifdef _WIN32
#undef max
#endif

using namespace std;

int DEFAULT;

#ifdef _WIN32
// this will let me access the console
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

/* Set color of console text. */
void IOManager::setColor(int colorCode) {
#ifdef _WIN32
	// this will only work on windows
	SetConsoleTextAttribute(console, colorCode);
#endif
}

/* Clear the console. */
void IOManager::clear() {
#ifdef _WIN32
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
#else
	// this is the non-windows way of doing this
	// should work, though I have not yet had a chance to test this.
	cout << "\x1B[2J\x1B[H";
#endif
}

/* Print a ling in a certain color. */
void IOManager::printlc(string line, int color) {
	setColor(color);
	cout << line << endl;
	setColor(DEFAULT);
}

/* Print in a certain color, but no newline. */
void IOManager::printc(string text, int color) {
	setColor(color);
	cout << text;
}

/* Wait for user to press enter. */
void IOManager::wait() {
	setColor(DARKWHITE);
	cout << "\nPress ENTER to continue...";
	// this is why i had to undef max, because windows defines it in some header file somewhere
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	setColor(DEFAULT);
}

/* Wait for user to press enter, display custom message. */
void IOManager::wait(string message) {
	setColor(DARKWHITE);
	cout << "\n" << message;
	// this is why i had to undef max, because windows defines it in some header file somewhere
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	setColor(DEFAULT);
}

/* Return true or false based on the existance of a file. */
bool IOManager::fileExists(char filename[]) {
	if (ifstream(filename))
		return true;
	
	ofstream file(filename);
	if (!file) {
		file.close();
		return false;
	}
}

IOManager::IOManager() {
	DEFAULT = WHITE;
}

IOManager::IOManager(int defaultColor) {
	DEFAULT = defaultColor;
}