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
	std::map<int, std::vector<std::shared_ptr<sf::Texture>>> roads;
	std::map<std::pair<int,int>, std::shared_ptr<sf::Texture>> mapObjects;
	std::map<int, std::shared_ptr<sf::Texture>> grounds;
	std::map<int, std::shared_ptr<sf::Texture>> mapDwelling;
	std::shared_ptr<sf::Texture> castleTown;
	std::shared_ptr<sf::Texture> allHeroesPortraits;
	std::shared_ptr<sf::Texture> allCreaturePortraits;
	std::map<Monster, sf::IntRect> creaturePortraits;
	std::map<int, sf::Texture> primarySkills;
	std::map<int, sf::IntRect> portriats;
	std::map<int, sf::IntRect> smallPortraits;
	void Init();
	sf::Image image;
	static Graphics & Get();
	static sf::IntRect selectTownLevel(int level);
	static sf::IntRect selectPortrait(Monster type);
	static sf::IntRect selectPortriat(HeroName portrait);
	static sf::IntRect selectSmallPortrait(HeroName portrait);
	static sf::IntRect selectHeroOnMap(HeroClass hc);
	///set matching road textures to neighobur tiles
	static void updateRoadTexture(const sf::Vector2i& mapPos);
	/*

	heroMoveArrows;
	mapObjectAnimations;
	imageLists;

	std::shared_ptr<CAnimation> getAnimation(const CGObjectInstance * obj);
	*/
};

extern Graphics & graphics;