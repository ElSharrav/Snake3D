#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <glm/vec2.hpp>

#include "../glfw/Glfw.h"

#include "../engine/primitives/cube.h"
#include "board.h"

class GameManager;

enum class EditMode
{
	Editing,
	Looking,
};

class MapEditor
{
	glm::ivec2 screenCoordsToMapCoords(int x, int y, int screenX, int screenY);
	void updateWallSelectedSegmentPosition(int x, int y, int screenWidth, int screenHeight);
	
	GameManager* gameManager;

	Board board;

	EditMode mode = EditMode::Editing;
	bool enteringMapName = false;

	std::string mapName;

	int activeLayer = 0;
	Cube wallSegment = Cube(1,1,1);
	Cube wallSelectedSegment = Cube(1, 1, 1);

	glm::vec2 screenSize;
	double mouseX = 0, mouseY = 0;

	bool isLetter(int code);
public:
	MapEditor(GameManager* gameManager);

	void render();
	void update(float deltaTime);

	void enterMapEditor();

	void mouseMovedEvent(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset);
	void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	void scrollEvent(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif