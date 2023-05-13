#include "Snake.h"


Snake::Snake(Board* board) : board(board), head(board), tail(board), snakeVelocity(2), size(2)
{
	tail.getQueue().push(glm::vec3(1, 0, 0));
	head.setSnakeVelocity(snakeVelocity);
	tail.setSnakeVelocity(snakeVelocity);
}

void Snake::draw(Cube& cube, ShaderProgram& shader)
{
	
	// drawing snake head
	head.draw(cube, shader);

	// drawing snake body
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t k = 0; k < 10; k++)
			{
				char fieldState = board->getFieldState(i, j, k);

				switch (fieldState)
				{
				case Field::SNAKE:
				{
					cube.setPosition(board->calculateOffset(i, j, k));
					cube.draw(shader);
					break;
				}
				default:
					break;
				}

			}
		}
	}

	//todo drawing snake tail

	tail.draw(cube, shader);
}

Field Snake::move(float deltaTime)
{
	Field enteredField = head.move(deltaTime, tail);
	tail.move(deltaTime);

	if (enteredField == Field::FOOD) 
	{ 
		tail.setMovementBlocked(true);
		++size;
	}

	return enteredField;
}

void Snake::requestDirectionChange(glm::ivec3 movementDirection, glm::ivec3 compensationVector)
{
	head.requestDirectionChange(movementDirection, compensationVector);
}

void Snake::setSnakeVelocity(float velocity)
{
	this->snakeVelocity = velocity;
	head.setSnakeVelocity(velocity);
	tail.setSnakeVelocity(velocity);
}