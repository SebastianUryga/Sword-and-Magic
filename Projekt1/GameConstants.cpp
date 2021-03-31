#include "pch.h"
#include "GameConstants.h"
#include "Direction.h"
uint16_t visitDir1 = DIRECTION_BOTTOM_ROW | DIRECTION_CENTER_ROW;
uint16_t visitDir2 = DIRECTION_ALL;

std::map<std::pair<Obj, int>, MapObjectParametrs> mapObjectsStats{
	{{Obj::STABLES,0}, {"Stabels",3,2,{ {2,4,1},{1,4,1} },6,visitDir1,false}} ,
	{{Obj::TAVERN,0}, {"Tavern",3,4,{ {4,2,1},{1,1,1},{1,1,1},{1,1,1}},7,visitDir1,true}},
	{{Obj::TRADING_POST,0}, {"Trading Post",3,3, { {2,4,1}, {1,1,1}, {1,1,1} },7,visitDir1,false}},
	{{Obj::MOUNTS,0}, {"Mounts",4,3, { {1,4,4,1},{4,4,4,1},{1,1,1,1} },0,0,false}},
	{{Obj::MOUNTS,1}, {"Mounts",4,2, { {1,4,4,1},{1,1,4,4} },0,0,false}},
	{{Obj::CRATER,0}, {"Crater",2,2, { {4,4},{4,4} },0,0,false}},
	{{Obj::DIRT_HILLS, 0}, {"Dirt Hills",2,2, { {4,4},{1,1} },0,0,false }},
	{{Obj::DIRT_HILLS, 1}, { "Dirt Hills",2,2, { {4,4},{1,1} },0,0,false }},
	{{Obj::DIRT_HILLS, 2}, {"Dirt Hills",2,2, { {4,4},{1,1} },0,0,false }},
	{{Obj::DIRT_HILLS, 3}, {"Dirt Hills",2,2, { {4,4},{1,1} },0,0,false }},
	{{Obj::ARENA,0}, {"Arena",3,3,{ {4,2,4},{4,4,4},{1,1,1} },0,visitDir1,false}},
	{{Obj::TOWN_WALL,0}, {"Wall",12,7,{ {4,4,4,4,4,1,4,4,4,4,4,1},{4,1,1,1,1,1,1,1,1,1,4,1},
	{4,1,1,1,1,1,1,1,1,1,4,1},{4,1,1,1,1,1,1,1,1,1,4,1},{4,1,1,1,1,1,1,1,1,1,4,1},
	{4,1,1,1,1,1,1,1,1,1,4,1},{1,1,1,1,1,1,1,1,1,1,1,1}},0,visitDir1,false}},
	{{Obj::DWELLING,Dwelling::Guardhouse}, 
	{"Guardhouse",3,3, { {2,4,1} ,{1,1,1}, {1,1,1} },0,visitDir1,false}},
	{{Obj::DWELLING, Dwelling::ArchersTower},
	{"Archers Tower",3,3, { {4,2,1} ,{1,1,1}, {1,1,1} },0,visitDir1,false}},
	{{Obj::DWELLING,Dwelling::GriffinTower},
	{"Grifin Tower",3,3, { {2,4,1} ,{1,1,1}, {1,1,1} },0,visitDir1,false}},
	{{Obj::DWELLING,Dwelling::Barracks},
	{"Barracks",3,3, { {2,4,1} ,{1,1,1}, {1,1,1} },0,visitDir1,false}}

};

