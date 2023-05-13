#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "../../glfw/Glfw.h"

#include "../../engine/shaders/shaderProgram.h"
#include "../../engine/fonts/Fonts.h"

#include "MenuOption.h"

#include <vector>

class GameMenu;

class OptionsScreen
{
protected:
	int optionFocused;
	std::vector< MenuOption > options;

	GameMenu* menu;
	Font* font;
	ShaderProgram* textShader;

public:
	OptionsScreen(GameMenu* menu);

	virtual void render();
	virtual void update(float deltaTime);

	virtual void mouseMovedEvent(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset);
	virtual void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void scrollEvent(GLFWwindow* window, double xoffset, double yoffset);
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif