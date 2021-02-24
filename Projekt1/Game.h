#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include "MainMenuState.h"

class Game
{
private:
	//Variable
	StateData stateData;
	sf::RenderWindow* window;
	sf::Font* font;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialaizer
	void initWindow();
	void initFonts();
	void initKeys();
	void initStateData();
	void initState();
	void initTextures();
	
public:
	Game();
	virtual ~Game();

	// Functions

	void endApplication();

	void render();

	//update
	void updateDt();
	void updateEvents();
	void update();

	void run();
};

#endif // !GAME_H