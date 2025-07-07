#ifndef MAPNAMES_H
#define MAPNAMES_H

#include <vector>
#include <string>

class MapNames
{

public:

	void loadNames(std::string filePath);
	void saveNames(std::string filePath);
	void addName(std::string mapName);

	std::vector<std::string> names;
};

#endif