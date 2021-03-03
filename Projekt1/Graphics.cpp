#include "pch.h"
#include "Graphics.h"

Graphics & graphics = Graphics::Get();

Graphics::Graphics()
{
	fogOfWarFullHide = std::make_shared<sf::Texture>();
	fogOfWarPartialHide = std::make_shared<sf::Texture>();
	heroMoveArrows = std::make_shared<sf::Texture>();
	heroOnMapSheet = std::make_shared<sf::Texture>();
	this->allHeroesPortraits = std::make_shared<sf::Texture>();
	fogOfWarFullHide->setRepeated(true);
	fogOfWarPartialHide->setRepeated(true);
	heroOnMapSheet->setRepeated(true);
	this->portriats[Hero::EDRIC] = sf::IntRect(101, 3, 42, 47);
	this->portriats[Hero::CHRISTIAN] = sf::IntRect(365, 54, 42, 47);
	this->portriats[Hero::RION] = sf::IntRect(680, 54, 42, 47);
	this->heroesOnMap[HeroClass::KNIGHT] = sf::IntRect(0, 0, 100, 100);
	this->heroesOnMap[HeroClass::CLERIC] = sf::IntRect(0, 64, 100, 100);
	this->heroesOnMap[HeroClass::DRUID] = sf::IntRect(0, 128, 100, 100);
}


Graphics::~Graphics()
{
}

void Graphics::Init()
{
	this->allHeroesPortraits->loadFromFile("Textures\\Heroes Portraits.png");
	this->fogOfWarFullHide->loadFromFile("Textures\\fog.png");
	//this->fogOfWarPartialHide->loadFromFile("Textures\\");
	this->heroMoveArrows->loadFromFile("Textures\\arrows.png");
	this->heroOnMapSheet->loadFromFile("Textures\\heroes_texture.png");
	this->mapObjects[Obj::HERO] = this->heroOnMapSheet;
	this->mapObjects[Obj::TAVERN] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::ARENA] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::CRATER] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::STABLES] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::TRADING_POST] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::MOUNTS1] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::MOUNTS2] = std::make_shared<sf::Texture>();
	this->mapObjects[Obj::TAVERN]->loadFromFile("Textures\\Tavern.png");
	this->mapObjects[Obj::ARENA]->loadFromFile("Textures\\Arena.png");
	this->mapObjects[Obj::MOUNTS1]->loadFromFile("Textures\\AvLMtDr4.png");
	this->mapObjects[Obj::MOUNTS2]->loadFromFile("Textures\\AvLMtDr5.png");
	this->mapObjects[Obj::CRATER]->loadFromFile("Textures\\Crater.png");
	this->mapObjects[Obj::STABLES]->loadFromFile("Textures\\Stables.png");
	this->mapObjects[Obj::TRADING_POST]->loadFromFile("Textures\\Trading Post.png");
	this->grounds[Maps::Ground::DIRT] = std::make_shared<sf::Texture>();
	this->grounds[Maps::Ground::DIRT]->loadFromFile("Textures\\Dirt_(h).png");
	this->grounds[Maps::Ground::DIRT]->setRepeated(true); 
	this->grounds[Maps::Ground::GRASS] = std::make_shared<sf::Texture>();
	this->grounds[Maps::Ground::GRASS]->loadFromFile("Textures\\Grass_(h)2.png");
	this->grounds[Maps::Ground::GRASS]->setRepeated(true);
}

Graphics & Graphics::Get()
{
	static Graphics gr;
	return gr;
}

sf::IntRect Graphics::selectPortriat(Hero portrait)
{
	return Graphics::Get().portriats[portrait];
}

sf::IntRect Graphics::selectHeroOnMap(HeroClass hc)
{
	return Graphics::Get().heroesOnMap[hc];
}
