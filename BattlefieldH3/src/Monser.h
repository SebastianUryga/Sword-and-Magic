#pragma once
#include "PCH.hpp"
struct MonsterStats
{
	sf::Vector2i size = { 1,1 };
	uint8_t damage = 1;
	uint8_t attack = 0;
	uint8_t defence = 0;
	uint8_t level = 1;
	uint8_t arrows = 0;
	uint16_t hp = 10;
	float speed = 50.f;
	float attackSpeed = 0.5;
	bool fly = false;
	bool archer = false;
	bool bigCreature = false;
};
struct MonsterAnimationParametrs
{
	float animationTimer;
	int start_frame_x;
	int start_frame_y;
	int frames_x;
	int frames_y;
	int width;
	int height;
	sf::Vector2f orgin;
	float tileWidth;
};

class Monster
{
public:
	enum MonsterType : int
	{
		NO_CREATURE = 0,

		PIKEMAN = 1,
		HALBERDIER = 2,
		ARCHER = 3,
		MARKSMEN = 4,
		GRIFFIN = 5,
		ROYAL_GRIFFIN = 6,
		SWORDSMAN = 7,
		CRUSADER = 8,
		MONK = 9,
		ZEALOT,
		CAVALIER = 11,
		ANGEL = 13,
		MINOTAUR = 14,
		BLACK_DRAGON = 15,

		ORK1 = 30,
		ORK2 = 31,
		ORK3 = 32,
		TROLL1 = 33,
		TROLL2 = 34,
		TROLL3 = 35,
		KNIGHT1 = 36,
		KNIGHT2 = 37,
		KNIGHT3 = 38,
		ELF1 = 39,
		ELF2 = 40,
		ELF3 = 41,
	};

	Monster(MonsterType type = NO_CREATURE) :
		monster(type)
	{}
	Monster(const Monster& other) :
		monster(other.monster)
	{}
	Monster& operator=(const Monster& other)
	{
		monster = other.monster;
		return *this;
	}
	explicit Monster(int type)
	{
		monster = static_cast<MonsterType>(type);
	}
	bool operator==(const Monster& other) const
	{
		return monster == other.monster;
	}
	bool operator<(const Monster& other) const
	{
		return monster < other.monster;
	}
	MonsterType monster;
};
extern std::map<Monster, std::string> creatureToString;
extern std::map<Monster, MonsterStats> creaturesStats;
extern std::map<Monster, sf::Vector2f> creatureTexturesOffest;

extern std::map<std::pair<Monster, std::string>, MonsterAnimationParametrs> animationParametrs;
static std::vector<Monster> allMonseters = {
	Monster::NO_CREATURE, Monster::PIKEMAN, Monster::HALBERDIER, Monster::SWORDSMAN, Monster::CRUSADER, Monster::ARCHER, Monster::MARKSMEN, Monster::GRIFFIN, Monster::ROYAL_GRIFFIN, Monster::MONK, Monster::ZEALOT, Monster::CAVALIER, Monster::ANGEL, Monster::MINOTAUR, Monster::BLACK_DRAGON
};
static std::vector<Monster> allMonseters2 = {
	Monster::NO_CREATURE, Monster::ORK1, Monster::ORK2, Monster::ORK3, Monster::TROLL1, Monster::TROLL2, Monster::TROLL3,
	Monster::KNIGHT1, Monster::KNIGHT2, Monster::KNIGHT3, Monster::ELF1,Monster::ELF2,Monster::ELF3
};