#include "shader.h"

#include <fstream>
#include <sstream>

Shader::Shader( GLenum shaderType)
{
	shader = glCreateShader(shaderType);
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

std::string Shader::compile(const std::string& vertexShaderSource)
{
	const char* shaderSource = vertexShaderSource.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	std::string returnMessage = "";
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		returnMessage += "Error in shader: " + vertexShaderSource + infoLog;
	}
	return returnMessage;
}

std::string Shader::compileFromPath(const std::string& shaderPath)
{
    std::string shaderCode;

    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
		return "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }

    return compile(shaderCode.c_str());
}

unsigned int Shader::getShader()
{
	return shader;
}