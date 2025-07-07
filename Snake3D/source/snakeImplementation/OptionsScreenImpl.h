#ifndef OPTIONSSCREENIMPL_H
#define OPTIONSSCREENIMPL_H

#include "Options/OptionsScreen.h"

class SelectLevelScreen;

class OptionsScreenImpl : public OptionsScreen
{

	bool soundsMuted = false;

	int choosenDifficulty;
	int difficultyMIN;
	int difficultyMAX;

	int choosenMouseSensitivity;
	float minimumMouseSensitivity;
	float mouseSensitivityStep;
	int mouseSensitivityMIN;
	int mouseSensitivityMAX;

	void playClick();
	void playSwitch();

	void loadDifficultyFromFile();
	void loadMouseSensitivityFromFile();

	void chooseSelectedOption();

public:
//	using OptionsScreen::OptionsScreen;
	OptionsScreenImpl(GameMenu* menu);

	virtual void render() override;
	virtual void update(float deltaTime) override;

	void saveOptions();

	virtual void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)  override;
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)  override;

	bool areSoundsMuted();

	friend class SelectLevelScreen;
};

#endif