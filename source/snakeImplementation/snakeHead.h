#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "board.h"
#include "SnakeTail.h"
#include "../engine/shaders/shaderProgram.h"
#include "../engine/primitives/cube.h"

#include "../engine/macros.h"

#include <glm/vec3.hpp>
#include <queue>

class SnakeHead
{
	Board* board;

	float snakeVelocity;
	
	glm::ivec3 movementDirection;			// movement direction and movement direction requested are always meant to be normalized one axis vectors
	glm::ivec3 movementDirectionRequested;

	// when we are moving towards negative axis ex. from 3 to 2 on given axis, we need to add 1 on given axis to centerPosition vector, to make it the same case as with moving towards positive numbers
	// when we are moving towards positive axis, compensationVector should be equal 0
	glm::ivec3 compensationVector; 
	glm::ivec3 compensationVectorRequested; 

	glm::vec3 movementDirectionMultipliedWithVelocity;

	glm::vec3 worldPosition;
	glm::vec3 boardPositionPixels;
	glm::ivec3 boardPositionCoords;


	void calculateMovementDirectionMultipliedWithVelocity();
	glm::ivec3 calculateBoardPosition(glm::vec3 worldPosition);
public:
	SnakeHead(Board* board, glm::vec3 startingPos = glm::vec3(1, 0, 0) , glm::ivec3 startingMovementDirection = glm::vec3(1, 0, 0), glm::ivec3 startingCompensationVector = glm::ivec3(0,0,0) );

	Field move(float deltaTime, SnakeTail& tail);
	void requestDirectionChange(glm::ivec3 movementDirection, glm::ivec3 compensationVector);
	void draw(Cube& cube, ShaderProgram& shader);
	void setSnakeVelocity(float velocity);

	GETTER(glm::ivec3, movementDirection);
	GETTER(glm::vec3, worldPosition);
};

#endif