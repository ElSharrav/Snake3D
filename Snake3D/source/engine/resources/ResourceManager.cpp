#pragma once

#include "ResourceManager.h"

#include "../macros.h"

#include <iostream>

TextureNotFoundException::TextureNotFoundException(const std::string& texturePath) : texturePath(texturePath)
{
	
}

ResourceMachine::ResourceMachine()
{

}

ResourceMachine::~ResourceMachine()
{
//	deleteTextures();
	deleteFonts();
	deleteShaders();
//	deleteSolids();
//	deleteSoundBuffers();
}


void ResourceMachine::deleteFonts()
{
	for (auto i = fonts.begin(); i != fonts.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceMachine::deleteShaders()
{
	for (auto i = shaders.begin(); i != shaders.end(); ++i)
	{
		delete i->second;
	}
}
/*
void ResourceMachine::deleteTextures()
{
	for (auto i = textures.begin(); i != textures.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceMachine::deleteSoundBuffers()
{
	for (auto i = soundBuffers.begin(); i != soundBuffers.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceMachine::deleteSolids()
{
	for (auto i = solids.begin(); i != solids.end(); ++i)
	{
		delete i->second;
	}
}

void ResourceManager::loadTexture(const std::string& filePath, Textures_Id id)
{
	sf::Texture* texture = new sf::Texture();
	if ( !texture->loadFromFile(filePath) ) { 
		throw TextureNotFoundException(filePath);
	}
	rm.addTexture(texture, id);

	LOGLN("Texture: " << id << " Succesfully Loaded: " << filePath);
}

*/

void ResourceManager::loadFont(const std::string& filePath,int size,  Fonts id)
{
	Font* font = new Font(filePath, size);
	font->loadCharacters();

	rm.addFont(font, id);
}

 void ResourceManager::loadShader(const std::string& vShaderPath, const std::string& fShaderPath, Shaders id)
{
	 ShaderProgram* shader = new ShaderProgram();

	 compileAndLinkShader(shader, vShaderPath, fShaderPath);
	 
	 rm.addShader(shader, id);
}

void ResourceManager::compileAndLinkShader(ShaderProgram* shader, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	Shader vShader(GL_VERTEX_SHADER);

	std::string vShaderCompileMessage = vShader.compileFromPath(vertexShaderPath);

	if (vShaderCompileMessage.size() > 0)
	{
		LOG(vertexShaderPath + " : " + vShaderCompileMessage);
	}
	else
	{
		LOG(vertexShaderPath + " : " + "vertex shader compiled without errors");
	}

	Shader fShader(GL_FRAGMENT_SHADER);

	std::string fShaderCompileMessage = fShader.compileFromPath(fragmentShaderPath);

	if (fShaderCompileMessage.size() > 0)
	{
		LOG(fragmentShaderPath + " : " + fShaderCompileMessage);
	}
	else
	{
		LOG(fragmentShaderPath + " : " + "fragment shader compiled without errors");
	}

	shader->link(&vShader, &fShader);
}

/*

void ResourceManager::loadSoundBuffer(const std::string& filePath, Sounds_Id id)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	if (!soundBuffer->loadFromFile(filePath)) {
		//throw TextureNotFoundException(filePath);		// sound buffer not found
	}
	rm.addSoundBuffer(soundBuffer, id);

	LOGLN("Sound Buffer: " << id << " Succesfully Loaded: " << filePath);
}

sf::Texture* ResourceManager::getTexture(Textures_Id id)
{
	return rm.textures.at(id);
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(Sounds_Id id)
{
	return rm.soundBuffers.at(id);
}

*/

Font* ResourceManager::getFont(Fonts id)
{
	return rm.fonts.at(id);
}

 ShaderProgram* ResourceManager::getShader(Shaders id)
{
	return rm.shaders.at(id);
}
/*
Solid* ResourceManager::getSolid(const std::string& label)
{
	return rm.solids.at(label);
}

void ResourceMachine::addTexture(sf::Texture* texture, Textures_Id id)
{
	textures.insert({id, texture});
}
*/
void ResourceMachine::addFont(Font* font, Fonts id)
{
	fonts.insert({ id, font });
}

void ResourceMachine::addShader(ShaderProgram* shader, Shaders id)
{
	shaders.insert({ id, shader});
}
/*
void ResourceMachine::addSoundBuffer(sf::SoundBuffer* buffer, Sounds_Id id)
{
	soundBuffers.insert({ id, buffer });
}
void ResourceManager::addSolid(Solid* solid, const std::string& label)
{
	rm.solids.insert({ label, solid });
}

*/

ResourceMachine ResourceManager::rm;