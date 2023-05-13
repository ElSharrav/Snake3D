#ifndef SNAKE_H
#define SNAKE_H

#include "snakeHead.h"
#include "snakeTail.h"

#include "../engine/macros.h"

#include <glm/vec3.hpp>

class Snake
{
	float snakeVelocity;

	int size;

	Board* board;
	SnakeHead head;
	SnakeTail tail;

public:
	Snake( Board* board);

	void draw(Cube& cube, ShaderProgram& shader);
	Field move(float deltaTime);
	void requestDirectionChange(glm::ivec3 movementDirection, glm::ivec3 compensationVector);

	void setSnakeVelocity(float velocity);

	GETTER(int, size);
	GETTER_REF(SnakeHead, head);

	GETTER(float, snakeVelocity);
};

#endif