#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/glad.h> 


class Texture
{
	unsigned int texture;
public:
	Texture();

	void activate();
	void load(const std::string& texturePath);

};

#endif
