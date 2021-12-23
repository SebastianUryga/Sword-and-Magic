#pragma once
#include "Monser.h"
#include "PCH.hpp"

class Graphics2
{
public:
	Graphics2();
	virtual ~Graphics2();

	sf::Image image;

	class CreatureTexture
	{
	public:
		std::vector<std::shared_ptr<sf::Texture>> idle;
		std::vector<std::shared_ptr<sf::Texture>> move;
		std::vector<std::shared_ptr<sf::Texture>> attak;
		std::vector<std::shared_ptr<sf::Texture>> die;
		std::vector<std::shared_ptr<sf::Texture>> hurt;

		void Load(std::string creatureName)
		{
			int i = 0;
			auto temp = std::make_shared<sf::Texture>();
			std::string s = "Textures/" +creatureName + "/" + creatureName;
			while(temp->loadFromFile(s + "_IDLE_00" + std::to_string(i) + ".png"))
			{
				idle.push_back(temp);
				temp = std::make_shared<sf::Texture>();
				if (++i > 9) break;
			}
			i = 0;
			while (temp->loadFromFile(s + "_ATTAK_00" + std::to_string(i) + ".png"))
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
			
		}
	};
	//std::map <Background, std::shared_ptr<sf::Texture>> bacgroundsTextures;
	std::map <Monster, CreatureTexture> creaturesTextures;
	void init();

	static Graphics2& Get();
};

extern Graphics2& graphics2;