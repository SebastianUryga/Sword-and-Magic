#pragma once
#include "interface_gamearea.h"
#include "SettingState.h"
#include "MapObject.h"

class GuiHandler;

class GameState :
	public State
{
private:
	sf::View view;
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
	void handleButtonsArea();
	void setCurrentColor(int color);
	void setToNextColor();
	void OnMouseLeftButtonClick() override;
	// Functions

	//void OpenHeroesDialog(Heroes & hero);
	//void OpenCastleDialog(Castle &);
	void calculatePaths(const HeroInstance *hero);

	void updateView();
	void updateEvents();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

