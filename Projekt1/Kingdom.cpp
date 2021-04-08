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
	this->money = 20000;

}

void Kingdom::clear()
{
	this->color = Color::NONE;
}

Kingdom::Kingdom() : color(Color::NONE),race(Fraction::Castle),money(300)
{
}


Kingdom::~Kingdom()
{
}

bool Kingdom::isVisited(int object) const
{
	return false;
}

void Kingdom::spendMoney(int cost)
{
	this->money -= cost;
}

bool Kingdom::containsHero(const HeroInstance * h)
{
	if (std::find(heroes.begin(), heroes.end(), h) != heroes.end())
		return true;
	else
		return false;
}

bool Kingdom::containsTown(const TownInstance * h)
{
	if (std::find(castles.begin(), castles.end(), h) != castles.end())
		return true;
	else
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

int Kingdom::getMoney() const
{
	return money;
}
