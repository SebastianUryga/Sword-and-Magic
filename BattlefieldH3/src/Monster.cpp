#include "Monster.h"

std::map<Monster, std::string> creatureToString = {
	{Monster::NO_CREATURE,"No Creature"},
	{Monster::PIKEMAN,"Pikeman"},
	{Monster::HALBERDIER,"Halberdier"},
	{Monster::SWORDSMAN,"Swordsman"},
	{Monster::CRUSADER,"Crusader"},
	{Monster::ARCHER,"Archer"},
	{Monster::MARKSMEN,"Marsman"},
	{Monster::GRIFFIN,"Griffin"},
	{Monster::ROYAL_GRIFFIN,"Royal Griffin"},
	{Monster::MONK,"Monk"},
	{Monster::ZEALOT,"Zealot"},
	{Monster::CAVALIER,"Cavalier"},
	{Monster::ANGEL,"Angel"},
	{Monster::MINOTAUR,"Minotaur"},
	{Monster::ORK2,"Ork with sword"},
	{Monster::ORK1,"Ork with hammer"},
	{Monster::ORK3,"Ork with axe"},
	{Monster::TROLL1,"Mountain Troll"},
	{Monster::TROLL2,"Stone Troll"},
	{Monster::TROLL3,"Cave Troll"},
	{Monster::KNIGHT1,"Sperman"},
	{Monster::KNIGHT2,"Axeman"},
	{Monster::KNIGHT3,"Swordsman"},
	{Monster::ELF1,"Elf archer"},
	{Monster::ELF2,"Elf warrior"},
	{Monster::ELF3,"Elf wizard"},
};
std::map<Monster, MonsterStats> creaturesStats = {
	{Monster::NO_CREATURE,{{1,1},0,0,0,0,0,0,0.f,0.f,false,false,false}},
	{Monster::PIKEMAN,{{1,1},5,5,4,1,0,15,60.f,0.4f,false,false,false}},
	{Monster::HALBERDIER,{{1,1},5,6,6,1,0,20,60.f,0.5f,false,false,false}},
	{Monster::SWORDSMAN,{{1,1},7,10,8,4,0,35,60.f,0.6f,false,false,false}},
	{Monster::CRUSADER,{{1,1},8,12,10,4,0,35,60.f,0.7f,false,false,false}},
	{Monster::ARCHER,{{1,1},4,5,3,2,12,15,50.f,0.25f,false,true,false}},
	{Monster::MARKSMEN,{{1,1},4,5,3,2,16,15,50.f,0.35f,false,true,false}},
	{Monster::GRIFFIN,{{1,1},6,8,6,3,0,35,130.f,0.6f,true,false,true }},
	{Monster::ROYAL_GRIFFIN,{{1,1},6,9,9,3,0,40,140.f,0.7f,true,false,true }},
	{Monster::MONK,{{1,1},7,10,5,5,14,20,40.f,0.30f,false,true,false }},
	{Monster::ZEALOT,{{1,1},7,10,5,5,14,20,40.f,0.30f,false,true,false }},
	{Monster::CAVALIER,{{1,1},11,13,10,6,0,60,90.f,0.5f,false,false,true }},
	{Monster::ANGEL,{{1,1},18,16,13,7,0,100,130.f,0.4f,true,false,false }},
	{Monster::MINOTAUR,{{1,1},13,10,8,5,0,50,70.f,0.3f,false,false,false }},
	{Monster::BLACK_DRAGON,{{1,1},12,17,12,7,0,180,170.f,0.9f,true,false,true }},
	{Monster::ORK3,{{2,2},5,7,8,3,0,24,50.f,0.7f,false,false,false }},
	{Monster::ORK2,{{2,2},6,4,5,3,0,20,70.f,0.6f,false,false,false }},
	{Monster::ORK1,{{2,2},6,4,8,3,0,25,60.f,0.55f,false,false,false }},
	{Monster::TROLL1,{{3,2},12,12,6,3,0,65,40.f,0.2f,false,false,false }},
	{Monster::TROLL2,{{3,2},8,12,5,3,0,60,50.f,0.3f,false,false,false }},
	{Monster::TROLL3,{{3,2},9,12,8,3,0,40,45.f,0.25f,false,false,false }},
	{Monster::KNIGHT1,{{2,2},3,7,14,3,0,31,60.f,0.7f,false,false,false }},
	{Monster::KNIGHT2,{{2,2},6,4,15,3,0,25,40.f,0.4f,false,false,false }},
	{Monster::KNIGHT3,{{2,2},5,4,12,3,0,25,90.f,0.55f,false,false,false }},
	{Monster::ELF1,{{2,2},4,7,5,3,7,10,60.f,0.3f,false,true,false }},
	{Monster::ELF2,{{2,2},5,3,5,3,0,25,90.f,0.6f,false,false,false }},
	{Monster::ELF3,{{2,2},6,9,2,3,4,12,70.f,0.24f,false,true,false }}
};
std::map < Monster, sf::Vector2f > creatureTexturesOffest = {
	{Monster::ORK3, sf::Vector2f(123, 180)},
	{Monster::ORK2, sf::Vector2f(123, 180)},
	{Monster::ORK1, sf::Vector2f(123, 180)},
	{Monster::TROLL1, sf::Vector2f(105, 290)},
	{Monster::TROLL2, sf::Vector2f(105, 290)},
	{Monster::TROLL3, sf::Vector2f(105, 290)},
	{Monster::KNIGHT1, sf::Vector2f(120, 170)},
	{Monster::KNIGHT2, sf::Vector2f(103, 190)},
	{Monster::KNIGHT3, sf::Vector2f(103, 190)},
	{Monster::ELF1, sf::Vector2f(95, 180)},
	{Monster::ELF2, sf::Vector2f(85, 200)},
	{Monster::ELF3, sf::Vector2f(175, 190)}
};
float attackTime = 0.8f;
float moveTime = 0.8f;
float moveTimeAngel = 0.9f;
float shootTime = 1.f;
std::map<std::pair<Monster, std::string>, MonsterAnimationParametrs> animationParametrs{
	{{Monster::PIKEMAN,"IDLE"},{3.f,0,0,7,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"START_MOVE"},{moveTime,4,1,1,1,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"MOVE1"},{moveTime,0,1,3,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"MOVE2"},{moveTime,4,1,1,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"ATTACK_UP"},{attackTime,0,3,5,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"ATTACK"},{attackTime,0,4,5,0,132,130,{15,73},50}},
	{{Monster::PIKEMAN,"ATTACK_DOWN"},{attackTime,0,5,5,0,132,130,{29,73},50}},
	{{Monster::PIKEMAN,"DIE"},{2.f,0,2,4,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"DAMAGED"},{0.6f,0,6,5,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"BLOCK"},{0.9f,0,7,4,0,88,130,{18,73},50}},
	{{Monster::PIKEMAN,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::HALBERDIER,"IDLE"},{3.f,0,0,8,0,62,130,{6,73},50}},
	{{Monster::HALBERDIER,"START_MOVE"},{moveTime,12,0,2,1,62,130,{6,73},50}},
	{{Monster::HALBERDIER,"MOVE1"},{moveTime,9,0,2,0,62,130,{6,73},50}},
	{{Monster::HALBERDIER,"MOVE2"},{moveTime,12,0,2,0,62,130,{6,73},50}},
	{{Monster::HALBERDIER,"ATTACK_UP"},{attackTime,0,2,5,0,105,130,{14,73},50}},
	{{Monster::HALBERDIER,"ATTACK"},{attackTime,0,2,5,0,105,130,{6,73},50}},
	{{Monster::HALBERDIER,"ATTACK_DOWN"},{attackTime,0,3,6,0,105,130,{34,73},50}},
	{{Monster::HALBERDIER,"DIE"},{2.f,11,3,2,0,70,130,{18,73},50}},
	{{Monster::HALBERDIER,"DAMAGED"},{0.6f,9,2,5,0,70,130,{18,73},50}},
	{{Monster::HALBERDIER,"BLOCK"},{0.9f,9,1,4,0,70,130,{6,73},50}},
	{{Monster::HALBERDIER,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},

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
	{{Monster::ARCHER,"MOVE2"},{moveTime,0,5,4,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK_UP"},{1.f,6,2,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK"},{1.f,6,1,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"ATTACK_DOWN"},{1.f,6,3,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT_UP"},{shootTime,0,2,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT"},{shootTime,0,1,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"SHOT_DOWN"},{shootTime,0,3,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"BLOCK"},{0.9f,6,4,5,0,104,100,{18,50},50}},
	{{Monster::ARCHER,"DIE"},{1.f,6,6,5,0,104,100,{18,50},50}},/*
	{{Monster::ARCHER,"TURN"},{2.f,0,254,3,0,104,100,{18,45,50,50}}},*/
	{{Monster::ARCHER,"DAMAGED"},{0.7f,6,5,5,0,104,100,{18,50},50}},

	{{Monster::MARKSMEN,"IDLE"},{1.f,0,0,8,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"START_MOVE"},{moveTime,0,4,2,0,104,100,{18,50},50} },
	{{Monster::MARKSMEN,"MOVE1"},{moveTime,3,4,3,0,104,100,{18,50},50} },
	{{Monster::MARKSMEN,"MOVE2"},{moveTime,0,5,3,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK_UP"},{1.f,6,2,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK"},{1.f,6,1,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"ATTACK_DOWN"},{1.f,6,3,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT_UP"},{shootTime,0,2,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT"},{shootTime,0,1,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"SHOT_DOWN"},{shootTime,0,3,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"DIE"},{1.f,6,6,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"BLOCK"},{0.9f,6,4,5,0,104,100,{18,50},50}},
	{{Monster::MARKSMEN,"DAMAGED"},{0.7f,6,5,5,0,104,100,{18,50},50}},

	{{Monster::GRIFFIN,"IDLE"},{1.f,0,0,5,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"START_MOVE"},{moveTime,0,1,2,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"END_MOVE"},{moveTime,6,1,1,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"MOVE1"},{moveTime,3,1,2,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"MOVE2"},{moveTime,0,2,0,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"ATTACK_UP"},{attackTime,2,2,5,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"ATTACK"},{attackTime,1,3,6,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"ATTACK_DOWN"},{attackTime,0,4,7,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"DIE"},{1.f,0,6,7,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"DAMAGED"},{0.7f,0,5,4,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"BLOCK"},{1.5f,2,7,2,0,165,124,{70,70},0}},
	{{Monster::GRIFFIN,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::GRIFFIN,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::GRIFFIN,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::ROYAL_GRIFFIN,"IDLE"},{1.f,0,0,5,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"END_MOVE"},{moveTime,6,1,1,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"START_MOVE"},{0.8f,0,1,2,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"MOVE1"},{moveTime,3,1,2,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"MOVE2"},{moveTime,4,1,0,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"ATTACK_UP"},{attackTime,0,2,5,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"ATTACK"},{attackTime,0,3,6,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"ATTACK_DOWN"},{attackTime,0,4,7,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"DIE"},{1.f,0,6,7,0,224,166,{94,84},0}},
	{{Monster::ROYAL_GRIFFIN,"DAMAGED"},{0.7f,0,5,4,0,224,166,{98,84},0}},
	{{Monster::ROYAL_GRIFFIN,"BLOCK"},{1.5f,0,7,2,0,224,166,{101,84},0}},
	{{Monster::ROYAL_GRIFFIN,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ROYAL_GRIFFIN,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ROYAL_GRIFFIN,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},

	{ {Monster::ZEALOT,"IDLE"},{1.f,0,0,6,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"START_MOVE"},{moveTime,0,1,0,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"MOVE1"},{moveTime,1,1,2,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"MOVE2"},{moveTime,4,1,1,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"ATTACK_UP"},{1.f,0,3,6,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"ATTACK"},{1.f,0,4,5,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"ATTACK_DOWN"},{1.f,0,5,7,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"SHOT_UP"},{shootTime,0,8,2,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"SHOT"},{shootTime,3,8,2,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"SHOT_DOWN"},{shootTime,5,6,2,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"BLOCK"},{0.9f,1,2,4,0,92,128,{18,60},50} },
	{ {Monster::ZEALOT,"DIE"},{1.f,0,7,5,0,92,128,{18,60},50} },/*
	{{Monster::ARCHER,"TURN"},{2.f,0,254,3,0,104,100,{18,45,50,50}}},*/
	{ {Monster::ZEALOT,"DAMAGED"},{0.7f,0,6,4,0,92,128,{18,60},50} },

	{{Monster::CAVALIER,"IDLE"},{1.f,0,0,8,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"START_MOVE"},{moveTime,0,7,3,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"MOVE1"},{moveTime,3,7,4,1,177,120,{60,70},0}},
	{{Monster::CAVALIER,"MOVE2"},{moveTime,0,8,5,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"ATTACK_UP"},{attackTime,0,2,7,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"ATTACK"},{attackTime,0,1,7,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"ATTACK_DOWN"},{attackTime,0,3,7,0,177,120,{60,54},0}},
	{{Monster::CAVALIER,"DIE"},{1.f,0,4,7,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"DAMAGED"},{0.7f,0,6,4,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"BLOCK"},{0.9f,0,5,3,0,177,120,{60,70},0}},
	{{Monster::CAVALIER,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::CAVALIER,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::CAVALIER,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},

	{{Monster::ANGEL,"IDLE"},{1.f,0,0,4,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"START_MOVE"},{moveTimeAngel,0,8,1,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"MOVE1"},{moveTimeAngel,2,8,3,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"MOVE2"},{moveTimeAngel,0,9,2,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK_UP"},{attackTime,0,3,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK"},{attackTime,0,2,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"ATTACK_DOWN"},{attackTime,0,4,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"DIE"},{1.f,0,6,5,0,140,130,{45,78},50}},
	{{Monster::ANGEL,"DAMAGED"},{0.7f,0,5,5,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"BLOCK"},{0.9f,0,7,3,0,130,130,{40,78},50}},
	{{Monster::ANGEL,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ANGEL,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::ANGEL,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},
	
	{{Monster::MINOTAUR,"IDLE"},{1.f,0,0,7,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"START_MOVE"},{moveTime,0,1,2,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"MOVE1"},{moveTime,3,1,2,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"MOVE2"},{moveTime,0,1,2,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"ATTACK_UP"},{attackTime,0,3,5,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"ATTACK"},{attackTime,0,4,5,0,104,118,{5,60},50}},
	{{Monster::MINOTAUR,"ATTACK_DOWN"},{attackTime,0,5,5,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"DIE"},{1.f,0,7,6,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"DAMAGED"},{0.7f,0,6,6,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"BLOCK"},{0.9f,2,2,3,0,104,118,{30,60},50}},
	{{Monster::MINOTAUR,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::MINOTAUR,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::MINOTAUR,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}},
	
	{{Monster::BLACK_DRAGON,"IDLE"},{1.f,0,0,5,0,114,172,{60,80},0}},
	{{Monster::BLACK_DRAGON,"START_MOVE"},{moveTime,0,1,2,0,188,172,{80,80},0}},
	{{Monster::BLACK_DRAGON,"MOVE1"},{moveTime,3,1,1,0,188,172,{80,80},0}},
	{{Monster::BLACK_DRAGON,"MOVE2"},{moveTime,5,1,1,0,188,172,{80,80},0}},
	{{Monster::BLACK_DRAGON,"ATTACK_UP"},{attackTime,0,3,7,0,220,172,{100,80},0}},
	{{Monster::BLACK_DRAGON,"ATTACK"},{attackTime,0,4,5,0,220,172,{100,80},0}},
	{{Monster::BLACK_DRAGON,"ATTACK_DOWN"},{attackTime,0,5,9,0,220,172,{100,80},0}},
	{{Monster::BLACK_DRAGON,"DIE"},{1.f,4,2,6,0,188,172,{90,80},0}},
	{{Monster::BLACK_DRAGON,"DAMAGED"},{0.7f,0,2,4,0,188,172,{100,80},0}},
	{{Monster::BLACK_DRAGON,"BLOCK"},{0.9f,5,0,5,0,188,172,{120,80},0}},
	{{Monster::BLACK_DRAGON,"SHOT_UP"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::BLACK_DRAGON,"SHOT"},{0,0,0,0,0,0,0,{0,0},0}},
	{{Monster::BLACK_DRAGON,"SHOT_DOWN"},{0,0,0,0,0,0,0,{0,0},0}}
};