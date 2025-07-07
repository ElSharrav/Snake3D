#include "SnakeTail.h"

SnakeTail::SnakeTail(Board* board, glm::vec3 startingPos , glm::ivec3 startingMovementDirection , glm::ivec3 startingCompensationVector) : worldPosition(startingPos)
, movementDirection(startingMovementDirection), compensationVector(startingCompensationVector), board(board), movementBlocked(false)
{
	snakeVelocity = 2;
	calculateMovementDirectionMultipliedWithVelocity();
	boardPositionCoords = calculateBoardPosition(worldPosition);
}

void SnakeTail::move(float deltaTime)
{
	if (! movementBlocked)
	{

		glm::vec3 movement = deltaTime * movementDirectionMultipliedWithVelocity;

		worldPosition += movement;

		glm::ivec3 newBoardPositionCoords = calculateBoardPosition(worldPosition);

		newBoardPositionCoords += compensationVector;

		if (newBoardPositionCoords != this->boardPositionCoords) // snake tail entered new field
		{
			// flag field as traversed by snake
			board->setFieldState(newBoardPositionCoords, Field::EMPTY);

			glm::ivec3 newDirection = movements.front();

			if (newDirection != movementDirection)	// we are changing direction
			{
				worldPosition.x = newBoardPositionCoords.x * FIELD_SIZE_X;
				worldPosition.y = newBoardPositionCoords.y * FIELD_SIZE_Y;
				worldPosition.z = newBoardPositionCoords.z * FIELD_SIZE_Z;
			}

			movementDirection = newDirection;

			if (movementDirection.x < 0) { compensationVector = glm::vec3(1, 0, 0); }
			else if (movementDirection.y < 0) { compensationVector = glm::vec3(0, 1, 0); }
			else if (movementDirection.z < 0) { compensationVector = glm::vec3(0, 0, 1); }
			else
			{
				compensationVector = glm::vec3(0);
			}

			calculateMovementDirectionMultipliedWithVelocity();
			movements.pop();
			// check if we are colliding with anything
	//		collisionField = board->getFieldState(newBoardPositionCoords + movementDirection);
		}

		this->boardPositionCoords = newBoardPositionCoords;

	}
}

void SnakeTail::draw(Cube& cube, ShaderProgram& shader)
{
	cube.setPosition(worldPosition);
	cube.draw(shader);
}

void SnakeTail::calculateMovementDirectionMultipliedWithVelocity()
{
	movementDirectionMultipliedWithVelocity = snakeVelocity * static_cast<glm::vec3>(movementDirection);
}

void SnakeTail::setSnakeVelocity(float velocity)
{
	this->snakeVelocity = velocity;
	calculateMovementDirectionMultipliedWithVelocity();
}

glm::ivec3 SnakeTail::calculateBoardPosition(glm::vec3 worldPosition)
{
	worldPosition = worldPosition - board->getBoardPositionInWorld();

	glm::ivec3 boardCoords;

	boardCoords.x = worldPosition.x / FIELD_SIZE_X;
	boardCoords.y = worldPosition.y / FIELD_SIZE_Y;
	boardCoords.z = worldPosition.z / FIELD_SIZE_Z;

	if (worldPosition.x < 0) { boardCoords.x -= 1; }
	if (worldPosition.y < 0) { boardCoords.y -= 1; }
	if (worldPosition.z < 0) { boardCoords.z -= 1; }

	return boardCoords;
}

void SnakeTail::addMovementToQueue(glm::vec3 direction)
{
	movements.push(direction);
}

std::queue<glm::ivec3>& SnakeTail::getQueue()
{
	return movements;
}

void SnakeTail::setMovementBlocked(bool movementBlocked)
{
	this->movementBlocked = movementBlocked;
}