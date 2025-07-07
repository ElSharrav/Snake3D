#include "Glad.h"

#include "glad/glad.h" 
#include "GLFW\glfw3.h"
//#include "glad.c"

Glad::Glad()
{

}


bool Glad::loadFunctionPointers()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}