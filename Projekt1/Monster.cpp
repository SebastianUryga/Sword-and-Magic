#include "pch.h"
#include "Monster.h"

std::map<Monster, MonsterStats> creaturesStats = {
	{Monster::NO_CREATURE,{0,0,0,0,0.f,0.f,false,false,false}},
	{Monster::PIKEMAN,{5,5,1,10,50.f,0.4f,false,false,false}},
	{Monster::HALBERDIER,{6,7,1,10,60.f,0.5f,false,false,false}},
	{Monster::SWORDSMAN,{10,8,4,35,70.f,0.6f,false,false,false}},
	{Monster::CRUSADER,{12,10,4,35,70.f,0.7f,false,false,false}},
	{Monster::ARCHER,{5,3,2,10,50.f,0.3f,false,true,false}},
	{Monster::MARKSMEN,{5,4,2,10,50.f,0.45f,false,true,false}},
	{Monster::GRIFFIN,{ 9,9,3,25,80.f,0.7f,true,false,true }},
	{Monster::ANGEL,{ 18,18,7,160,90.f,0.5f,true,false,false }}
};
float attackTime = 0.8f;
float moveTime = 0.8f;
std::map<std::pair<Monster, std::string>, MonsterAnimationParametrs> animationParametrs {
	{{Monster::PIKEMAN,"IDLE"},{3.f,0,0,7,0,88,121,{23,73},50}},
	{{Monster::PIKEMAN,"MOVE"},{2.f,0,1,6,0,88,121,{23,73},50}},
	{{Monster::PIKEMAN,"ATTACK_UP"},{2.f,0,2,6,0,88,133,{23,73},50}},
	{{Monster::PIKEMAN,"ATTACK"},{2.f,0,4,4,0,132,133,{18,73},50}},
	{{Monster::PIKEMAN,"ATTACK_DOWN"},{2.f,0,5,6,0,132,133,{23,73},50}},
	{{Monster::PIKEMAN,"DIE"},{2.f,0,2,5,0,88,121,{23,73},50}},
	{{Monster::PIKEMAN,"TURN"},{2.f,3,2,3,0,88,121,{23,73},50}},
	{{Monster::PIKEMAN,"DAMAGED"},{0.6f,0,6,6,0,88,121,{23,73},50}},
	{{Monster::PIKEMAN,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::SWORDSMAN,"IDLE"},{1.f,0,0,8,0,50,125,{0,62},50}},
	
	{{Monster::SWORDSMAN,"START_MOVE"},{moveTime,0,7,3,1,140,125,{60,62},50}},
	{{Monster::SWORDSMAN,"MOVE1"},{moveTime,3,7,2,1,140,125,{60,62},50}},
	{{Monster::SWORDSMAN,"MOVE2"},{moveTime,0,8,5,0,140,125,{60,62},50}},
	{{Monster::SWORDSMAN,"ATTACK_UP"},{attackTime,0,1,6,0,120,125,{23,62},50}},
	{{Monster::SWORDSMAN,"ATTACK"},{attackTime,0,2,6,0,120,125,{23,62},50}},
	{{Monster::SWORDSMAN,"ATTACK_DOWN"},{attackTime,0,3,6,0,120,125,{23,62},50}},
	{{Monster::SWORDSMAN,"DIE"},{1.f,0,4,5,0,140,125,{60,62},50}},/*/
	{{Monster::SWORDSMAN,"TURN"},{2.f,0,254,3,0,88,125,{30,62,50,50}}},*/
	{{Monster::SWORDSMAN,"DAMAGED"},{0.7f,0,5,5,0,140,125,{60,62},50}},
	{{Monster::SWORDSMAN,"BLOCK"},{0.9f,0,6,3,0,140,125,{60,62},50}},
	{{Monster::SWORDSMAN,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::SWORDSMAN,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::SWORDSMAN,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::CRUSADER,"IDLE"},{1.f,0,0,8,0,60,125,{0,62},50}},
	{{Monster::CRUSADER,"START_MOVE"},{moveTime,0,4,3,1,84,125,{4,62},50}},
	{{Monster::CRUSADER,"MOVE1"},{moveTime,3,4,2,1,84,125,{4,62},50}},
	{{Monster::CRUSADER,"MOVE2"},{moveTime,0,5,5,0,84,125,{4,62},50}},
	{{Monster::CRUSADER,"ATTACK_UP"},{attackTime,0,1,6,0,116,125,{13,62},50}},
	{{Monster::CRUSADER,"ATTACK"},{attackTime,0,2,6,0,116,125,{13,62},50}},
	{{Monster::CRUSADER,"ATTACK_DOWN"},{attackTime,0,3,6,0,116,125,{13,62},50}},
	{{Monster::CRUSADER,"DIE"},{1.f,0,7,5,0,122,125,{62,62},50}},
	{{Monster::CRUSADER,"DAMAGED"},{0.7f,0,6,5,0,122,125,{62,62},50}},
	{{Monster::CRUSADER,"BLOCK"},{0.9f,6,5,3,0,85,125,{27,62},50}},
	{{Monster::CRUSADER,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::CRUSADER,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::CRUSADER,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::ARCHER,"IDLE"},{1.f,0,0,8,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"START_MOVE"},{moveTime,0,4,2,0,104,100,{18,50},50} },
	{{Monster::ARCHER,"MOVE1"},{moveTime,3,4,2,0,104,100,{18,50},50} },
	{{Monster::ARCHER,"MOVE2"},{moveTime,0,5,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK_UP"},{1.f,6,2,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK"},{1.f,6,1,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK_DOWN"},{1.f,6,3,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT_UP"},{1.2f,0,2,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT"},{1.2f,0,1,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT_DOWN"},{1.2f,0,3,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"BLOCK"},{0.9f,6,4,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"DIE"},{1.f,6,6,5,0,104,100,{18,50},50}},/*
	{{Monster::ARCHER,"TURN"},{2.f,0,254,3,0,104,100,{18,45,50,50}}},*/
	{{Monster::ARCHER,"DAMAGED"},{0.7f,6,5,5,0,104,100,{18,50},50}},
	
	{{Monster::MARKSMEN,"IDLE"},{1.f,0,0,8,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"START_MOVE"},{moveTime,0,4,2,0,104,100,{18,50},50} },
	{{Monster::MARKSMEN,"MOVE1"},{moveTime,2,4,3,0,104,100,{18,50},50} },
	{{Monster::MARKSMEN,"MOVE2"},{moveTime,0,5,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK_UP"},{1.f,6,2,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK"},{1.f,6,1,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK_DOWN"},{1.f,6,3,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT_UP"},{1.2f,0,2,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT"},{1.2f,0,1,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT_DOWN"},{1.2f,0,3,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"DIE"},{1.f,6,6,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"BLOCK"},{0.9f,6,4,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"DAMAGED"},{0.7f,6,5,5,0,104,100,{18,50},50}},

	{{Monster::ANGEL,"IDLE"},{1.f,0,0,4,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"START_MOVE"},{moveTime,0,8,3,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"MOVE1"},{moveTime,3,8,2,1,130,130,{40,78},50}},
	{{Monster::ANGEL,"MOVE2"},{moveTime,0,9,3,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK_UP"},{attackTime,0,3,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK"},{attackTime,0,2,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK_DOWN"},{attackTime,0,4,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"DIE"},{1.f,0,6,5,0,140,130,{45,78},50}},
	{{Monster::ANGEL,"DAMAGED"},{0.7f,0,5,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"BLOCK"},{0.9f,0,7,3,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ANGEL,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ANGEL,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}}
};