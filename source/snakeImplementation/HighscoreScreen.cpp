#include "HighscoreScreen.h"

#include "GameMenu.h"
#include "GameManager.h"

#define HIGHSCORE_TEXT_COLOR glm::vec3( 0.0f, 0.0f, 0.0f )
#define HIGHSCORE_DIFFERENT_TEXT_COLOR glm::vec3( 1.0f, 0.0f, 0.0f )

bool HighscoreScreen::isLetter(int code)
{
	return ((code>=65 && code <= 90) || (code >= 97 && code <= 122));
}

HighscoreScreen::HighscoreScreen(GameMenu* menu) : OptionsScreen(menu)
{
	for (size_t i = 0; i < 10; i++)
	{
		colors.push_back(HIGHSCORE_TEXT_COLOR);
	}
}

void HighscoreScreen::saveHighScore()
{
	enteringPlayerName = true;
}

void HighscoreScreen::setDifferentColor(int scoreWithDifferentColor)
{
	this->scoreWithDifferentColor = scoreWithDifferentColor;
	colors.at(scoreWithDifferentColor) = HIGHSCORE_DIFFERENT_TEXT_COLOR;
}

void HighscoreScreen::setPlayerScore(int score)
{
	this->playerScore = score;
}

void HighscoreScreen::setPlayerPosition(int position)
{
	this->playerPosition = position;
}

void HighscoreScreen::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (enteringPlayerName)
	{
		if (isLetter(key) && action == GLFW_RELEASE)
		{
			playerName.push_back(key);
			menu->gethighscores().editPlayerName(playerName, playerPosition);
		}
		else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE)
		{
			if (playerName.size() > 0) {
				playerName.pop_back();
				menu->gethighscores().editPlayerName(playerName, playerPosition);
			}
		}
		else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		{
			menu->gethighscores().editPlayerName(playerName, playerPosition);
			menu->gethighscores().saveToFile();
			enteringPlayerName = false;
			playerName = "player";
			playerPosition = 0;
			playerScore = 0;
		}
	}
	else
	{
		if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		{
			menu->setmenuOptionSelected(GameState::MENU);
			colors.at(scoreWithDifferentColor) = HIGHSCORE_TEXT_COLOR;
		}
	}
}

void HighscoreScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (enteringPlayerName) {
		if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
		{
			menu->gethighscores().editPlayerName(playerName, playerPosition);
			menu->gethighscores().saveToFile();
			enteringPlayerName = false;
			playerName = "player";
			playerPosition = 0;
			playerScore = 0;
		}
	}
	else
	{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
	{
		menu->setmenuOptionSelected(GameState::MENU);
		colors.at(scoreWithDifferentColor) = HIGHSCORE_TEXT_COLOR;
	}
	}
}

void HighscoreScreen::render()
{
	for (size_t i = 0; i < 10; i++)
	{
		font->RenderText(*textShader, menu->gethighscores().getHighscoresText(i), 750, 900 - i * 80, 1.0f, colors.at(i));
	}

	if (enteringPlayerName)
	{
		font->RenderText(*textShader, "Podaj swoje imie", 900, 1000, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	}
}

