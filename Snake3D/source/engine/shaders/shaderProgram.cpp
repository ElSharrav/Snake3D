#include "shaderProgram.h"

#include "shader.h" 

#include <glm/gtc/type_ptr.hpp>

#include "../lightning/light.h"
#include "../lightning/material.h"

ShaderProgram::ShaderProgram( )
{
	shaderProgram = glCreateProgram();
}

std::string ShaderProgram::link(Shader* vertexShader, Shader* fragmentShader)
{
	glAttachShader(shaderProgram, vertexShader->getShader());
	glAttachShader(shaderProgram, fragmentShader->getShader());
	glLinkProgram(shaderProgram);

	int  success;
	char infoLog[512];
	std::string returnMessage = "";
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		returnMessage += "Error in linking shaders: " ;
		returnMessage += infoLog;
	}
	return returnMessage;
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::setInt(const std::string& name , int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name , float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, glm::mat4 matrix)
{
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setVec3(const std::string& name,const glm::vec3 &vector)
{
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUniform3fv(location, 1, &vector[0]);
	
}

void ShaderProgram::setCameraPos(const glm::vec3& cameraPos)
{
	setVec3("cameraPosition", cameraPos);
}

void ShaderProgram::setLight(const Light& light)
{
	setVec3("light1.ambient", light.getAmbient());
	setVec3("light1.diffuse", light.getDiffuse());
	setVec3("light1.specular", light.getSpecular());
	setVec3("light1.position", light.getPosition());
	setFloat("light1.range", light.getRange());
}
void ShaderProgram::setMaterial(const Material& material)
{
	setVec3("material.ambient", material.getAmbient());
	setVec3("material.diffuse", material.getDiffuse());
	setVec3("material.specular", material.getSpecular());
	setFloat("material.shininess", material.getShininess());
}