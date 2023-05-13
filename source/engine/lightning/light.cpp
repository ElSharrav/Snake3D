#include "light.h"

#include <glm/gtc/matrix_transform.hpp>

Light::Light(const glm::vec3& position,const glm::vec3& ambient ,const glm::vec3& diffuse ,const glm::vec3& specular ) : position(position),ambient(ambient), diffuse(diffuse), specular(specular), range(2), source(0.05,0.05,0.05)
{
	source.move(position);
	source.setColor(glm::vec3(1.0,1.0,1.0));
}

Light::~Light()
{

}

glm::vec3 Light::getPosition() const
{
	return position;
}
glm::vec3 Light::getAmbient() const 
{
	return ambient;
}
glm::vec3 Light::getSpecular() const

{
	return specular;
}
glm::vec3 Light::getDiffuse() const

{
	return diffuse;
}
float Light::getRange() const

{
	return range;
}

void Light::setPosition(const glm::vec3& position)
{
	this->position = position;
	source.setPosition(position);
}

void Light::draw(ShaderProgram& shader)
{
	source.draw(shader);
}