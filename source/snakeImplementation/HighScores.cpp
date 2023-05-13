#include "HighScores.h"

#include <algorithm>
#include <string_view>

HighScores::HighScores(std::string filePath) : filePath(filePath)
{

}

void HighScores::loadFromFile()
{
	file.open(filePath, std::ios_base::in);

	int score;
	std::string playerName;

	for (size_t i = 0; i < 10; i++)
	{
		file >> score;
		file >> playerName;
		highscores.push_back(std::make_pair(score,playerName));
	}

	highscoresText.insert(highscoresText.begin(), 10, "1.     0");
	updateHighscoresTexts();

	file.close();
}

void HighScores::saveToFile()
{
	file.open(filePath, std::ios_base::out | std::ios_base::trunc);

	for (size_t i = 0; i < highscores.size(); i++)
	{
		file << highscores.at(i).first;
		file << " ";
		file << highscores.at(i).second;
		file << " ";
	}

	file.close();
}

int HighScores::insertNewScore(int score, std::string playerName)
{
	// if score is big enough to be on highscore
	for (int i = 0; i < 10; i++)
	{
		if (score > highscores.at(i).first)
		{
	/*		struct {
				bool operator()(const int& a, const int& b) const { return a > b; }
			} static customLess;*/
			struct {
				bool operator()(const std::pair<int, std::string>& a,const std::pair<int, std::string>& b) const { return a.first > b.first; }
			} static customLess;

			// overwrite worst score, and sort highscores
			highscores.at(9).first = score;
			highscores.at(9).second = playerName;
			std::stable_sort(highscores.begin(), highscores.end(), customLess);
			updateHighscoresTexts();

			return i;
		}
	}

	return -1;
}

void HighScores::editPlayerName(std::string newPlayerName, int position)
{
	highscores.at(position).second = newPlayerName;
	updateHighscoresTexts();
}

void HighScores::updateHighscoresTexts()
{
	for (size_t i = 0; i < highscoresText.size(); i++)
	{
		highscoresText.at(i) = (std::to_string(i+1) + ".  " + highscores.at(i).second + "   " + std::to_string(highscores.at(i).first));
	}
}

const std::string& HighScores::getHighscoresText(int position)
{
	return highscoresText.at(position);
}