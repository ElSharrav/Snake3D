#pragma once

#include "../fonts/Fonts.h"
#include "../shaders/shader.h"

#include <unordered_map>
#include <string>

enum Textures_Id
{

};

enum Fonts
{
	MAIN_FONT,
};

enum Sounds_Id
{

};

enum Musics_Id
{

};

enum Shaders
{
	TEXT_SHADER,
};

class ResourceManager;

class TextureNotFoundException
{
public:
	TextureNotFoundException(const std::string& texturePath);
	std::string texturePath;
};

class ResourceMachine
{
	std::unordered_map<Fonts, Font*> fonts;
	std::unordered_map<Shaders, ShaderProgram*> shaders;

	~ResourceMachine();
	ResourceMachine();

//	void deleteTextures();
	void deleteFonts();
	void deleteShaders();
//	void deleteSoundBuffers();
//	void deleteSolids();

//	void addTexture(sf::Texture* texture, Textures_Id id);
	void addFont(Font* font, Fonts id);
	void addShader(ShaderProgram* shader, Shaders id);
//	void addSoundBuffer(sf::SoundBuffer* buffer, Sounds_Id id);

public:

	friend class ResourceManager;
};

class ResourceManager
{
	static ResourceMachine rm;

	ResourceManager();

	static void compileAndLinkShader(ShaderProgram* shader, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

public:

//	static void loadSoundBuffer(const std::string& filePath, Sounds_Id id);
//	static void loadTexture(const std::string& filePath, Textures_Id id);
	static void loadFont(const std::string& filePath, int size, Fonts id);
	static void loadShader(const std::string& vShaderPath, const std::string& fShaderPath, Shaders id);

//	static void addSolid(Solid* solid, const std::string& label);

//	static sf::Texture* getTexture(Textures_Id id);
//	static sf::SoundBuffer* getSoundBuffer(Sounds_Id id);
	static Font* getFont(Fonts id);
	static ShaderProgram* getShader(Shaders id);
//	static Solid* getSolid(const std::string& label);
};