#include "pch.h"
#include "Monster.h"

MonsterStats monsterStats[] = {
	{0,0,0,0,false,false},
	{5,5,1,10,false,false},
	{11,10,4,35,false,false},
	{5,3,1,10,false,true},
	{4,3,1,5,false,false}
};


std::map<std::pair<Monster, std::string>, MonsterAnimationParametrs> animationParametrs {
	{{Monster::PIKEMAN,"IDLE"},{10.f,23,0,8,0,88,121,false}},
	{{Monster::PIKEMAN,"MOVE"},{2.f,23,139,6,0,88,121,false}},
	{{Monster::PIKEMAN,"ATTACK_UP"},{2.f,23,373,6,0,88,133,false}},
	{{Monster::PIKEMAN,"ATTACK"},{2.f,23,506,6,0,132,133,false}},
	{{Monster::PIKEMAN,"ATTACK_DOWN"},{2.f,18,625,6,0,132,133,false}},
	{{Monster::PIKEMAN,"DIE"},{2.f,23,254,5,0,88,121,false}},
	{{Monster::PIKEMAN,"TURN"},{2.f,463,254,3,0,88,121,false}},
	{{Monster::PIKEMAN,"DAMAGED"},{2.f,23,737,6,0,88,121,false}},
	{{Monster::PIKEMAN,"SHOT"},{0,0,0,0,0,0,false}}
};