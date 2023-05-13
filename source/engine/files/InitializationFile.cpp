#include "InitializationFile.h"

#include "../string/StringOperations.h"


using namespace std;

void InitializationFile::populateValues()
{
	values.clear();	// in case values were populated before

	string line = getNonCommentLine();

	if (checkLineType(line) != InitializationFile::LINE_TYPE::SECTION)
	{
		// raise exception, first non comment line must be section
	}

	lastLine = line;

	while ( ! isEOF() )
	{
		addSectionToValues();
	}

}

std::string InitializationFile::getNonCommentLine()
{
	string line;

	while ( true )
	{
		line = getLine();

		if (checkLineType(line) != InitializationFile::LINE_TYPE::COMMENT)
		{
			break;
		}
	}

	return line;
}

std::string InitializationFile::getSectionName(const std::string& line)
{
	if( (line.at(0) != SECTION_START_SIGN) || (line.at( line.size() - 1 ) != SECTION_END_SIGN) ) 
	{ 
		// throw exception
	}
	return line.substr(1, line.size() - 2);
}

std::pair<std::string, std::string> InitializationFile::getKeyValuePair(const std::string& line)
{
//	return StringOperations::split(line, KEY_VALUE_SEPARATOR);
	vector<string> keyValue = StringOperations::split(line, KEY_VALUE_SEPARATOR);
	return make_pair( keyValue.at(0) , keyValue.at(1));
}

void InitializationFile::addSectionToValues(  )
{
	string line;
	string sectionName;

	vector< pair<string, string> > values;
	pair<string, string> keyValue;

	sectionName = getSectionName(getLastLine());

	while (true)	// until we will met end of the section
	{
	line = getNonCommentLine();

	if (checkLineType(line) == InitializationFile::LINE_TYPE::SECTION  )
	{
		this->lastLine = line;
		break;
	}

	keyValue = getKeyValuePair(line);

	values.push_back(make_pair(keyValue.first, keyValue.second));


	if (isEOF())
	{
		break;
	}


	}

	this->values.push_back(values);
	sectionNames.push_back(sectionName);

}

void InitializationFile::saveSectionToFile( int sectionNumber )
{
	string line;
	line = (SECTION_START_SIGN + sectionNames.at(sectionNumber) + SECTION_END_SIGN);
	writeLine( "" );
	write( line );

	vector<std::pair<std::string, std::string>>* section = &this->values.at(sectionNumber);

	for (int i = 0; i < section->size() ; i++)
	{
		line = section->at(i).first + KEY_VALUE_SEPARATOR + section->at(i).second;
		writeLine( "");
		write( line );
	}
}

void InitializationFile::saveValuesToFile()
{
	close();
	open( ios_base::out | ios_base::trunc );

	write(";file with game options");	// we are writing comment on the start of the file to overcome bug with new lines

	for (int i = 0; i < sectionNames.size() ; i++)
	{
		saveSectionToFile(i);
	}
}

InitializationFile::LINE_TYPE InitializationFile::checkLineType(const std::string& line)
{
	if (line.at(0) == SECTION_START_SIGN) { return InitializationFile::LINE_TYPE::SECTION; }
	else if (line.at(0) == COMMENT_START_SIGN) { return InitializationFile::LINE_TYPE::COMMENT; }
	else return InitializationFile::LINE_TYPE::KEY_VALUE;
}

const std::string& InitializationFile::getLastLine()
{
	return this->lastLine;
}

std::vector < std::pair<std::string, std::string>> InitializationFile::getSectionKeyValues(const std::string & sectionName)const
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			return this->values.at(i);
		}
	}

	return std::vector < std::pair<std::string, std::string>>() ;
}

std::string InitializationFile::getValue(const std::string& sectionName, const std::string& keyValue)const
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					return j->second;
				}
			}
			
			// key didn't found in section, we can stop searching
			break;
		}
	}

	throw std::invalid_argument("Key: " + keyValue + " not found in section: " + sectionName);
}

float InitializationFile::getFloat(const std::string& sectionName, const std::string& keyValue)const
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					return atof(j->second.c_str());
				}
			}

			// key didn't found in section, we can stop searching
			break;
		}
	}

	throw std::invalid_argument( "Key: " + keyValue + " not found in section: " + sectionName);
}

int InitializationFile::getInt(const std::string& sectionName, const std::string& keyValue)const
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					return atoi(j->second.c_str());
				}
			}

			// key didn't found in section, we can stop searching
			break;
		}
	}

	throw std::invalid_argument("Key: " + keyValue + " not found in section: " + sectionName);
}

void InitializationFile::setValue(const std::string& sectionName, const std::string& keyValue, const std::string& value)
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					j->second = value;
				}
			}

		}
	}
}

void InitializationFile::setValue(const std::string& sectionName, const std::string& keyValue, int value)
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					j->second = std::to_string( value );
				}
			}

		}
	}
}

void InitializationFile::setValue(const std::string& sectionName, const std::string& keyValue, float value)
{
	for (int i = 0; i < sectionNames.size(); i++)
	{
		if (sectionNames.at(i) == sectionName)
		{
			auto firstIt = this->values.at(i).begin();
			for (auto j = firstIt; j < this->values.at(i).end(); j++)
			{
				if (j->first == keyValue)
				{
					j->second = std::to_string(value);
				}
			}

		}
	}
}