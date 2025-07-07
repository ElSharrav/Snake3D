#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <string>
#include <utility>
#include <vector>

class StringOperations
{
public:
	static std::vector< std::string> split(const std::string& text, const char& separator);

	template<typename T>
	std::string convertToString(T toConvert)
	{
		std::stringstream ss;
		ss << toConvert;
		return ss.str();
	}

};

#endif