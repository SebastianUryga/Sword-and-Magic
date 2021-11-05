#include "GuiHandler.h"

void Spell::castSpellOnUnit(BattleUnit& unit, const Spell spell)
{
	auto& list = unit.castedSpellList;

	//check if spell is already casted
	if (std::find(list.begin(), list.end(), spell) != list.end())
	{
		std::find(list.begin(), list.end(), spell)->timeRemain = 20;
		unit.spellToAnimate = spell;
		return;
	}

	switch (spell.spell)
	{
	case Spell::SpellType::WEEKNES:
		Spell::takeOffSpellFromUnit(unit, Spell(Spell::SpellType::SHIELD));
		unit.defence -= 6;
		break;
	case Spell::SpellType::SHIELD:
		Spell::takeOffSpellFromUnit(unit, Spell(Spell::SpellType::WEEKNES));
		unit.defence += 6;
		break;
	case Spell::SpellType::HASTE:
		Spell::takeOffSpellFromUnit(unit, Spell(Spell::SpellType::SLOW));
		unit.speed += 30.f;
		break;
	case Spell::SpellType::SLOW:
		Spell::takeOffSpellFromUnit(unit, Spell(Spell::SpellType::HASTE));
		unit.speed *= 0.7f;
		break;
	case Spell::SpellType::COUNTER_STRIKE:
		unit.attackCoulddown *= 0.8;
		break;
	case Spell::SpellType::BERSERK:
		unit.setEnemy(!unit.enemy);
	default:
		break;
	}
	list.push_front(CastedSpell(spell, 15));
	unit.spellToAnimate = spell;
}

void Spell::takeOffSpellFromUnit(BattleUnit& unit, const Spell spell)
{
	auto& list = unit.castedSpellList;
	//check if there is spell we want to take off
	if (std::find(list.begin(), list.end(), spell) != list.end())
	{
		switch (spell.spell)
		{
		case Spell::SpellType::WEEKNES:
			unit.defence += 6;
			break;
		case Spell::SpellType::SHIELD:
			unit.defence -= 6;
			break;
		case Spell::SpellType::HASTE:
			unit.speed -= 30.f;
			break;
		case Spell::SpellType::SLOW:
			unit.speed /= 0.7f;
			break;
		case Spell::SpellType::COUNTER_STRIKE:
			unit.attackCoulddown /= 0.8;
			break;
		case Spell::SpellType::BERSERK:
			unit.setEnemy(!unit.enemy);
			break;
		default:
			break;
		}

		list.erase(std::find(list.begin(), list.end(), spell));
	}

}
std::map<Spell::SpellType, EffectsAnimationParametrs> batteEffectsAnimationParamets = {
	{Spell::SpellType::WEEKNES, {0.6f,0,0,20,0,97,114,50}},
	{Spell::SpellType::SHIELD, {0.7f,0,1,16,0,56,114,50}},
	{Spell::SpellType::CURSE, {0.5f,0,2,21,0,85,114,50}},
	{Spell::SpellType::HASTE, {0.7f,0,3,15,0,113,114,50}},
	{Spell::SpellType::SLOW, {0.6f,0,6,15,0,74,114,50}},
	{Spell::SpellType::COUNTER_STRIKE, {0.5f,0,4,16,0,84,114,50}},
	{Spell::SpellType::BERSERK, {0.5f,0,5,16,0,61,114,50}},
	{Spell::SpellType::FORGETFULNESS, {0.5f,0,7,15,0,119,114,50}}
};
std::map<Spell::SpellType, std::string> spellToString = {
	{Spell::SpellType::NONE, "None"},
	{Spell::SpellType::WEEKNES, "Weeknes"},
	{Spell::SpellType::SHIELD, "Shield"},
	{Spell::SpellType::HASTE, "Haste"},
	{Spell::SpellType::CURSE, "Curse"},
	{Spell::SpellType::SLOW, "Slow"},
	{Spell::SpellType::COUNTER_STRIKE, "Counter Strike"},
	{Spell::SpellType::BERSERK, "Berserk"},
	{Spell::SpellType::FORGETFULNESS, "Forgetfulness"}
};







