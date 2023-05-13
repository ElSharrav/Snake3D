#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <glm/vec3.hpp>

#include "../engine/primitives/cube.h"
#include "../engine/shaders/shaderProgram.h"

#define BOARD_SIDE_SIZEX 10
#define BOARD_SIDE_SIZEY 10
#define BOARD_SIDE_SIZEZ 10

#define FIELD_SIZE_X 1
#define FIELD_SIZE_Y 1
#define FIELD_SIZE_Z 1

#define FLOOR_FIELDS BOARD_SIDE_SIZEX*BOARD_SIDE_SIZEZ
#define BOARD_FIELDS BOARD_SIDE_SIZEX*BOARD_SIDE_SIZEY*BOARD_SIDE_SIZEZ

enum Field
{
	EMPTY = 0,
	SNAKE = 1,
	FOOD = 2,
	WALL = 3,
};

class Board
{
	std::vector<char> boardValues;
	glm::vec3 boardPositionInWorld;
	
public:
	Board();

	void drawWalls(Cube& cube, ShaderProgram& shader);

	Field getFieldState(int x, int y, int z) const;
	Field getFieldState(glm::vec3 pos) const;
	glm::vec3 calculateOffset(int x, int y, int z) const;

	void loadLevel(std::string filePath);
	void saveLevel(std::string filePath);

	void setFieldState(int x, int y, int z, Field state);
	void setFieldState(glm::ivec3 pos, Field state);
	void setBoardInWorldPosition(glm::vec3 boardPositionInWorld);
	glm::vec3 getBoardPositionInWorld();
};

#endif