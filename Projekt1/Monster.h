#pragma once

struct MonsterStats
{
	uint8_t attack;
	uint8_t defence;
	uint8_t level;
	uint16_t hp;
	bool fly;
	bool archer;
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
	bool turn;
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
		SWORDMAN = 2,
		CRUSADER = 4
	};

	Monster(MonsterType type = NO_CREATURE) : monster(type) {}
	Monster(const Monster& other) : monster(other.monster) {}
	Monster& operator=(const Monster& other) { monster = other.monster; return *this; }
	explicit Monster(int type) { monster = static_cast<MonsterType>(type); }
	operator Monster() const { return monster; }
	bool operator==(const Monster& other) const { return monster == other.monster; }
	bool operator<(const Monster& other) const { return monster < other.monster; }
	MonsterType monster;
};

extern std::map<std::pair<Monster,std::string>, MonsterAnimationParametrs> animationParametrs;