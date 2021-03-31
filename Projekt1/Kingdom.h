#pragma once
#include "World.h"

class HeroInstance;
class TownInstance;
namespace MP2
{
	class ObjectInstance;
}

class Kingdom
{
private:
	int	color;
	Fraction race;
	int money;
	//Funds resorce;
	
	//std::list<int> vistedObjectindex;

public:
	std::vector<HeroInstance*> heroes;
	std::vector<TownInstance*> castles;

	void init(int color);
	void clear();

	Kingdom();
	virtual ~Kingdom();

	bool isVisited(int object) const;

	void spendMoney(int cost);

	bool containsHero(const HeroInstance* h);
	bool containsTown(const TownInstance* h);
	//Accesors

	int getColor() const;
	int getRace() const;
	int getMoney() const;

};

