#include "material.h"

#include <glm/gtc/matrix_transform.hpp>

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess) :ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{

}

Material::~Material()
{

}


float Material::getShininess() const
{
	return shininess;
}
glm::vec3 Material::getAmbient() const
{
	return ambient;
}
glm::vec3 Material::getSpecular() const
{
	return specular;
}
glm::vec3 Material::getDiffuse() const
{
	return diffuse;
}