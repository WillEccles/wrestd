#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <random>
#include <map>

namespace wrestd {
	// A collection of functions that help with string operations.
	namespace strings {
		// Count occurrences of a substring in a given string.
		int substr_count(std::string, std::string, bool);

		// Replace occurrences of a substring with a new string.
		std::string substr_replace(std::string&, std::string, std::string, bool, bool);

		// Lowercase a string.
		std::string to_lower(std::string);

		// Uppercase a string.
		std::string to_upper(std::string);

		// Generate a random string of a given length from a set of characters.
		std::string rand_str(std::string, std::size_t);

		// Return the phonetic alphabet representation of a character in a the NATO alphabet.
		std::string to_phonetic(char);

		// Return the phonetic version of the given string.
		std::string to_phonetic(std::string&);

		const static std::map<char, std::string> NATO_ALPHABET = { {'A', "Alfa"}, {'B', "Bravo"}, {'C', "Charlie"}, {'D', "Delta"}, {'E', "Echo"}, {'F', "Foxtrot"}, {'G', "Golf"}, {'H', "Hotel"}, {'I', "India"}, {'J', "Juliet"}, {'K', "Kilo"}, {'L', "Lima"}, {'M', "Mike"}, {'N', "November"}, {'O', "Oscar"}, {'P', "Papa"}, {'Q', "Quebec"}, {'R', "Romeo"}, {'S', "Sierra"}, {'T', "Tango"}, {'U', "Uniform"}, {'V', "Victor"}, {'W', "Whiskey"}, {'X', "X-ray"}, {'Y', "Yankee"}, {'Z', "Zulu"}, {'a', "Alfa"}, {'b', "Bravo"}, {'c', "Charlie"}, {'d', "Delta"}, {'e', "Echo"}, {'f', "Foxtrot"}, {'g', "Golf"}, {'h', "Hotel"}, {'i', "India"}, {'j', "Juliet"}, {'k', "Kilo"}, {'l', "Lima"}, {'m', "Mike"}, {'n', "November"}, {'o', "Oscar"}, {'p', "Papa"}, {'q', "Quebec"}, {'r', "Romeo"}, {'s', "Sierra"}, {'t', "Tango"}, {'u', "Uniform"}, {'v', "Victor"}, {'w', "Whiskey"}, {'x', "X-ray"}, {'y', "Yankee"}, {'z', "Zulu"}};
	};
};

/* Count occurrences of substring 'substr' in std::string 'str'. */
int wrestd::strings::substr_count(std::string str, std::string substr, bool overlap = true)
{
	if (str.find(substr) == str.npos)
		return 0;

	int index = 0;
	int count = 0;

	while (str.find(substr, index) != str.npos)
	{
		index = str.find(substr, index) + (overlap ? 1 : substr.length());
		count++;
	}

	return count;
}

/* Same as substr_replace, but acts directly on 'str'. */
void substr_replace_volatile(std::string &str, std::string substr, std::string replacement, bool overlap = false)
{
	if (str.find(substr) == str.npos)
		return;

	int index = 0;

	while (str.find(substr, index) != str.npos)
	{
		index = str.find(substr, index);
		str.erase(index, substr.length());
		str.insert(index, replacement);
		index += (overlap ? 1 : replacement.length());
	}
}

/* Replace all occurrences of substring 'substr' in std::string 'str'. */
std::string wrestd::strings::substr_replace(std::string &str, std::string substr, std::string replacement, bool overlap = false, bool replace = false)
{
	if (replace)
	{
		substr_replace_volatile(str, substr, replacement, overlap);
		return str;
	}

	std::string _str = str;

	if (_str.find(substr) == _str.npos)
		return _str;

	int index = 0;

	while (_str.find(substr, index) != _str.npos)
	{
		index = _str.find(substr, index);
		_str.erase(index, substr.length());
		_str.insert(index, replacement);
		index += (overlap ? 1 : replacement.length());
	}

	return _str;
}

/* Convert a std::string to all lowercase. (ASCII-only obviously) */
std::string wrestd::strings::to_lower(std::string str)
{
	std::string _str = str;

	for (int i = 0; i < _str.length(); i++)
		if (_str[i] >= 0x41 /*A*/ && _str[i] <= 0x5A /*Z*/)
			_str[i] = (char)(_str[i] + 0x20);

	return _str;
}

/* Convert a std::string to all uppercase. (ASCII-only obviously) */
std::string wrestd::strings::to_upper(std::string str)
{
	std::string _str = str;

	for (int i = 0; i < _str.length(); i++)
		if (_str[i] >= 0x61 /*a*/ && _str[i] <= 0x7A /*z*/)
			_str[i] = (char)(_str[i] - 0x20);

	return _str;
}

// Generate a string of a given length from a set of characters.
std::string wrestd::strings::rand_str(std::string chars, std::size_t length) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<std::size_t> dist(0, chars.length() - 1);

	std::string out(length, '\0');
	for (std::size_t i = 0; i < length; i++) {
		out[i] = chars[dist(gen)];
	}

	return out;
}

std::string wrestd::strings::to_phonetic(char letter) {
	if ((letter <= 'z' && letter >= 'a') || (letter <= 'Z' && letter >= 'A'))
		return wrestd::strings::NATO_ALPHABET.at(letter);
	else {
		std::string s = " ";
		s[0] = letter;
		return s;
	}
}

std::string wrestd::strings::to_phonetic(std::string &str) {
	std::string rval;
	for (std::size_t i = 0; i < str.length(); i++) {
		if ((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A')) {
			if (i > 0)
				rval += ' ';
			rval += wrestd::strings::to_phonetic(str[i]);
		} else if (str[i] != ' ') {
			rval += str[i];
		}
	}
	return rval;
}

#endif
