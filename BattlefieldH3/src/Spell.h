#pragma once
#include "PCH.hpp"
class BattleUnit;

class Spell
{
public:
	enum class SpellType : int
	{
		NONE=0,
		WEEKNES=1,
		SHIELD=2,
		CURSE=3,
		BLESS=4,
		HASTE=5,
		SLOW=6,
		COUNTER_STRIKE=7,
		BERSERK=8,
		FORGETFULNESS=9,
		TURN_TO_STONE=10,
		STRENGTH=11,
	};
	SpellType spell;
	Spell(SpellType type = SpellType::NONE):spell(type) {}
	Spell(const Spell& other) : spell(other.spell) {}
	Spell& operator=(const Spell& other) { spell = other.spell;  return *this;}
	bool operator== (const Spell & other) { return other.spell == this->spell; }
	bool operator!= (const Spell & other) { return other.spell != this->spell; }
	explicit Spell(int type) { spell = static_cast<SpellType>(type); }

	static void castSpellOnUnit(BattleUnit& unit, const Spell spell);
	static void takeOffSpellFromUnit(BattleUnit& unit, const Spell spell);
};

struct EffectsAnimationParametrs
{
	float animationTimer;
	int start_frame_x;
	int start_frame_y;
	int frames_x;
	int frames_y;
	int width;
	int height;
	//sf::Vector2f orgin;
	float tileWidth;
};

extern std::map<Spell::SpellType, std::string> spellToString;
extern std::map<Spell::SpellType, int> spellCost;

extern std::map<Spell::SpellType, EffectsAnimationParametrs> batteEffectsAnimationParamets;
static std::vector<Spell::SpellType> allSpells = {
	Spell::SpellType::WEEKNES,Spell::SpellType::SHIELD,Spell::SpellType::CURSE,
	Spell::SpellType::HASTE,Spell::SpellType::COUNTER_STRIKE,Spell::SpellType::STRENGTH,
	Spell::SpellType::SLOW,Spell::SpellType::BLESS,Spell::SpellType::TURN_TO_STONE
};