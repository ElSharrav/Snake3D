#include "Glfw.h"

Glfw::Glfw()
{

}

GLFWwindow* Glfw::createWindow(int width, int height,const std::string& title, GLFWmonitor* monitor)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
    glfwMakeContextCurrent(window);
    return window;
}


int Glfw::initGlfw(int majorOpenGLVersion, int minorOpenGLVersion, int openGLProfile)
{
    int result = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorOpenGLVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorOpenGLVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, openGLProfile);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    return result;
}

void Glfw::terminate()
{
    glfwTerminate();
}

