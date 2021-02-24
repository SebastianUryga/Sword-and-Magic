#pragma once
#include "Direction.h"
class Kingdom
{
private:
	int	color;
	int race;
	//Funds resorce;
	//std::vector<HeroInstance> heroes;
	//std::vector<Castle> castles;
	//std::list<int> vistedObjectindex;

public:

	void init(int color);
	void clear();
	Kingdom();
	virtual ~Kingdom();

	bool isVisited(int object) const;

	//Accesors
	int getColor() const;
	int getRace() const;

};

