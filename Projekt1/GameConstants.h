#pragma once
#include"Monster.h"

namespace GameConstants
{

};

namespace PrimarySkill
{
	enum PrimarySkill {
		ATTACK, DEFENSE, SPELL_POWER, KNOWLEDGE,
		EXPERIENCE = 4
	}; //for some reason changePrimSkill uses it
}
enum ArrowDirection : int8_t
{
	None = -1,
	EndPath = 0,
	TopLeft_TopLeft = 13,
	TopLeft_Top = 19,
	TopLeft_TopRight = 19,
	TopLeft_Left = 11,
	TopLeft_Right = 20,
	TopLeft_BottomLeft = 2,
	TopLeft_Bottom = 2,
	Top_TopLeft = 22,
	Top_Top = 17,
	Top_TopRight = 20,
	Top_Left = 11,
	Top_Right = 6,
	Top_BottomLeft = 11,
	Top_BottomRight = 20,
	TopRight_TopLeft = 22,
	TopRight_Top = 9,
	TopRight_TopRight = 23,
	TopRight_Left = 11,
	TopRight_Right = 5,
	TopRight_Bottom = 11,
	TopRight_BottomRight = 7,
	Left_TopLeft = 8,
	Left_Top = 19,
	Left_TopRight = 19,
	Left_Left = 24,
	Left_BottomLeft = 2,
	Left_Bottom = 16,
	Left_BottomRight = 16,
	Right_TopLeft = 9,
	Right_Top = 9,
	Right_TopRight = 1,
	Right_Right = 18,
	Right_BottomLeft = 14,
	Right_Bottom = 14,
	Right_BottomRight = 7,
	BottomLeft_TopLeft = 8,
	BottomLeft_Top = 8,
	BottomLeft_Left = 15,
	BottomLeft_Right = 10,
	BottomLeft_BottomLeft = 4,
	BottomLeft_Bottom = 16,
	BottomLeft_BottomRight = 10,
	Bottom_TopLeft = 15,
	Bottom_TopRight = 21,
	Bottom_Left = 15,
	Bottom_Right = 21,
	Bottom_BottomLeft = 6,
	Bottom_Bottom = 12,
	Bottom_BottomRight = 10,
	BottomRight_TopRight = 1,
	BottomRight_Top = 8,
	BottomRight_Left = 15,
	BottomRight_Right = 21,
	BottomRight_BottomLeft = 6,
	BottomRight_Bottom = 14,
	BottomRight_BottomRight = 3,
};

enum HeroName
{
	EDRIC,
	CHRISTIAN,
	RION,
	CAITLIN,
	LOYNIS
};
enum HeroClass : int
{
	KNIGHT,
	CLERIC,
	RANGER,
	DRUID,
	ALCHEMIST,
	WIZARD,
};
enum Dwelling : int
{
	Guardhouse,
	ArchersTower,
	GriffinTower,
	Barracks,
	Monastery,
	TrainingGrounds,
	PoltarOfGlory,
};
enum TownLevel : int
{
	NoFort = 0,
	Fort = 1,
	Citadel = 2,
	Castle = 3
};
struct Arrow
{
	ArrowDirection dir = None;
	bool reachbleInOneTurn = true;
	bool toDraw = false;
	sf::Sprite sprite;
	void setTexture(sf::Texture& texture) { sprite.setTexture(texture); }
	void setType(ArrowDirection dir) { 
		this->dir = dir;
		sf::IntRect arrow;
		if(reachbleInOneTurn)
			arrow = sf::IntRect((dir % 7) * 33, (dir / 7) * 32, 33, 32);
		else
			arrow = sf::IntRect(((dir+28) % 7) * 33, ((dir+28) / 7) * 32, 33, 32);
		sprite.setTextureRect(arrow);
	}
	void setPosition(int x, int y) {
		this->sprite.setPosition((float)x, (float)y);
	}
};

class Obj
{
public:
	enum ObjType
	{
		NO_OBJ = -1,
		ALTAR_OF_SACRIFICE = 2,
		ANCHOR_POINT = 3,
		ARENA = 4,
		ARTIFACT = 5,
		PANDORAS_BOX = 6,
		BLACK_MARKET = 7,
		MOUNTS = 8,
		KEYMASTER = 10,
		BUOY = 11,
		CAMPFIRE = 12,
		CARTOGRAPHER = 13,
		SWAN_POND = 14,
		COVER_OF_DARKNESS = 15,
		CREATURE_BANK = 16,
		CURSED_GROUND1 = 21,
		CORPSE = 22,
		MARLETTO_TOWER = 23,
		DERELICT_SHIP = 24,
		DRAGON_UTOPIA = 25,
		EVENT = 26,
		EYE_OF_MAGI = 27,
		FAERIE_RING = 28,
		FLOTSAM = 29,
		FOUNTAIN_OF_FORTUNE = 30,
		FOUNTAIN_OF_YOUTH = 31,
		GARDEN_OF_REVELATION = 32,
		GARRISON = 33,
		HERO = 34,
		HILL_FORT = 35,
		GRAIL = 36,
		HUT_OF_MAGI = 37,
		IDOL_OF_FORTUNE = 38,
		LEAN_TO = 39,
		LIBRARY_OF_ENLIGHTENMENT = 41,
		LIGHTHOUSE = 42,
		MAGIC_PLAINS1 = 46,
		SCHOOL_OF_MAGIC = 47,
		MAGIC_SPRING = 48,
		MAGIC_WELL = 49,
		MERCENARY_CAMP = 51,
		MERMAID = 52,
		MINE = 53,
		MONSTER = 54,
		MYSTICAL_GARDEN = 55,
		OASIS = 56,
		OBELISK = 57,
		REDWOOD_OBSERVATORY = 58,
		OCEAN_BOTTLE = 59,
		PILLAR_OF_FIRE = 60,
		STAR_AXIS = 61,
		PRISON = 62,
		PYRAMID = 63,//subtype 0
		WOG_OBJECT = 63,//subtype > 0
		RALLY_FLAG = 64,
		RANDOM_ART = 65,
		RANDOM_TREASURE_ART = 66,
		RANDOM_MINOR_ART = 67,
		RANDOM_MAJOR_ART = 68,
		RANDOM_RELIC_ART = 69,
		RANDOM_HERO = 70,
		RANDOM_MONSTER = 71,
		RANDOM_MONSTER_L1 = 72,
		RANDOM_MONSTER_L2 = 73,
		RANDOM_MONSTER_L3 = 74,
		RANDOM_MONSTER_L4 = 75,
		RANDOM_RESOURCE = 76,
		RANDOM_TOWN = 77,
		REFUGEE_CAMP = 78,
		RESOURCE = 79,
		SANCTUARY = 80,
		SCHOLAR = 81,
		SEA_CHEST = 82,
		SEER_HUT = 83,
		CRYPT = 84,
		SHIPWRECK = 85,
		SHIPWRECK_SURVIVOR = 86,
		SHIPYARD = 87,
		SHRINE_OF_MAGIC_INCANTATION = 88,
		SHRINE_OF_MAGIC_GESTURE = 89,
		SHRINE_OF_MAGIC_THOUGHT = 90,
		SIGN = 91,
		SIRENS = 92,
		SPELL_SCROLL = 93,
		STABLES = 94,
		TAVERN = 95,
		TEMPLE = 96,
		TOWN_WALL = 97,
		TOWN = 98,
		TRADING_POST = 99,
		LEARNING_STONE = 100,
		TREASURE_CHEST = 101,
		TREE_OF_KNOWLEDGE = 102,
		SUBTERRANEAN_GATE = 103,
		UNIVERSITY = 104,
		WAGON = 105,
		WAR_MACHINE_FACTORY = 106,
		SCHOOL_OF_WAR = 107,
		WARRIORS_TOMB = 108,
		WATER_WHEEL = 109,
		WATERING_HOLE = 110,
		WHIRLPOOL = 111,
		WINDMILL = 112,
		WITCH_HUT = 113,
		HOLE = 124,
		BORDER_GATE = 212,
		FREELANCERS_GUILD = 213,
		HERO_PLACEHOLDER = 214,
		QUEST_GUARD = 215,
		DWELLING = 216,
		RANDOM_DWELLING_LVL = 217, //subtype = creature level
		RANDOM_DWELLING_FACTION = 218, //subtype = faction
		GARRISON2 = 219,
		ABANDONED_MINE = 220,
		TRADING_POST_SNOW = 221,
		ROCKLANDS = 231,
		CRATER = 232,
		FLOWERS = 233,
		LAKE = 234,
		MOUND = 235,
		DIRT_HILLS = 236,
	};


	Obj(ObjType _num = NO_OBJ) : num(_num)
	{}
	Obj(const Obj & other) { num = other.num; }
	explicit Obj(int id) : num(static_cast<ObjType>(id)) {}
	Obj & operator=(const Obj & other) { num = other.num; return *this; }
	operator ObjType() const { return num; }
	ObjType num;
};

struct MapObjectParametrs
{
	std::string name;
	int width;
	int height;
	std::vector<std::vector<int8_t>> usedTlies;
	int frameAnimation;
	uint16_t visitDir;
	bool blockVisit;
};

extern std::map<std::pair<Obj,int>, MapObjectParametrs> mapObjectsStats;
