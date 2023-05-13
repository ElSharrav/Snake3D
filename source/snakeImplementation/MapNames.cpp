#include "MapNames.h"

#include <fstream>
#include <iostream>

using namespace std;

void MapNames::loadNames(std::string filePath)
{
	fstream fileWithMapNames(filePath, ios::in);

	names.clear();

	while (!fileWithMapNames.eof())
	{
		string name;
		fileWithMapNames >> name;
		names.push_back(name);
		cout << name << "\n";
	}

	fileWithMapNames.close();
}

void MapNames::saveNames(std::string filePath)
{
	fstream fileWithMapNames(filePath, ios::out);

	for (size_t i = 0; i < names.size()-1; i++)
	{
		fileWithMapNames << names.at(i) << "\n";
	}
	fileWithMapNames << names.at(names.size() - 1);
	
	fileWithMapNames.close();
}

void MapNames::addName(std::string mapName)
{
	names.push_back(mapName);
}
