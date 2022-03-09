#pragma once
#include "WindowObject.h"
class MainMenu : public WindowObject
{
private:
	void initBackgroud();
	void initButtons();
public:
	MainMenu(const sf::Vector2f& windowSize);
	virtual ~MainMenu();
};

