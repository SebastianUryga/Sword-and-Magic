#include "pch.h"
#include "Fraction.h"

std::map<BuildingID, BuildingStats> buildingStats{
	{NONE,{0,"None",Obj::DIRT_HILLS,0,NONE}},{TAVERN,{500,"Tavern",Obj::TAVERN,0,NONE}},
	{FORT,{5000,"Fort",Obj::TOWN,TownLevel::Fort,CITADEL}}, 
	{CITADEL,{2500,"Citadel",Obj::TOWN,TownLevel::Citadel,CASTLE}},
	{CASTLE,{5000,"Castle",Obj::TOWN,TownLevel::Castle,NONE}},
	{GUARDHOUSE,{1000,"Guardhouse",Obj::DWELLING,Dwelling::Guardhouse,NONE}},
	{ARCHER_TOWER,{2000,"Archers Tower",Obj::DWELLING,Dwelling::ArchersTower,NONE}},
	{GRIFFIN_TOWER,{3000,"Griffin Tower",Obj::DWELLING,Dwelling::GriffinTower,NONE}},
	{BARACKS,{3000,"Baracks",Obj::DWELLING,Dwelling::Barracks,NONE}}
};

