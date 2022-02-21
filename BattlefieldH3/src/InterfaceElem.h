#pragma once
#include "PCH.hpp"
// Base User Interface element
class GuiHandler;

class InterfaceElem
{
public:
	InterfaceElem();
	~InterfaceElem();

	sf::FloatRect shape;

	std::map<sf::Mouse::Button, bool> currentMouseState;
	void updateMouseState(sf::Mouse::Button btn, bool state);
	bool mouseState(sf::Mouse::Button btn) const;
	virtual bool contains(sf::Vector2f pos);
	virtual void keyPressed([[maybe_unused]] const sf::Keyboard& key);

	virtual void clickLeft([[maybe_unused]] bool down, [[maybe_unused]] bool previousState);
	virtual void clickRight([[maybe_unused]] bool down, [[maybe_unused]] bool previousState);
	virtual void hover([[maybe_unused]] bool on);

	friend class GuiHandler;
};
