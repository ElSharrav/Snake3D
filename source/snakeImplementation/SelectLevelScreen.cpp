#include "SelectLevelScreen.h"

#include "Game.h"
#include "GameMenu.h"
#include "GameManager.h"

#define PATH_TO_MAPS "resources/maps/"

SelectLevelScreen::SelectLevelScreen(GameMenu* menu, std::string levelsListPath): OptionsScreen(menu)
{
	mapNames.loadNames(levelsListPath);

	options.push_back(MenuOption());

	options.at(0).setLabel(mapNames.names.at(0), *font);

	options.at(0).setcenterPosition(glm::vec2(960, 540));
}

void SelectLevelScreen::render()
{
	for (int i = 0; i < options.size(); i++)
	{
		options.at(i).draw(*font, *textShader);
	}
}

void SelectLevelScreen::update(float deltaTime)
{

}


void SelectLevelScreen::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
	{
		if (!menu->getoptionsScreen().areSoundsMuted()) {
			menu->getoptionsScreen().playClick();
		}
	//	chooseSelectedOption();
	//	//	gameManager->setstate(GameState::GAME);
//	menu->getgameManager()->getgame()->getboard().loadLevel(mapNames.names.at(optionFocused));
		std::string fullPathToMap = PATH_TO_MAPS;
		fullPathToMap.append(mapNames.names.at(optionFocused));
		menu->getgameManager()->getgame()->resetGame(fullPathToMap);
//		menu->getgameManager()->setstate(GameState::GAME);
		menu->getgameManager()->switchToGame();
	}
	else if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_RELEASE)
	{
		if (!menu->getoptionsScreen().areSoundsMuted()) {
			menu->getoptionsScreen().playSwitch();
		}

		optionFocused += 1;

		if (optionFocused >= mapNames.names.size())
		{
			optionFocused = 0;
		}

		options.at(0).setLabel(mapNames.names.at(optionFocused), *font);
	}
	else if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_RELEASE)
	{
		if (!menu->getoptionsScreen().areSoundsMuted()) {
			menu->getoptionsScreen().playSwitch();
		}

		optionFocused -= 1;

		if (optionFocused < 0)
		{
			optionFocused = (mapNames.names.size() - 1);
		}
		options.at(0).setLabel(mapNames.names.at(optionFocused), *font);

	}
	else if ((key == GLFW_KEY_ESCAPE) && action == GLFW_RELEASE)
	 {
		if (!menu->getoptionsScreen().areSoundsMuted()) {
			menu->getoptionsScreen().playSwitch();
		}
		 menu->setmenuOptionSelected(GameState::MENU);
	 }
}

void SelectLevelScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
		if (!menu->getoptionsScreen().areSoundsMuted()) {
			menu->getoptionsScreen().playSwitch();
		}
		std::string fullPathToMap = PATH_TO_MAPS;
		fullPathToMap.append(mapNames.names.at(optionFocused));
		menu->getgameManager()->getgame()->resetGame(fullPathToMap);
		//		menu->getgameManager()->setstate(GameState::GAME);
		menu->getgameManager()->switchToGame();

	}
}

void SelectLevelScreen::enterScreen(std::string levelsListPath)
{
	mapNames.loadNames(levelsListPath);
	options.at(0).setLabel(mapNames.names.at(0), *font);
}
