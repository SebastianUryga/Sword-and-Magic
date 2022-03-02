#include "Player.h"
#include "Spell.h"
#include "Monser.h"

void Player::setAI(bool AI)
{
	artificalIntelligence = AI;
}

bool Player::setMana(int mana)
{
	_actualManaPoints = mana;
	return true;
}

bool Player::isAI() const
{
	return this->artificalIntelligence;
}

bool Player::hasSpell(Spell spell)
{
	return std::find(availbleSpells.begin(), availbleSpells.end(), spell) != availbleSpells.end();
}

int Player::getActuallMana() const
{
	return this->_actualManaPoints;
}

int Player::getMaxMana() const
{
	return this->_maxManaPoints;
}

int Player::getSpellCooldown() const
{
	return (int)this->_spellCooldown;
}

bool Player::refreshColldown()
{
	this->_spellCooldown = 5.f;
	return true;
}

bool Player::substrackMana(int mana)
{
	if (_actualManaPoints < mana)
		return false;
	_actualManaPoints -= mana;
	return true;
}

Player::Player(bool AI, int manaPoints = 30)
	: artificalIntelligence(AI), _maxManaPoints(manaPoints)
{
	this->initArmy();
	this->initSpellbook();
	_actualManaPoints = _maxManaPoints;
	_spellCooldown = 0.f;
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	if (_spellCooldown > 0)
		_spellCooldown -= dt;
}

bool Player::load(std::fstream file)
{
	return false;
}

bool Player::save(std::fstream file)
{
	return false;
}

void Player::initArmy()
{
	this->army = { { Monster::ELF1, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 2 }, { Monster::NO_CREATURE, 2 }, { Monster::NO_CREATURE, 0 } };

}

void Player::initSpellbook()
{
	auto spell = Spell();
	this->availbleSpells = { Spell::SpellType::WEEKNES,Spell::SpellType::SHIELD,Spell::SpellType::CURSE,
	Spell::SpellType::HASTE,Spell::SpellType::COUNTER_STRIKE,Spell::SpellType::STRENGTH,
	Spell::SpellType::SLOW,Spell::SpellType::BLESS,Spell::SpellType::TURN_TO_STONE };
}
