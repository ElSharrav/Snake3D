#ifndef SNAKETAIL_H
#define SNAKETAIL_H

#include <queue>

#include "board.h"
#include "../engine/shaders/shaderProgram.h"
#include "../engine/primitives/cube.h"

#include <glm/vec3.hpp>

class SnakeTail
{
	std::queue<glm::ivec3> movements;

	Board* board;

	float snakeVelocity;

	bool movementBlocked;

	glm::ivec3 movementDirection;			// movement direction and movement direction requested are always meant to be normalized one axis vectors

		// when we are moving towards negative axis ex. from 3 to 2 on given axis, we need to add 1 on given axis to centerPosition vector, to make it the same case as with moving towards positive numbers
	// when we are moving towards positive axis, compensationVector should be equal 0
	glm::ivec3 compensationVector;
	
	glm::vec3 movementDirectionMultipliedWithVelocity;

	glm::vec3 worldPosition;

	glm::ivec3 boardPositionCoords;

	void calculateMovementDirectionMultipliedWithVelocity();
	glm::ivec3 calculateBoardPosition(glm::vec3 worldPosition);

public:
	SnakeTail(Board* board, glm::vec3 startingPos = glm::vec3(0, 0, 0), glm::ivec3 startingMovementDirection = glm::vec3(1,0,0), glm::ivec3 startingCompensationVector = glm::ivec3(0, 0, 0));

	void move(float deltaTime);

	void draw(Cube& cube, ShaderProgram& shader);

	void setSnakeVelocity(float velocity);

	void addMovementToQueue(glm::vec3 direction);

	std::queue<glm::ivec3>& getQueue();

	void setMovementBlocked( bool movementBlocked );
};

#endif