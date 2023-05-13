#ifndef INITIALIZATIONFILE_H
#define INITIALIZATIONFILE_H

#include "File.h"
#include <vector>
#include <utility>
#include <stdexcept>

#define SECTION_START_SIGN '['
#define SECTION_END_SIGN ']'
#define COMMENT_START_SIGN ';'
#define KEY_VALUE_SEPARATOR '='

class FileCorruptedException : public std::logic_error
{
	using std::logic_error::logic_error;
};


class InitializationFile : private File
{
	using File::File;

	enum LINE_TYPE
	{
		SECTION,
		KEY_VALUE,
		COMMENT,
	};

	std::string lastLine;

	std::vector< std::vector< std::pair<std::string, std::string> > > values;
	std::vector< std::string > sectionNames;

	std::string getNonCommentLine();
	LINE_TYPE checkLineType( const std::string& line ); 
	std::string getSectionName(const std::string& line);	// line should starts with SECTION_START_SIGN and end with SECTION_END_SIGN
	std::pair<std::string, std::string> getKeyValuePair(const std::string& line);
	const std::string& getLastLine();

	void addSectionToValues();

	void saveSectionToFile(int sectionNumber);

public:
	void populateValues();
	void saveValuesToFile();

	std::vector < std::pair<std::string, std::string>> getSectionKeyValues(const std::string& sectionName)const;
	std::string getValue(const std::string& sectionName, const std::string& keyValue)const;
	float getFloat(const std::string& sectionName, const std::string& keyValue)const;
	int getInt(const std::string& sectionName, const std::string& keyValue)const;

	void setValue(const std::string& sectionName, const std::string& keyValue , const std::string& value);
	void setValue(const std::string& sectionName, const std::string& keyValue , int value);
	void setValue(const std::string& sectionName, const std::string& keyValue , float value);
};

#endif