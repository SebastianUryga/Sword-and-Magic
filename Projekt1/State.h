#include "pch.h"

class State;

class StateData
{
public:
	StateData(){}

	//Variables
	sf::RenderWindow* window;
	sf::Font* font;
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
};

class State
{
private:

protected:
	StateData* stateData;
	sf::RenderWindow* window;
	sf::Font* font;
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	bool quit;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosTile;
	bool mouseMoved;

	//Functions
	virtual void initKeybinds() = 0;
public:
	State(StateData* stateData);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	virtual void endState();
	virtual void OnMouseLeftButtonClick();
	virtual void OnMouseLeftButtonReleased();
	virtual void OnMouseRightButtonClick();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePositions(sf::View *view = nullptr);
	virtual void updateKeytime(const float& dt);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

