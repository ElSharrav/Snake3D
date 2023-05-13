#ifndef FONTS_H
#define FONTS_H

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glm/vec2.hpp>


#include "../shaders/shaderProgram.h"

#include <map>

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class Font
{
	unsigned int VAO, VBO;

	FT_Library ft;
	FT_Face face;

	std::map<char, Character> Characters;


public:
	Font(const std::string& path, int size);

	void loadCharacters();
	void RenderText(ShaderProgram& s, std::string text, float x, float y, float scale, glm::vec3 color);
	float getTextAdvanceInPixels(const std::string& text);
};

#endif