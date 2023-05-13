#include "board.h"

#include <iostream>
#include <fstream>

using namespace std;

Board::Board() : boardValues(BOARD_FIELDS , 0), boardPositionInWorld(0,0,0)
{

}

void Board::drawWalls(Cube& cube, ShaderProgram& shader)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t k = 0; k < 10; k++)
			{
				char fieldState = getFieldState(i, j, k);

				switch (fieldState)
				{
				case Field::WALL:
				{
					cube.setPosition(calculateOffset(i, j, k));
					cube.draw(shader);
					break;
				}
				default:
					break;
				}

			}
		}
	}
}

Field Board::getFieldState(int x, int y, int z) const
{
	return static_cast<Field>(boardValues.at(y * FLOOR_FIELDS + z * BOARD_SIDE_SIZEX + x));
}

Field Board::getFieldState(glm::vec3 pos) const
{
	return static_cast<Field>(boardValues.at(pos.y * FLOOR_FIELDS + pos.z * BOARD_SIDE_SIZEX + pos.x));
}

glm::vec3 Board::calculateOffset(int x, int y, int z) const
{
	return glm::vec3( x * FIELD_SIZE_X , y * FIELD_SIZE_Y , z * FIELD_SIZE_Z);
}

void Board::loadLevel(std::string filePath)
{
	fstream file(filePath, ios::in);

	char fieldState;

	for (size_t i = 0; i < 10*10*10; i++)
	{
		file >> fieldState;
		boardValues.at(i) = fieldState-48;
	}

	file.close();
}

void Board::saveLevel(std::string filePath)
{
	fstream file(filePath, ios::out);

	char fieldState;

	for (size_t i = 0; i < 10*10*10; i++)
	{
		file << static_cast<int>(boardValues.at(i)) << " ";
	}

	file.close();
}

void Board::setFieldState(int x, int y, int z, Field state)
{
	boardValues.at(y * FLOOR_FIELDS + z * BOARD_SIDE_SIZEX + x) = state;
}

void Board::setFieldState(glm::ivec3 pos, Field state)
{
	boardValues.at(pos.y * FLOOR_FIELDS + pos.z * BOARD_SIDE_SIZEX + pos.x) = state;
}

void Board::setBoardInWorldPosition(glm::vec3 boardPositionInWorld)
{
	this->boardPositionInWorld = boardPositionInWorld;
}

glm::vec3 Board::getBoardPositionInWorld()
{
	return boardPositionInWorld;
}