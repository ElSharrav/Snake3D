#include "camera.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos) : view( glm::mat4(1.0f)), radiusSensitivity(0.5f), angleSensitivity(0.10f), angleYSensitivity(0.10f), radius( 20.0f ), angle( 90.0f ), angleY(45.0f)
{
	center = glm::vec3(5, 5, 5);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	calculatePosition();

	view = glm::lookAt(position, center, up);
}

Camera::~Camera()
{

}

void Camera::calculatePosition()
{
	float radians = glm::radians(angle);
	float radiansY = glm::radians(angleY);

	position.y = center.y + radius * glm::sin(radiansY);
	position.x = center.x + radius * glm::cos(radians) * glm::cos(radiansY);
	position.z = center.z + radius * glm::sin(radians) * glm::cos(radiansY);

	view = glm::lookAt(position, center, up);
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::mat4 Camera::getView()
{
	return view;
}

void Camera::setAngle(float angle)
{
	this->angle = angle;

	calculatePosition();
}

void Camera::addAngle(float angle)
{
	this->angle += (angleSensitivity * angle) ;

//	std::cout << angle << std::endl;

	calculatePosition();
}

void Camera::addAngleY(float angleY)
{
	this->angleY += (angleYSensitivity * angleY);

	if (this->angleY > 89)
	{
		this->angleY = 89;
	}
	else if (this->angleY < -89)
	{
		this->angleY = -89;
	}

//	std::cout << this->angleY << std::endl;

	calculatePosition();
}

void Camera::setAngleY(float angleY)
{
	this->angleY = angleY;

	if (this->angleY > 89)
	{
		this->angleY = 89;
	}
	else if (this->angleY < -89)
	{
		this->angleY = -89;
	}

//	std::cout << this->angleY << std::endl;

	calculatePosition();
}

void Camera::addRadius(float radius)
{
	this->radius += (radius * radiusSensitivity );

	calculatePosition();
}

float Camera::getAngle()
{
	return angle;
}

float Camera::getAngleY()
{
	return angleY;
}