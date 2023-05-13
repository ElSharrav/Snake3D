#ifndef NDCQUAD_H
#define NDCQUAD_H

#include "../shaders/shaderProgram.h"
#include <glm/vec3.hpp>

class NDCquad
{
	unsigned int VBO;
	unsigned int VAO;
	float vertices[24];

public:
	NDCquad();

	void draw(ShaderProgram& shader);

};

#endif