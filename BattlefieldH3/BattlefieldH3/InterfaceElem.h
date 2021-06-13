#pragma once
#include "pch.h"
// Base User Interface element
class GuiHandler;

class InterfaceElem
{
public:
	InterfaceElem();
	~InterfaceElem();

	sf::FloatRect shape;

	std::map<sf::Mouse::Button, bool> currentMouseState;
	void updateMouseState(sf::Mouse::Button btn, bool state) { currentMouseState[btn] = state; }
	bool mouseState(sf::Mouse::Button btn) const { return currentMouseState.count(btn) ? currentMouseState.at(btn) : false; }
	virtual bool contains(sf::Vector2f pos);
	virtual void keyPressed(const sf::Keyboard& key) {}

	virtual void clickLeft(bool down, bool previousState) {}
	virtual void clickRight(bool down, bool previousState) {}
	virtual void hover(bool on) {}

	friend class GuiHandler;
};

