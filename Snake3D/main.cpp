#include "source/Glad/Glad.h"
#include "source/glfw/Glfw.h"

#include "source/engine/engine.h"
#include "source/engine/macros.h"

#include "source/stb_image/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string_view>

constexpr unsigned int majorOpenGLVersion = 3;
constexpr unsigned int minorOpenGLVersion = 3;

constexpr unsigned int windowX = 1920;
constexpr unsigned int windowY = 1080;

//#define windowX 1366
//#define windowY 768

constexpr char windowTitle[] = "Snake 3d";

int main()
{
//	stbi_set_flip_vertically_on_load(true);

	bool GLFWResult = Glfw::initGlfw(majorOpenGLVersion, minorOpenGLVersion, GLFW_OPENGL_CORE_PROFILE);
	if (!GLFWResult)
	{
		LOG("Initializing GLFW error");
		return ERROR_EXIT_CODE;
	}

	glm::vec2 screenSize = Engine::getWindowsScreenSize();

	GLFWwindow* window = Engine::createWindow(screenSize.x, screenSize.y, windowTitle, glfwGetPrimaryMonitor());
//	GLFWwindow* window = Engine::createWindow(windowX, windowY, WINDOW_TITLE, glfwGetPrimaryMonitor());

	if (window == NULL)
	{
		LOG("Failed to initialize window");
		return 1;
	}

	bool gladInitialization = Glad::loadFunctionPointers();
	if (!gladInitialization)
	{
		LOG("Glad initialization error");
		return 1;
	}

	Engine engine(window);

	engine.start();

	return 0;
}