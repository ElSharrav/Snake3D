#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader
{
	unsigned int shader;
public:
	Shader( GLenum shaderType);
	~Shader();

	std::string compile(const std::string& vertexShaderSource);		// if compilation succesful empty string is returned otherwise error string is returned
	std::string compileFromPath(const std::string& shaderPath);		// if compilation succesful empty string is returned otherwise error string is returned
	unsigned int getShader();
};

#endif
