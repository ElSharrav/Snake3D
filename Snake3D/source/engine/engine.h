#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "../glfw/Glfw.h"

#include "primitives/line.h"
#include "../snakeImplementation/board.h"
#include "../snakeImplementation/snakeHead.h"
#include "../snakeImplementation/Snake.h"
#include "../snakeImplementation/GameManager.h"
#include "camera/camera.h"
#include "colors/color.h"
#include "shaders/shaderProgram.h"

#include <glm/vec2.hpp>

class Game;

class Engine
{
	static Engine* callbacksHelperEngine;

	GameManager* gameManager;
	Game* game;

	glm::vec4 clearColor;

	Line yAxis;
	Line zAxis;
	Line xAxis;

	GLFWwindow* window;

	glm::vec2 screenSize;

	double lastFrameCursorPosX;
	double lastFrameCursorPosY;

	float deltaTime;
	float lastFrame;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void update();
	void render();

	void initializeAxes();
	void drawAxes();

public:
	Engine(GLFWwindow* window);
	~Engine();

	static GLFWwindow* createWindow(int width, int height, const std::string& title, GLFWmonitor* monitor = NULL);

	void start();

	void requestEngineClose();
	void compileAndLinkShader(ShaderProgram* shader, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	static glm::vec2 getWindowsScreenSize();

//	GETTER(GLFWwindow*, window);

	GLFWwindow* getwindow() { return this->window; }

//	GETTER(glm::vec2, screenSize);

	glm::vec2 getscreenSize() { return this->screenSize; }
};
#endif
