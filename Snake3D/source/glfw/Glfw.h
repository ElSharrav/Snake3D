#ifndef GLFW_H
#define GLFW_H

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include<string>

class Glfw
{
private:
	Glfw();

public:

	static GLFWwindow* createWindow(int width, int height,const std::string& title, GLFWmonitor* monitor = NULL);
	static int initGlfw(int majorOpenGLVersion, int minorOpenGLVersion, int openGLProfile);
	static void terminate();
};


#endif
