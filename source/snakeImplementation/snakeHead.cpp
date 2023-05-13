#include "snakeHead.h"

#include <iostream>

using namespace std;

SnakeHead::SnakeHead(Board* board, glm::vec3 startingPos, glm::ivec3 startingMovementDirection, glm::ivec3 startingCompensationVector ) : worldPosition(startingPos), board(board), movementDirection(startingMovementDirection), movementDirectionRequested(startingMovementDirection), compensationVector(startingCompensationVector)
{
	snakeVelocity = 2;
	calculateMovementDirectionMultipliedWithVelocity();
	boardPositionCoords = calculateBoardPosition( worldPosition );
}


void SnakeHead::calculateMovementDirectionMultipliedWithVelocity()
{
	movementDirectionMultipliedWithVelocity = snakeVelocity * static_cast<glm::vec3>(movementDirection);
}

glm::ivec3 SnakeHead::calculateBoardPosition(glm::vec3 worldPosition)
{
	worldPosition = worldPosition - board->getBoardPositionInWorld();
	
	glm::ivec3 boardCoords;

	boardCoords.x = worldPosition.x / FIELD_SIZE_X;
	boardCoords.y = worldPosition.y / FIELD_SIZE_Y;
	boardCoords.z = worldPosition.z / FIELD_SIZE_Z;

	if (worldPosition.x < 0) { boardCoords.x -= 1; }
	if(worldPosition.y < 0) { boardCoords.y -= 1; }
	if(worldPosition.z < 0) { boardCoords.z -= 1; }

	return boardCoords;
}

Field SnakeHead::move( float deltaTime, SnakeTail& tail)
{
	Field collisionField = Field::EMPTY;

	glm::vec3 movement = deltaTime * movementDirectionMultipliedWithVelocity;

	worldPosition += movement;

	glm::ivec3 newBoardPositionCoords = calculateBoardPosition(worldPosition);

	newBoardPositionCoords += compensationVector;

	if (newBoardPositionCoords != this->boardPositionCoords) // snake entered new field
	{
		tail.setMovementBlocked(false);

		if (movementDirection != movementDirectionRequested) // we must change direction
		{
			worldPosition.x = newBoardPositionCoords.x * FIELD_SIZE_X;
			worldPosition.y = newBoardPositionCoords.y * FIELD_SIZE_Y;
			worldPosition.z = newBoardPositionCoords.z * FIELD_SIZE_Z;

			movementDirection = movementDirectionRequested;
			compensationVector = compensationVectorRequested;
			calculateMovementDirectionMultipliedWithVelocity();
		}

		// we say to snakeTail where it should go
		tail.getQueue().push(movementDirection);


		// check if we hit the wall
		glm::vec3 nextField = newBoardPositionCoords + movementDirection;
	
		if ((nextField.x >= BOARD_SIDE_SIZEX) || (nextField.y >= BOARD_SIDE_SIZEY) || (nextField.z >= BOARD_SIDE_SIZEZ) || (nextField.x < 0) || (nextField.y < 0) || (nextField.z < 0))
		{
			collisionField = Field::WALL;
//			std::cout << nextField.x << " " << nextField.y << " " << nextField.z << std::endl;
		}
		else
		{
			// check with what we are colliding 
			collisionField = board->getFieldState(nextField);
		}

		// flag field as traversed by snake
		board->setFieldState(newBoardPositionCoords, Field::SNAKE);

	}	

	this->boardPositionCoords = newBoardPositionCoords;

	return collisionField;
}

void SnakeHead::requestDirectionChange(glm::ivec3 movementDirection, glm::ivec3 compensationVector)
{
	if ( movementDirection != -this->movementDirection )
	{
		this->movementDirectionRequested = movementDirection;
		this->compensationVectorRequested = compensationVector;
	}
}

void SnakeHead::draw(Cube& cube, ShaderProgram& shader)
{
	cube.setPosition(worldPosition);
	cube.draw(shader);
}

void SnakeHead::setSnakeVelocity(float velocity)
{
	this->snakeVelocity = velocity;
	calculateMovementDirectionMultipliedWithVelocity();
}