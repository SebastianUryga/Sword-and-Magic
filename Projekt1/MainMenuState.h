#pragma once
#include "EditorState.h"


class MainMenuState :
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
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	// Functions

	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

