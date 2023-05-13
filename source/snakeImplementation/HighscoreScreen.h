#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "../glfw/Glfw.h"
#include "Options/OptionsScreen.h"

#include <vector>
#include <glm/vec3.hpp>

class GameMenu;

class HighscoreScreen : public OptionsScreen 
{
	bool isLetter(int code);

	std::vector<glm::vec3> colors;

	bool enteringPlayerName = false;
	std::string playerName = "player";
	int playerScore = 0;
	int playerPosition = 0;
	int scoreWithDifferentColor;
public:
//	using OptionsScreen::OptionsScreen; 
	HighscoreScreen(GameMenu* menu);

	void saveHighScore();
	void setDifferentColor(int scoreWithDifferentColor);
	void setPlayerScore(int score);
	void setPlayerPosition(int position);

	virtual void render();

	virtual void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
};



#endif