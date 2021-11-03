#include "GuiHandler.h"


InterfaceElem::InterfaceElem()
{
}


InterfaceElem::~InterfaceElem()
{
}

bool InterfaceElem::contains(const sf::Vector2f & pos)
{
	return shape.contains(pos);
}
