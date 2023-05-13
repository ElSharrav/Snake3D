#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <fstream>
#include <string>
#include <utility>
#include <vector>

class HighScores
{
	std::vector<std::pair<int,std::string>> highscores;
	std::vector<std::string> highscoresText;

	void updateHighscoresTexts();

	std::string filePath;

	std::fstream file;
public:
	HighScores(std::string filePath);

	void loadFromFile();
	void saveToFile();
	// returns position of new score, -1 if score is too weak 
	int insertNewScore( int score, std::string playerName);
	void editPlayerName( std::string newPlayerName, int position); 

	const std::string& getHighscoresText(int position);
};

#endif