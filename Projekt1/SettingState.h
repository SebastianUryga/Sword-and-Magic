#pragma once

#include "GuiHandler.h"



class SettingState :
	public State
{
private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::map<std::string, Button*> buttons;

	// Functions
	void initBackground();
	void initKeybinds();
	void initButtons();

public:
	SettingState(StateData * state_data);
	virtual ~SettingState();

	// Accesors

	// Functions

	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

