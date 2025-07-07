#include "StringOperations.h"

using namespace std;

std::vector< std::string>  StringOperations::split(const std::string& text, const char& separator)
{
	std::vector<std::string> parts;
	size_t startPos = 0;
	size_t endPos = 0;


	while ( (endPos = text.find(separator, startPos)) != string::npos )
	{
		parts.push_back( text.substr( startPos , endPos-startPos ) );
		startPos = endPos + 1;
	}

	parts.push_back(text.substr(startPos, endPos - startPos));

	return parts;
}