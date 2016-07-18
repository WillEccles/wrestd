/*----------COPYRIGHT-------------------------
(c) Copyright Will Eccles, 2016
----------------------------------------------*/

/*----------LICENSE---------------------------
This software is licensed under the Apache license. See LICENSE file to learn more.
----------------------------------------------*/

/*----------DESCRIPTION-----------------------
This is a collection of my frequently used classes and methods.
----------------------------------------------*/

/* Common imports, or things required for the classes to work. */
#include <stdio.h>
#include <string>
#include <thread>
#include <time.h>

// used to detect things later on, IIRC. Just copied it from the old IOManager.h file, pretty sure it's used somewhere.
#ifdef _WIN32
#define ISWINDOWS 1
#else
#define ISWINDOWS 0
#endif

// My namespace, which contains helpful methods and such.
namespace wrestd {
	/* Methods that work with strings. */
	namespace strings {
		int substr_count(std::string, std::string, bool);
		std::string substr_replace(std::string&, std::string, std::string, bool, bool);
		std::string to_lower(std::string);
		std::string to_upper(std::string);
	}
	
	/* Handles IO functions, such as console printing, colors, waiting, etc. and file existance checks. */
	namespace io {
		enum color_t {
			BLACK = 0,
			DARKBLUE = 1,
			DARKGREEN = 2,
			DARKTEAL = 3,
			DARKRED = 4,
			DARKMAGENTA = 5,
			DARKYELLOW = 6,
			DARKWHITE = 7,
			DARKGREY = 8,
			BLUE = 9,
			GREEN = 10,
			TEAL = 11,
			RED = 12,
			MAGENTA = 13,
			YELLOW = 14,
			WHITE = 15,
			DEFAULT = WHITE
		};
		void printc(std::string, color_t);
		void printlc(std::string, color_t);
		void clear();
		void wait();
		void wait(std::string);
		void setColor(color_t);
		int DEFAULT;
		bool fileExists(char[]);
	};
	
	/* Handles threading-related functions, including execution times and such. 
	At this time, executionTime does not work.*/
	namespace threading {
		template<class _Fn, class... _Args, class RType> 
			RType executionTime(_Fn&& fn, _Args&&... args);
	};
}