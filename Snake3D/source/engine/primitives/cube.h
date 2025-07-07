#ifndef CUBE_H
#define CUBE_H

#include "Point3d.h"
#include "Vec2.h"
#include "Point3d.h"

#include "../shaders/shaderProgram.h"

#include <glm/matrix.hpp>

// cube goes from point (0,0,0) to every axis in positive part of axis
/*
* 36 vertices ( 2 triangles * 3 vertices * 6 cube sides )
* 
* 
* order of vertices for each side
2---3                3         2---3
|   |  becomes      /|   and   |  /
|   |             /  |         |/
0---1            0---1         0

0-1-3 and 0-3-2 is order in vertices
*/
class Cube
{
	unsigned int VBO;
	unsigned int VAO;
//	float vertices[288]; // without normals
	float vertices[396];


	glm::mat4 model;
public:
	Cube(float width, float lenght, float height);

	void draw(ShaderProgram& shader);
	void move(glm::vec3 move);
	void setColor(glm::vec3 color);
	void setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords,  Vec2<float> fourthTexCoords);
	void setPosition(const glm::vec3& position);
	//void rotate( float degrees,  glm::vec3 axis);
};

#endif
