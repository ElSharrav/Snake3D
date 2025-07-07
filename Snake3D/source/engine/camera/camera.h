#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "../shaders/shaderProgram.h"

#include "../macros.h"

class Camera
{
	float radius;
	float angle;
	float angleY;

	glm::vec3 center;

	//transformation matrix
	glm::mat4 view; 

	glm::vec3 position;
	// up vector for camera
	glm::vec3 up;			

	float angleSensitivity;
	float angleYSensitivity;
	float radiusSensitivity;

	void calculatePosition();

public:
	Camera( glm::vec3 pos = glm::vec3(0) );
	~Camera();

	glm::mat4 getView( );
	glm::vec3 getPosition();

	void setAngle(float angle);
	void setAngleY(float angle);
	void addAngle(float angle);
	void addAngleY(float angleY);

	void addRadius(float radius);
	float getAngle();
	float getAngleY();

	SETTER(float, angleSensitivity);
	SETTER(float, angleYSensitivity);
};

#endif
