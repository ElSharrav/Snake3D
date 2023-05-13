#ifndef LINE_H
#define LINE_H

#include "Point3d.h"
#include "Vec2.h"
#include "Point3d.h"

#include "../shaders/shaderProgram.h"

#include <glm/matrix.hpp>

class Line
{
	unsigned int VBO;
	unsigned int VAO;
	float vertices[12];

	float width;

	glm::mat4 model;
public:
	Line(glm::vec3 firstVertice, glm::vec3 secondVertice);

	void draw(ShaderProgram& shader);
	void setColor(glm::vec3 color);
	void setWidth(float width);
	void setPosition(glm::vec3 position);
//	void setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords);
	void rotate( float degrees,  glm::vec3 axis);
};

#endif
