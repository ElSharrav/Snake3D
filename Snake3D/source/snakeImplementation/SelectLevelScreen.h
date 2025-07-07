#ifndef SELECTLEVELSCREEN_H
#define SELECTLEVELSCREEN_H

#include "Options/OptionsScreen.h"
#include "MapNames.h"

class SelectLevelScreen : public OptionsScreen
{
	
public:
	SelectLevelScreen(GameMenu* menu, std::string levelsListPath);

	virtual void render() override;
	virtual void update(float deltaTime) override;

	virtual void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)  override;
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)  override;

	void enterScreen(std::string levelsListPath);

	MapNames mapNames;
};

#endif