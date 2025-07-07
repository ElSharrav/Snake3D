#ifndef COLOR_H
#define COLOR_H

#include <glm/vec4.hpp>

struct Color
{
	float R;
	float G;
	float B;
	float A;

	Color(float R, float G, float B, float A);

	static glm::vec4 Red;
	static glm::vec4 Black;
	static glm::vec4 White;
};

#endif