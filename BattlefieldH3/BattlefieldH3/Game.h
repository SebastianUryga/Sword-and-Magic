#pragma once
#include "WindowObject.h"
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
public:
	Game();
	virtual ~Game();
	// Functions
	void mainMenuState();
	void settingState();
	void gameState();
	void editorState();
	void endApplication();

	void render();

	//update
	void updateDt();
	void updateEvents();
	void update();

	void run();
};

