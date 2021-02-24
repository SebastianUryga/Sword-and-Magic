#pragma once
#include "Button.h"
class ControlPanel
{
private:
	sf::RectangleShape background;
	
	std::map<std::string, Button*> buttons;
public:
	ControlPanel();
	virtual ~ControlPanel();

	// Functions
	void setPos(int x, int y);

	void update();
	void render(sf::RenderTarget * target);
};

