#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <glad/glad.h> 
#include <glm/matrix.hpp>



class Material;
class Light;
class Shader;

class ShaderProgram
{
	unsigned int shaderProgram;
public:
	ShaderProgram();

	std::string link(Shader* vertexShader, Shader* fragmentShader);
	void use();
	void setInt(const std::string& name, int value); // must call use() before setInt();
	void setFloat(const std::string& name, float value);
	void setMatrix4(const std::string& name, glm::mat4 matrix);
	void setVec3(const std::string& name,const glm::vec3 &vector);
	void setCameraPos(const glm::vec3& cameraPos);
	void setLight(const Light& light);
	void setMaterial(const Material& material);
//	std::string compile(const std::string& vertexShaderSource);		// if compilation succesful empty string is returned otherwise error string is returned
};

#endif
