#pragma once
#include "GuiHandler.h"
#include "BattleHandler.h"

class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::Font* font;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::map<std::string, int> supportedKeys;

	//Initialaizer
	void initWindow();
	void initFonts();
	void initKeys();
	void initTextures();

	void refresh();
public:
	Game();
	virtual ~Game();
	// Functions
	void mainMenuState();
	void settingState();
	void gameState();
	void campainState();
	void editorState();
	void endApplication();

	void render();

	//update
	void updateDt();
	void updateEvents();
	void updateMousePos();
	void update();

	void run();
};

