#include "OptionsScreen.h"

#include "../../engine/resources/ResourceManager.h"

OptionsScreen::OptionsScreen(GameMenu* menu) : menu(menu), optionFocused(0)
{
	textShader = ResourceManager::getShader(Shaders::TEXT_SHADER);
	font = ResourceManager::getFont(Fonts::MAIN_FONT);
}

void OptionsScreen::render()
{

}
void OptionsScreen::update(float deltaTime)
{

}

void OptionsScreen::mouseMovedEvent(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{

}
void OptionsScreen::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}
void OptionsScreen::scrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{

}
void OptionsScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}