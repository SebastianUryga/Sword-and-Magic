#pragma once
#include "Monser.h"
#include "GameConstants.h"
class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	std::shared_ptr<sf::Texture> battleBackgrouds;
	std::map<int, std::shared_ptr<sf::Texture>> mapDwelling;
	std::shared_ptr<sf::Texture> menuBackgroud;
	std::shared_ptr<sf::Texture> allCreaturePortraits;
	std::map<Monster, sf::IntRect> creaturePortraits;
	std::map<Monster, std::shared_ptr<sf::Texture>> battleUnitsSheets;
	std::map<BattleObstacle::Type, std::shared_ptr<sf::Texture>> battleObsticles;
	std::map<int, sf::Texture> primarySkills;
	std::map<int, sf::IntRect> portriats;
	std::map<int, sf::IntRect> smallPortraits;
	void Init();

	static Graphics& Get();
	static sf::IntRect selectPortrait(Monster type);
	///set matching road textures to neighobur tiles

};

extern Graphics& graphics;