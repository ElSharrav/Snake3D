#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "../../engine/macros.h"
#include "../../engine/fonts/Fonts.h"

class MenuOption
{
	std::string label;
	float width;
	
	glm::vec2 centerPosition;
	glm::vec3 color;

	float scale;
	int scaleDir;	
	float scaleUpperBound, scaleLowerBound, scaleSpeed;

public:
	MenuOption( glm::vec2 position = glm::vec2(0,0));

	void draw( Font& font, ShaderProgram& textShader );

	void updateScale(float dt);
	void resetScale();

	void setLabel(const std::string& label, Font& font);

	SETTER(const glm::vec2&, centerPosition);
	SETTER(const glm::vec3&, color);

	GETTER(std::string, label);
	GETTER(float, width);
	GETTER(glm::vec2, centerPosition);
};

#endif