#include "pch.h"
#include "Kingdom.h"


void Kingdom::init(int color)
{
	clear();
	this->color = color;
	if (Color::ALL & color)
	{
		//heroes.reserve(8);
		//castles.reserve();
		//UpdateStartingResurse();
	}

}

void Kingdom::clear()
{
	this->color = Color::NONE;
}

Kingdom::Kingdom() : color(Color::NONE)
{
}


Kingdom::~Kingdom()
{
}

bool Kingdom::isVisited(int object) const
{
	return false;
}

int Kingdom::getColor() const
{
	return this->color;
}

int Kingdom::getRace() const
{
	return this->race;
}
