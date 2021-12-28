#pragma once
#include "Monser.h"
#include "PCH.hpp"


enum class Background : int
{
	BACKGROUND1 = 0, BACKGROUND2 = 1, BACKGROUND3 = 2,
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

		void Load(std::string creatureName)
		{	
			int i = 0;
			auto temp = std::make_shared<sf::Texture>();
			this->portrait = std::make_shared<sf::Texture>();
			std::string s = "Textures/" +creatureName + "/" + creatureName;
			this->portrait->loadFromFile(s + "_head" + ".png");
			while(temp->loadFromFile(s + "_IDLE_00" + std::to_string(i) + ".png"))
			{
				idle.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_ATTACK_00" + std::to_string(i) + ".png"))
			{
				attak.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_WALK_00" + std::to_string(i) + ".png"))
			{
				move.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_DIE_00" + std::to_string(i) + ".png"))
			{
				die.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_HURT_00" + std::to_string(i) + ".png"))
			{
				hurt.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_RUN_00" + std::to_string(i) + ".png"))
			{
				run.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			
		}
	};
	std::shared_ptr<sf::Texture> allSpellIcons;
	std::map<Spell::SpellType, sf::IntRect> spellIcons;
	std::shared_ptr<sf::Texture> battleEffectsSheet;
	std::map <Background, std::shared_ptr<sf::Texture>> backgroundsTextures;
	std::map <Monster, CreatureTexture> creaturesTextures;
	static sf::IntRect selectSpellIcon(Spell type);

	void init();

	static Graphics2& Get();
};

extern Graphics2& graphics2;