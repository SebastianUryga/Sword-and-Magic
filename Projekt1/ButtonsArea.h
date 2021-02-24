#pragma once
#include "Button.h"
#include "BorderWindow.h"
class ButtonsArea : public BorderWindow
{
private:
	Button* buttonEndTurn;
	Button* buttonSystem;

	sf::Font font;
	sf::RenderWindow* window;
	
	sf::Vector2f offsetPosition;
public:
	ButtonsArea();
	virtual ~ButtonsArea();

	// Functions
	void setPos(float x, float y);
	void move(float x, float y);
	void initBackground();
	void initButtons();
	void built(sf::Vector2f pos,sf::Font& font, sf::RenderWindow* window);

	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget *target);
};

