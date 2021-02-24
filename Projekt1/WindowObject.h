#pragma once
#include "Button.h"

class WindowObject
{
public:

	sf::RectangleShape background;

	sf::Vector2i mousePos;
	sf::Font font;
	WindowObject(float x, float y, float width, float height, sf::Font& font);
	virtual ~WindowObject();


	void deactivate();
	void activate();

	void close();

	virtual void OnMouseLeftButtonClick();

	virtual void update(const sf::Vector2i mousePos);
	virtual void render(sf::RenderTarget* target);
};

