#include "texture.h"

#include <stdexcept>

#include "../../stb_image/stb_image.h"

Texture::Texture( )
{
	
}

void Texture::activate()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::load(const std::string& texturePath)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		throw std::invalid_argument("Failed to load texture");
	}

	stbi_image_free(data);
}