#pragma once
#include "GameConstants.h"
class Fraction
{
public:
	enum FractionType
	{
		None,
		Random,
		Castle,
		Rampart,
		Fort,
		Inferno,
		Necropolis,
		Dungeon,
	};
	FractionType type;
	Fraction(Fraction& other) : type(other.type) {}
	Fraction(FractionType& type) : type(type) {}
	explicit Fraction(int type) : type(static_cast<FractionType>(type)) {}
	bool operator==(Fraction& other) { return other.type == this->type; }
	Fraction& operator=(const Fraction & other) { this->type = other.type; return *this; }
	Fraction& operator=(const FractionType & type) { this->type = type; return *this; }
	operator FractionType() const { return type; }
	Fraction() {}
};

enum BuildingID
{
	NONE = -1,
	TAVERN,
	FORT,
	CITADEL,
	CASTLE,
	VILLAGE_HALL,
	TOWN_HALL,
	CAPITOL,
	WALLS,
	GUARDHOUSE,
	ARCHER_TOWER,
	GRIFFIN_TOWER,
	BARACKS,
};
struct  BuildingStats
{
	int cost;
	std::string name;
	Obj type;
	int subType;
	BuildingID upgrade;
};

extern std::map<BuildingID, BuildingStats> buildingStats;