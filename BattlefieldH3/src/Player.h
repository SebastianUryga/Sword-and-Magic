#pragma once
#include "PCH.hpp"
#include "Garrnison.h"


class Spell;

class Player
{

private:
	bool artificalIntelligence;

	int _actualManaPoints;
	int _maxManaPoints;

	float _spellCooldown;
	void initArmy();
	void initSpellbook();
public:
	std::vector<Troop> army;
	std::vector<Spell> availbleSpells;
	
	bool setMana(int mana);
	bool isAI() const;
	bool hasSpell(Spell spell);
	int getActuallMana() const;
	int getMaxMana() const;
	int getSpellCooldown() const;
	bool refreshColldown();
	bool substrackMana(int mana);

	Player(bool AI, int manaPoints);
	virtual ~Player();

	void update(const float& dt);

	bool load(std::fstream file);
	bool save(std::fstream file);
};

