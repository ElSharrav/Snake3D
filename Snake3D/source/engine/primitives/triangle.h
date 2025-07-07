#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point3d.h"
#include "Vec2.h"
#include "Point3d.h"

#include "../shaders/shaderProgram.h"

#include <glm/matrix.hpp>

class Triangle
{
	unsigned int VBO;
	unsigned int VAO;
	float vertices[24];

	glm::mat4 model;
public:
	Triangle(Vec3<float> firstVertice, Vec3<float> secondVertice, Vec3<float> thirdVertice);

	void draw(ShaderProgram& shader);
	void setColor(Vec3<float> color);
	void setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords);
	void rotate( float degrees,  glm::vec3 axis);
};

#endif
