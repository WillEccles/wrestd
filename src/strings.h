#ifndef STRINGS_H
#define STRINGS_H

#include <string>

namespace wrestd {
	namespace strings {
		int substr_count(std::string, std::string, bool);
		std::string substr_replace(std::string&, std::string, std::string, bool, bool);
		std::string to_lower(std::string);
		std::string to_upper(std::string);
	};
};

#endif
