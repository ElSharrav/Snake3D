#include "MenuOption.h"
#include <iostream>

MenuOption::MenuOption( glm::vec2 position) : centerPosition(position)
{
	color = glm::vec3(0.0, 0.0, 0.0);
	width = 0;

	scale = 1.0f;
	scaleDir = 1;

	scaleSpeed = 1.0f;

	scaleUpperBound = 1.75f;
	scaleLowerBound = 1.0f;
}


void MenuOption::draw(Font& font, ShaderProgram& textShader)
{
	float scaledWidth = (width * scale);
	
	font.RenderText(textShader, label , centerPosition.x - (scaledWidth/2), centerPosition.y , scale, color);
}

void MenuOption::updateScale(float dt)
{
	scale += (dt * scaleDir * scaleSpeed);

	if (scale > scaleUpperBound)
	{
		scale = scaleUpperBound;
		scaleDir = -1;
	}
	else if( scale < scaleLowerBound )
	{
		scale = scaleLowerBound;
		scaleDir = 1;
	}
}

void MenuOption::resetScale()
{
	scale = 1.0f;
	scaleDir = 1;
}

void MenuOption::setLabel(const std::string& label, Font& font)
{
	this->label = label;
	width = font.getTextAdvanceInPixels(this->label);
}