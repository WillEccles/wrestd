#ifndef IO_H
#define IO_H

#include <string>

namespace wrestd {
	namespace io {
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
		void printc(std::string, color_t, color_t = NOBG);
		void printlc(std::string, color_t, color_t = NOBG);
		void clear();
		void wait(color_t = DEFAULT, color_t = NOBG);
		void wait(std::string, color_t = DEFAULT, color_t = NOBG);
		void setColor(color_t, color_t = NOBG);
		bool fileExists(char[]);
		int termHeight();
		int termWidth();
		void setFormat(format_t);
	};
};

#endif
