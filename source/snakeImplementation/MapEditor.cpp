#include "MapEditor.h"

#include "../engine/camera/camera.h"
#include "../engine/engine.h"
#include "Game.h"
#include "GameManager.h"
#include "GameMenu.h"

#include "../engine/fonts/Fonts.h"

#define PATH_TO_MAPS "resources/maps/"

MapEditor::MapEditor(GameManager* gameManager) : gameManager(gameManager)
{
	wallSegment.setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	wallSelectedSegment.setColor(glm::vec3(0.0f, 0.3f, 1.0f));

	screenSize = gameManager->getgameMenu()->engine->getscreenSize();
}

bool MapEditor::isLetter(int code)
{
	return ((code >= 65 && code <= 90) || (code >= 97 && code <= 122));
}

glm::ivec2 MapEditor::screenCoordsToMapCoords(int x, int y, int screenX, int screenY)
{
	float xRatio = (float)x / screenX;
	float yRatio = (float)y / screenY;

	glm::ivec2 mapCoord = glm::vec2(xRatio * 10, yRatio * 10);

	return mapCoord;
}

void MapEditor::updateWallSelectedSegmentPosition(int x, int y, int screenWidth, int screenHeight)
{
	glm::vec2 mapCoordClicked = screenCoordsToMapCoords(x, y, screenWidth, screenHeight);
	glm::vec3 position = board.calculateOffset(mapCoordClicked.x, activeLayer, mapCoordClicked.y);
	wallSelectedSegment.setPosition(position);
}


void MapEditor::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	Game* game = gameManager->getgame();
	ShaderProgram& colorShader = game->getcolorShader();
	game->drawBorders(game->colorShader);
	if (mode == EditMode::Editing)
	{
		wallSelectedSegment.draw(colorShader);
	}

	board.drawWalls(wallSegment, gameManager->getgame()->colorShader);
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "c - switch mode", 20, 20, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "z - previous layer", 20, 60, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "a - next layer", 20, 100, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "s - save map", 20, 140, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "LPM - create obstacle", 20, 180, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "RPM - remove obstacle", 20, 220, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));

	if (enteringMapName)
	{
		gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, "Enter Map Name:", 20, 660, 1.0, glm::vec3(0.77f, 0.0f, 0.0f));
		gameManager->getgameMenu()->font->RenderText(*gameManager->getgame()->textShader, mapName, 400, 660, 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}
void MapEditor::update(float deltaTime)
{
	gameManager->getgame()->updateViewMatrixInShaders();
}

void MapEditor::enterMapEditor()
{
	if (mode == EditMode::Looking) {
		glfwSetInputMode(gameManager->getgameMenu()->engine->getwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if (mode == EditMode::Editing) {
		glfwSetInputMode(gameManager->getgameMenu()->engine->getwindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	gameManager->getgame()->cam = Camera();
	gameManager->getgame()->cam.setAngleY(90.0f);
	gameManager->getgame()->updateViewMatrixInShaders();
}

void MapEditor::mouseMovedEvent(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{
	mouseX = xpos;
	mouseY = ypos;

	if (mode == EditMode::Looking)
	{
		if (glm::abs(xoffset) > glm::abs(yoffset))	// did we moved mouse more in x axis that y axis
		{
			gameManager->getgame()->cam.addAngle(-xoffset);
		}
		else
		{
			gameManager->getgame()->cam.addAngleY(yoffset);
		}
	}
	else if (mode == EditMode::Editing)
	{
		updateWallSelectedSegmentPosition(mouseX, mouseY, screenSize.x, screenSize.y);
	}
}
void MapEditor::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (enteringMapName)
	{
		if (isLetter(key) && action == GLFW_RELEASE)
		{
			mapName.push_back(key);
//			menu->gethighscores().editPlayerName(playerName, playerPosition);
		}
		else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE)
		{
			if (mapName.size() > 0) {
				mapName.pop_back();
//				menu->gethighscores().editPlayerName(playerName, playerPosition);
			}
		}
		else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		{
			std::string fullMapPath = PATH_TO_MAPS;
			std::string MapFileName = mapName;
			MapFileName.append(".map");
			fullMapPath.append(MapFileName);

			board.saveLevel(fullMapPath);
			gameManager->getgameMenu()->getselectLevelScreen().mapNames.addName(MapFileName);
			gameManager->getgameMenu()->getselectLevelScreen().mapNames.saveNames("resources/maps/maps.txt");
;//			menu->gethighscores().editPlayerName(playerName, playerPosition);
//			menu->gethighscores().saveToFile();
			enteringMapName = false;
			mapName = "";
//			playerPosition = 0;
//			playerScore = 0;
		}
	}
	else
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		{
			glfwSetInputMode(gameManager->getgameMenu()->engine->getwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			gameManager->setstate(GameState::MENU);
		}
		else if (key == GLFW_KEY_C && action == GLFW_RELEASE)
		{
			if (mode == EditMode::Editing) {
				mode = EditMode::Looking;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else {
				//			enterMapEditor();
				mode = EditMode::Editing;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
		}
		else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			if (activeLayer < 9) {
				++activeLayer;
				updateWallSelectedSegmentPosition(mouseX, mouseY, screenSize.x, screenSize.y);
			}
		}
		else if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
		{
			if (activeLayer > 0) {
				--activeLayer;
				updateWallSelectedSegmentPosition(mouseX, mouseY, screenSize.x, screenSize.y);
			}
		}
		else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			enteringMapName = true;
//			board.saveLevel("resources/maps/mapEditor.map");
		}
	}
	
}
void MapEditor::scrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{

}
void MapEditor::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
	{
		glm::ivec2 mapCoord = screenCoordsToMapCoords(mouseX, mouseY, screenSize.x, screenSize.y);
		board.setFieldState(mapCoord.x, activeLayer, mapCoord.y, Field::WALL);
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
	{
		glm::ivec2 mapCoord = screenCoordsToMapCoords(mouseX, mouseY, screenSize.x, screenSize.y);
		board.setFieldState(mapCoord.x, activeLayer, mapCoord.y, Field::EMPTY);
	}
}