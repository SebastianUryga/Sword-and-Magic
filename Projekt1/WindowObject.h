#pragma once
#include "Button.h"
#include "GarrnisonInterface.h"

class WindowObject
{
public:

	sf::RectangleShape background;

	std::vector<std::shared_ptr<IntObject>> interactiveElem;
	std::map<std::string, std::shared_ptr<Button>> buttons;
	std::vector<sf::Text> texts;

	bool active;
	sf::Vector2i mousePos;
	sf::Font font;
	WindowObject(float x, float y, float width, float height, sf::Font& font);
	virtual ~WindowObject();
	void addText(std::string text, sf::Vector2f pos);

	void deactivate();
	void activate();
	void setPos(float x, float y);
	void close();

	virtual void update(const float dt, const sf::Vector2i mousePos);
	virtual void render(sf::RenderTarget* target);
};

