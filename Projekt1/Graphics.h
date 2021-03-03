#pragma once
#include"Tiles.h"
class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	std::shared_ptr<sf::Texture> fogOfWarFullHide;
	std::shared_ptr<sf::Texture> fogOfWarPartialHide;
	std::shared_ptr<sf::Texture> heroMoveArrows;
	std::shared_ptr<sf::Texture> heroOnMapSheet;
	std::map<int, sf::IntRect> heroesOnMap;
	std::map<int, std::shared_ptr<sf::Texture>> mapObjects;
	std::map<int, std::shared_ptr<sf::Texture>> grounds;
	std::shared_ptr<sf::Texture> allHeroesPortraits;
	std::map<int, sf::Texture> primarySkills;
	std::map<int, sf::IntRect> portriats;
	void Init();

	static Graphics & Get();
	static sf::IntRect selectPortriat(Hero portrait);
	static sf::IntRect selectHeroOnMap(HeroClass hc);
	/*

	heroMoveArrows;
	mapObjectAnimations;
	imageLists;

	std::shared_ptr<CAnimation> getAnimation(const CGObjectInstance * obj);
	*/
};

extern Graphics & graphics;