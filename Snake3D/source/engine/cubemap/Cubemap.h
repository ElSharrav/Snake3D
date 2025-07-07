#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>
#include <vector>

class Cubemap
{
	unsigned int cubeMap;
public:
	Cubemap();

	void activate();

	// argument needs to contain 6 strings, with paths to cubemap textures with following order:
	// 1. 	GL_TEXTURE_CUBE_MAP_POSITIVE_X	
	// 2.	GL_TEXTURE_CUBE_MAP_NEGATIVE_X	
	// 3.	GL_TEXTURE_CUBE_MAP_POSITIVE_Y	
	// 4.	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	
	// 5.	GL_TEXTURE_CUBE_MAP_POSITIVE_Z	
	// 6.	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	void load(std::vector<std::string>& texturePaths);	
};

#endif