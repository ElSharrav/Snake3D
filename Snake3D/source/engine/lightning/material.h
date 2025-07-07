#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

class Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

public:
	Material(const glm::vec3& ambient , const glm::vec3& diffuse , const glm::vec3& specular , float shininess = 32);
	~Material();

	float getShininess() const ;
	glm::vec3 getAmbient() const;
	glm::vec3 getSpecular() const;
	glm::vec3 getDiffuse() const;

};

#endif
