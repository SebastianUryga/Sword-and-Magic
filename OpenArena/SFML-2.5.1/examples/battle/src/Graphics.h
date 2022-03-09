#pragma once
#include "Monser.h"
#include "GameConstants.h"
#include "Spell.h"
class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	sf::Image image;

	std::shared_ptr<sf::Texture> allSpellIcons;
	std::shared_ptr<sf::Texture> battleBackgrouds;
	std::shared_ptr<sf::Texture> battleEffectsSheet;
	std::map<int, std::shared_ptr<sf::Texture>> mapDwelling;
	std::shared_ptr<sf::Texture> menuBackgroud;
	std::shared_ptr<sf::Texture> allCreaturePortraits;
	std::map<Monster, sf::IntRect> creaturePortraits;
	std::map<Spell::SpellType, sf::IntRect> spellIcons;
	std::map<Monster, std::shared_ptr<sf::Texture>> battleUnitsSheets;
	std::map<BattleObstacle::Type, std::shared_ptr<sf::Texture>> battleObsticles;
	std::map<int, sf::Texture> primarySkills;
	std::map<int, sf::IntRect> portriats;
	std::map<int, sf::IntRect> smallPortraits;
	void Init();

	static Graphics& Get();
	static sf::IntRect selectPortrait(Monster type);
	static sf::IntRect selectSpellIcon(Spell type);
};

extern Graphics& graphics;