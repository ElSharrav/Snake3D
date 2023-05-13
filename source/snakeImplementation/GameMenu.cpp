#include "GameMenu.h"

#include "Game.h"
#include "GameManager.h"

#include "../engine/resources/ResourceManager.h"
#include "../engine/resources/Sounds.h"

#include "MapEditor.h"

#include "../engine/engine.h"

#define HIGHSCORES_PATH "resources/data/best.hs"
#define LEVELS_NAMES_PATH "resources/maps/maps.txt"

#define SELECTED_OPTION_COLOR glm::vec3(0.47f, 0.0f, 0.0f)
#define UNSELECTED_OPTION_COLOR glm::vec3(0.0f, 0.0f, 0.0f)

GameMenu::GameMenu(GameManager* gameManager,Engine* engine) : gameManager(gameManager), engine(engine), highscores(HIGHSCORES_PATH), highscoresScreen(this), optionsScreen(this), selectLevelScreen(this, LEVELS_NAMES_PATH)
{
	menuOptionSelected = GameState::MENU;
//	engine->compileAndLinkShader(&textShader, "resources/shaders/text/textShader.vs", "resources/shaders/text/textShader.fs");
	textShader = ResourceManager::getShader(Shaders::TEXT_SHADER);

	projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	
	font = ResourceManager::getFont(Fonts::MAIN_FONT);

	initializeHighscores();
//	initializeSelectLevelNames();

	optionFocused = 0;

	textShader->use();
	textShader->setMatrix4("projection", projection);

	options.push_back(MenuOption( ));
	options.push_back(MenuOption( ));
	options.push_back(MenuOption( ));
	options.push_back(MenuOption( ));
	options.push_back(MenuOption( ));

	options.at(0).setLabel("Play", *font);
	options.at(1).setLabel("Options", *font);
	options.at(2).setLabel("HighScores", *font);
	options.at(3).setLabel("Map Editor", *font);
	options.at(4).setLabel("Exit", *font);

	options.at(0).setcenterPosition( glm::vec2( 960 , 950 ) );
	options.at(1).setcenterPosition(glm::vec2(960 , 750));
	options.at(2).setcenterPosition(glm::vec2(960 , 550));
	options.at(3).setcenterPosition(glm::vec2(960, 350));
	options.at(4).setcenterPosition(glm::vec2(960, 150));

	options.at(0).setcolor(SELECTED_OPTION_COLOR);

	initializeMenuMusic();
	if (!optionsScreen.areSoundsMuted()) {
		playMenuMusic();
	}

}

void GameMenu::render()
{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glClearColor(0.11, 0.173, 0.329,1.0); // blueish
	glClearColor(0.161, 0.271, 0.09,1.0); // greyish
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	textShader->use();
	textShader->setMatrix4("projection", projection);

	switch (menuOptionSelected)
	{
	case MENU:
	{
		for (int i = 0; i < options.size(); i++)
		{
			options.at(i).draw(*font, *textShader);
		}
		break;
	}
	case SELECTLEVEL:
	{
		selectLevelScreen.render();
		break;
	}
	case OPTIONS:
	{
		optionsScreen.render();
		break;
	}
	case HIGHSCORES:
	{
		highscoresScreen.render();
		break;
	}
	case GAME:
		break;
	default:
		break;
	}
}
void GameMenu::update(float deltaTime)
{
	switch (menuOptionSelected)
	{
	case MENU:
		options.at(optionFocused).updateScale(deltaTime);
		break;
	case OPTIONS:
		optionsScreen.update(deltaTime);
		break;
	case HIGHSCORES:
		break;
	case GAME:
		break;
	default:
		break;
	}

}

void GameMenu::initializeHighscores()
{
	highscores.loadFromFile();
}

void GameMenu::initializeSelectLevelNames()
{
	selectLevelScreen.mapNames.loadNames(LEVELS_NAMES_PATH);
}

void GameMenu::initializeMenuMusic()
{
	menuMusic = Sounds::playSound("resources/sounds/luminousfridge__menu_track.mp3", true, true);
}

void GameMenu::playClick()
{
	Sounds::playSound("resources/sounds/click.mp3");
}

void GameMenu::playSwitch()
{
	Sounds::playSound("resources/sounds/change.mp3");
}

void GameMenu::chooseSelectedOption()
{
	switch (optionFocused)
	{
	case 0:
	{
		if (gameManager->getgame()->getdied())
		{
			selectLevelScreen.enterScreen(LEVELS_NAMES_PATH);
			menuOptionSelected = GameState::SELECTLEVEL;
//			gameManager->getgame()->resetGame();
		}
		else
		{
			gameManager->switchToGame();
		}

		break;
	}
	case 1:
	{
		menuOptionSelected = GameState::OPTIONS;
		break;
	}
	case 2:
	{
		menuOptionSelected = GameState::HIGHSCORES;
		break;
	}
	case 3:
	{
		gameManager->setstate(GameState::MAPEDITOR);
		gameManager->getmapEditor()->enterMapEditor();
		break;
	}
	case 4:
	{
		engine->requestEngineClose();
		break;
	}
	default:
		break;
	}
}

void GameMenu::playMenuMusic()
{
	menuMusic->setPlayPosition(0);
	menuMusic->setIsPaused(false);
}

void GameMenu::stopMenuMusic()
{
	menuMusic->setIsPaused(true);
}

void GameMenu::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (menuOptionSelected == GameState::MENU)
	{
		if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
		{
			if (!optionsScreen.areSoundsMuted()) {
				playClick();
			}
			chooseSelectedOption();
		}
	}
	else if (menuOptionSelected == GameState::HIGHSCORES)
	{
		highscoresScreen.mouse_button_callback(window, button, action, mods);
	}
	else if (menuOptionSelected == GameState::OPTIONS)
	{
		optionsScreen.mouse_button_callback(window, button, action, mods);
	}
	else if (menuOptionSelected == GameState::SELECTLEVEL)
	{
		selectLevelScreen.mouse_button_callback(window, button, action, mods);
	}
}

void GameMenu::mouseMovedEvent(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{

}
void GameMenu::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (menuOptionSelected == GameState::MENU)
	{

		if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		{
			if (!optionsScreen.areSoundsMuted()) {
				playClick();
			}

			chooseSelectedOption();
			//	gameManager->setstate(GameState::GAME);
		}
		else if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_RELEASE)
		{
			if (!optionsScreen.areSoundsMuted()) {
				playSwitch();
			}
			options.at(optionFocused).resetScale();
			options.at(optionFocused).setcolor( UNSELECTED_OPTION_COLOR );

			optionFocused += 1;

			if (optionFocused >= options.size())
			{
				optionFocused = 0;
			}
			options.at(optionFocused).setcolor(SELECTED_OPTION_COLOR);
		}
		else if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_RELEASE)
		{
			if (!optionsScreen.areSoundsMuted()) {
				playSwitch();
			}
			options.at(optionFocused).resetScale();
			options.at(optionFocused).setcolor(UNSELECTED_OPTION_COLOR);

			optionFocused -= 1;

			if (optionFocused < 0)
			{
				optionFocused = (options.size() - 1);
			}
			options.at(optionFocused).setcolor(SELECTED_OPTION_COLOR);
		}
	}
	else if(menuOptionSelected == GameState::HIGHSCORES)
	{
		highscoresScreen.keyEvent(window, key, scancode, action, mods);
	}
	else if (menuOptionSelected == GameState::OPTIONS)
	{
		optionsScreen.keyEvent(window, key, scancode, action, mods);
	}
	else if (menuOptionSelected == GameState::SELECTLEVEL)
	{
		selectLevelScreen.keyEvent(window, key, scancode, action, mods);
	}
}


void GameMenu::scrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{

}
void GameMenu::setPostProcessEffect(POST_PROCESSING_EFFECT effect)
{

}