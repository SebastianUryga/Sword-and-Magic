#include "pch.h"
#include "IntObject.h"


IntObject::IntObject()
{
}


IntObject::~IntObject()
{
}

bool IntObject::contains(sf::Vector2f pos)
{
	return shape.contains(pos);
}
