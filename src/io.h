#ifndef WRESTD_IO_H
#define WRESTD_IO_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdio>

// to get properties of the terminal on BSD, etc.
#ifndef _WIN32
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#endif

// this is here because on VS2010 I have to change how this works to make it work properly
#define TO_STRING(i) (to_string(i))

// windows defined max, and I want to use a different one later on, meaning I have to undef this one
#if defined(_WIN32) && defined(max)
#undef max
#endif

#ifdef _WIN32
#define ISWINDOWS 1
#else
#define ISWINDOWS 0
#endif

#include <string>

// the following color code arrays are in the order of color_t color codes for reasy switching: color_t::black = 0, so nixcolorcodes[0] = 30, aka black
// foreground color codes for ANSI escapes
const int nixcolorcodes[16] = {30, 34, 32, 36, 31, 35, 33, 37, 90, 94, 92, 96, 91, 95, 93, 97};
// background color codes for ANSI escapes
const int nixbgcolorcodes[16] = {40, 44, 42, 46, 41, 45, 43, 47, 100, 104, 102, 106, 101, 105, 103, 107};

namespace wrestd {
	// A collection of things that help to deal with console/file IO.
	namespace io {
		// Contains various color options.
		enum color_t {
			BLACK = 0,
			DARKBLUE = 1,
			DARKGREEN = 2,
			DARKCYAN = 3,
			DARKRED = 4,
			DARKMAGENTA = 5,
			DARKYELLOW = 6,
			DARKWHITE = 7,
			DARKGREY = 8,
			BLUE = 9,
			GREEN = 10,
			CYAN = 11,
			RED = 12,
			MAGENTA = 13,
			YELLOW = 14,
			WHITE = 15,
			DEFAULT = WHITE,
			NOBG = 49,
			NOFG = 39
		};

		// Contains various options for formatting.
		enum format_t {
			NORMAL = 22,
			BOLD = 1,
			ITALIC = 3,
			FAINT = 2,
			UNDERLINE = 4,
			BLINK = 5,
			INVERTED = 7,
			RESET = 0
		};

		// Print a string in the given colors, foreground and background.
		void printc(std::string, color_t, color_t = NOBG);

		// Print a line (including newline character) in the given colors.
		void printlc(std::string, color_t, color_t = NOBG);

		// Clear the console.
		void clear();

		// Wait for the user to press a key.
		void wait(color_t = DEFAULT, color_t = NOBG);

		// Print a given string and wait for the user to press a key.
		void wait(std::string, color_t = DEFAULT, color_t = NOBG);

		// Set the colors of the console.
		void setColor(color_t, color_t = NOBG);

		// Determine whether or not a file exists.
		bool fileExists(char[]);

		// Get the height of the term (non-windows only).
		int termHeight();

		// Get the width of the term (non-windows only).
		int termWidth();

		// Set the format of the terminal.
		void setFormat(format_t);
	};
};

using namespace wrestd::io;

int getFGColor(int color)
{
	if (color > 15) return -1;

	if (color == DEFAULT)
		return NOFG;
	else
		return nixcolorcodes[color];
}

int getBGColor(int color)
{
	if (color > 15) return -1;

	if (color == DEFAULT)
		return NOBG;
	else
		return nixbgcolorcodes[color];
}

/* Set color of console text. Can specify background color if the system supports it. 
 *
 * FOR BEST RESULTS ON NON-WINDOWS:
 * DO NOT USE THIS FOR BACKGROUND COLOR
 * INSTEAD, SPECIFY ONE FOR PRINTLC OR PRINTC
 * */
void wrestd::io::setColor(color_t colorCode, color_t bgColorCode)
{
#ifdef _WIN32
	// this will let me access the console
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// this will only work on windows
	// if there is no bgColorCode specified, just do this
	if (bgColorCode == NOBG)
		SetConsoleTextAttribute(console, colorCode);
	else
	{
		WORD color = ((bgColorCode & 0x0F) << 4) + (colorCode & 0x0F);
		SetConsoleTextAttribute(console, color);
	}
#else
	// here I will use the nixcolors above
	int fgcolor = getFGColor(colorCode);
	int bgcolor = getBGColor(bgColorCode);
	std::printf("\033[%d;%dm", fgcolor, bgcolor);
#endif
}

/* Set the format of the text to the specified format_t.
 * Non-Windows only ATM. */
void wrestd::io::setFormat(format_t fmt)
{
#ifndef _WIN32
	std::printf("\033[%dm", fmt);
#endif
}

/* Clear the console. */
void wrestd::io::clear()
{
#ifdef _WIN32
	COORD topLeft = {0, 0};
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
#else
	// this is the non-windows way of doing this
	// J clears the display, 2 means to clear the whole thing, and then cursor gets put at the top left
	std::printf("\33c\033[2J");
#endif
}

/* Print a line in a certain color. 
 * Optionally, specify a background color for systems that support it. */
void wrestd::io::printlc(std::string line, color_t color, color_t bgColorCode)
{
#ifdef _WIN32
	setColor(color, bgColorCode);
	std::cout << line << endl;
	setColor(DEFAULT, DEFAULT);
#else
	std::printf("\033[%d;%dm%s\033[m\n", getFGColor(color), getBGColor(bgColorCode), line.c_str());
#endif
}

/* Print in a certain color, but no newline.
 * Optionally, specify a background color for systems that support it. */
void wrestd::io::printc(std::string text, color_t color, color_t bgColorCode)
{
#ifdef _WIN32
	setColor(color, bgColorCode);
	std::cout << text;
	setColor(DEFAULT, DEFAULT);
#else
	std::printf("\033[%d;%dm%s\033[m", getFGColor(color), getBGColor(bgColorCode), text.c_str());
#endif
}

/* Wait for user to press enter, optionally printing it in a specific color. 
 * Also optionally add a background color shown on systems which support it. */
void wrestd::io::wait(color_t messagecolor, color_t bgColor)
{
#ifdef _WIN32
	setColor(messagecolor, bgColor);
	std::cout << "\nPress ENTER to continue...";
#else
	std::printf("\n\033[%d;%dmPress ENTER to continue...\033[m", getFGColor(messagecolor), getBGColor(bgColor));
#endif
	// this is why i had to undef max, because windows defines it in some header file somewhere
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#ifdef _WIN32
	setColor(DEFAULT, DEFAULT);
#endif
}

/* Wait for user to press enter, display custom message, optionally specifying a color for the message. 
 * Optionally specify background color for supported systems. */
void wrestd::io::wait(std::string message, color_t messagecolor, color_t bgColorCode)
{
#ifdef _WIN32
	setColor(messagecolor, bgColorCode);
	std::cout << "\n"
		 << message;
#else
	std::printf("\n\033[%d;%dm%s\033[m", getFGColor(messagecolor), getBGColor(bgColorCode), message.c_str());
#endif
	// this is why i had to undef max, because windows defines it in some header file somewhere
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#ifdef _WIN32
	setColor(DEFAULT, DEFAULT);
#endif
}

/* Return true or false based on the existance of a file. */
bool wrestd::io::fileExists(char filename[])
{
	if (std::ifstream(filename))
		return true;

	std::ofstream file(filename);
	if (!file)
	{
		file.close();
		return false;
	}

	return false; // just in case both of the above fail to work. assume no file.
}

/* Retrieve the width of the terminal window in columns.
 * Returns -1 if unable to retrieve. */
int wrestd::io::termWidth()
{
#ifndef _WIN32
	struct winsize ws;
	int fd;

	// open terminal
	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
		return -1;

	// get the size
	if (ioctl(fd, TIOCGWINSZ, &ws) < 0)
		return -1;

	// otherwise return the width
	return ws.ws_col;
#endif
}

/* Retrieve the height of the terminal window in rows.
 * Returns -1 if error. */
int wrestd::io::termHeight()
{
#ifndef _WIN32
	struct winsize ws;
	int fd;

	// open terminal
	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
		return -1;

	// get size
	if (ioctl(fd, TIOCGWINSZ, &ws) < 0)
		return -1;

	// return height
	return ws.ws_row;
#endif
}

#endif
