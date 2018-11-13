#include <string>
#include <iostream>
#include "wrestrings.h"
#include <sstream>

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: [executable] [chars] [length]" << std::endl;
		return 1;
	}
	
	std::stringstream ss(argv[2]);
	std::size_t len;
	std::string chars = argv[1];

	if (chars.empty()) {
		std::cerr << "Usage: [executable] [chars] [length]" << std::endl;
		return 1;
	}

	if (!(ss >> len)) {
		std::cerr << "Usage: [executable] [chars] [length]" << std::endl;
		return 1;
	}

	std::cout << wrestd::strings::rand_str(chars, len) << std::endl;

	return 0;
}