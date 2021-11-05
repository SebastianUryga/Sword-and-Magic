#pragma once
class Spell
{
public:
	enum class SpellType : int
	{
		NONE,
		WEEKNES,
		SHIELD,
		CURSE,
		HASTE,
		SLOW,
		COUNTER_STRIKE,
		BERSERK,
		FORGETFULNESS,
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

extern std::map<Spell::SpellType, EffectsAnimationParametrs> batteEffectsAnimationParamets;
static std::vector<Spell::SpellType> allSpells = {
	Spell::SpellType::WEEKNES,Spell::SpellType::SHIELD,Spell::SpellType::CURSE,
	Spell::SpellType::HASTE,Spell::SpellType::COUNTER_STRIKE,Spell::SpellType::BERSERK,
	Spell::SpellType::SLOW,Spell::SpellType::FORGETFULNESS
};