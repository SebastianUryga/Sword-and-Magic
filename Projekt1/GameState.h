#pragma once
#include "SettingState.h"

class GuiHandler;

class GameState :
	public State
{
private:
	sf::Event sfEvent;

	MP2::ObjectInstance* selection;

	int currentColorTurn;

	void initView();
	void initTextutres();
	void initKeybinds();
	void initPlayers();
	void initWorld();
	void initGameArea();
	void initButtonsArea();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//modifires
	void setCurrentColor(int color);
	void setToNextColor();
	void OnMouseLeftButtonClick() override;
	void endState() override;
	// Functions
	void calculatePaths(const HeroInstance *hero);

	
	void updateView();
	void updateEvents();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

