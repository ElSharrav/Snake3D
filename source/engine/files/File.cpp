#include "File.h"

#include <fstream>

using namespace std;

File::File(const string& filename)
{
	this->fileName = filename;
	open( ios::in | ios::out);
}

std::string File::getLine()
{
	string line;
	getline(fs, line);
	return line;
}

void File::open(ios_base::openmode mode )
{
	fs.open(this->fileName, mode);
}

void File::close()
{
	fs.close();
}

void File::writeLine(const std::string& line)
{
	fs << line << std::endl;
}

void File::write(const std::string& text)
{
	fs << text;
}

bool File::isEOF() const
{
	return fs.eof();
}