#include "InterfaceElem.h"


InterfaceElem::InterfaceElem()
{
}


InterfaceElem::~InterfaceElem()
{
}

void InterfaceElem::updateMouseState(sf::Mouse::Button btn, bool state)
{
	currentMouseState[btn] = state;
}

bool InterfaceElem::mouseState(sf::Mouse::Button btn) const
{
	return currentMouseState.count(btn) ? currentMouseState.at(btn) : false;
}

bool InterfaceElem::contains(sf::Vector2f pos)
{
	return shape.contains(pos);
}

void InterfaceElem::keyPressed(const sf::Keyboard& key)
{
}

void InterfaceElem::clickLeft(bool down, bool previousState)
{
}

void InterfaceElem::clickRight(bool down, bool previousState)
{
}

void InterfaceElem::hover(bool on)
{
}
