#pragma once
#include "Monser.h"
#include "PCH.hpp"
#include "Spell.h"
#include "GameConstants.h"

class Spell;
class Monster;

enum class Background : int
{
	BACKGROUND1 = 0, BACKGROUND2 = 1, BACKGROUND3 = 2, BACKGROUND4 = 3,
};

class Graphics2
{
public:
	Graphics2();
	virtual ~Graphics2();

	sf::Image image;
	sf::Texture arrow;
	sf::Texture magicBulet;
	
	class CreatureTexture
	{
	public:
		std::shared_ptr<sf::Texture> portrait;
		std::vector<std::shared_ptr<sf::Texture>> idle;
		std::vector<std::shared_ptr<sf::Texture>> move;
		std::vector<std::shared_ptr<sf::Texture>> run;
		std::vector<std::shared_ptr<sf::Texture>> attak;
		std::vector<std::shared_ptr<sf::Texture>> die;
		std::vector<std::shared_ptr<sf::Texture>> hurt;

		void Load(std::string creatureName);
	};
	std::shared_ptr<sf::Texture> allSpellIcons;
	std::map<Spell::SpellType, sf::IntRect> spellIcons;
	std::map<BattleObstacle::Type, std::shared_ptr<sf::Texture>> battleObsticles;
	std::map <Spell::SpellType, std::shared_ptr<sf::Texture>> battleEffects;
	std::shared_ptr<sf::Texture> battleEffectsSheet;
	std::map <Background, std::shared_ptr<sf::Texture>> backgroundsTextures;
	std::map <Monster, CreatureTexture> creaturesTextures;
	static sf::IntRect selectSpellIcon(Spell type);

	void init();

	static Graphics2& Get();
};

extern Graphics2& graphics2;