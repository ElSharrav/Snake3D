#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class File
{
	std::string fileName;

public:
	File( const std::string& filename );

	void open(std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
	void close();

	std::string getLine();

	void writeLine(const std::string& line);
	void write(const std::string& text);

	bool isEOF()const;

private:
	std::fstream fs;
};

#endif