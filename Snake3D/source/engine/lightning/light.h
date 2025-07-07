#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "../primitives/cube.h"

class Light
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3 position;

	float range;

	Cube source;

public:
	Light( const glm::vec3& position = glm::vec3(0.0) ,const glm::vec3& ambient = glm::vec3(0.3),const glm::vec3& diffuse = glm::vec3(0.6),const glm::vec3& specular = glm::vec3(1.0));
	~Light();

	glm::vec3 getPosition() const ;
	glm::vec3 getAmbient() const ;
	glm::vec3 getSpecular() const ;
	glm::vec3 getDiffuse() const ;
	float getRange() const ;

	void setPosition(const glm::vec3& position);

	void draw(ShaderProgram& shader);
};

#endif
