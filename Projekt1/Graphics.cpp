#include "pch.h"
#include "Graphics.h"

Graphics & graphics = Graphics::Get();

Graphics::Graphics()
{
	this->battleBackgrouds = std::make_shared<sf::Texture>();
	fogOfWarFullHide = std::make_shared<sf::Texture>();
	fogOfWarPartialHide = std::make_shared<sf::Texture>();
	heroMoveArrows = std::make_shared<sf::Texture>();
	heroOnMapSheet = std::make_shared<sf::Texture>();
	this->castleTown = std::make_shared<sf::Texture>();
	this->allHeroesPortraits = std::make_shared<sf::Texture>();
	this->allCreaturePortraits = std::make_shared<sf::Texture>();
	this->battleBackgrouds->setRepeated(true);
	fogOfWarFullHide->setRepeated(true);
	fogOfWarPartialHide->setRepeated(true);
	heroOnMapSheet->setRepeated(true);
	this->portriats[HeroName::EDRIC] = sf::IntRect(411, 3, 42, 47);
	this->portriats[HeroName::CHRISTIAN] = sf::IntRect(365, 54, 42, 47);
	this->portriats[HeroName::RION] = sf::IntRect(680, 54, 42, 47);
	this->portriats[HeroName::CAITLIN] = sf::IntRect(319, 106, 42, 47);
	this->portriats[HeroName::LOYNIS] = sf::IntRect(274, 106, 42, 47);
	this->smallPortraits[HeroName::EDRIC] = sf::IntRect(155,538,34,23);
	this->smallPortraits[HeroName::CHRISTIAN] = sf::IntRect(459,538,34,23);
	this->smallPortraits[HeroName::CAITLIN] = sf::IntRect(762,538,34,23);
	this->smallPortraits[HeroName::LOYNIS] = sf::IntRect(762,512,34,23);
	this->smallPortraits[HeroName::RION] = sf::IntRect(611,512,34,23);
	this->heroesOnMap[HeroClass::KNIGHT] = sf::IntRect(0, 0, 100, 100);
	this->heroesOnMap[HeroClass::CLERIC] = sf::IntRect(0, 1, 100, 100);
	this->heroesOnMap[HeroClass::DRUID] = sf::IntRect(0, 2, 100, 100);
	this->creaturePortraits[Monster::NO_CREATURE] = sf::IntRect(386, 627, 58, 64);
	this->creaturePortraits[Monster::PIKEMAN] = sf::IntRect(8, 6, 58, 64);
	this->creaturePortraits[Monster::HALBERDIER] = sf::IntRect(70, 6, 58, 64);
	this->creaturePortraits[Monster::ARCHER] = sf::IntRect(134, 6, 58, 64);
	this->creaturePortraits[Monster::MARKSMEN] = sf::IntRect(194, 6, 58, 64);
	this->creaturePortraits[Monster::GRIFFIN] = sf::IntRect(256, 6, 58, 64);
	this->creaturePortraits[Monster::ROYAL_GRIFFIN] = sf::IntRect(320, 6, 58, 64);
	this->creaturePortraits[Monster::SWORDSMAN] = sf::IntRect(386, 6, 58, 64);
	this->creaturePortraits[Monster::CRUSADER] = sf::IntRect(456, 6, 58, 64);
}


Graphics::~Graphics()
{
}

void Graphics::Init()
{
	
	image.loadFromFile("Textures\\TRDC000.png");
	sf::Color tran = this->image.getPixel(1, 1);
	image.createMaskFromColor(tran, 0);
	roads[0] = std::vector < std::shared_ptr<sf::Texture>>();
	
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[0].push_back(texture);
	image.loadFromFile("Textures\\TRDC001.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[0].push_back(texture);

	roads[1] = std::vector < std::shared_ptr<sf::Texture>>();

	image.loadFromFile("Textures\\TRDC010.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[1].push_back(texture);
	image.loadFromFile("Textures\\TRDC011.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[1].push_back(texture);
	image.loadFromFile("Textures\\TRDC012.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[1].push_back(texture);
	image.loadFromFile("Textures\\TRDC013.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[1].push_back(texture);

	roads[2] = std::vector < std::shared_ptr<sf::Texture>>();
	image.loadFromFile("Textures\\TRDC020.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[2].push_back(texture);
	image.loadFromFile("Textures\\TRDC021.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[2].push_back(texture);
	image.loadFromFile("Textures\\TRDC022.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[2].push_back(texture);
	image.loadFromFile("Textures\\TRDC023.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[2].push_back(texture);

	roads[3] = std::vector < std::shared_ptr<sf::Texture>>();
	image.loadFromFile("Textures\\TRDC030.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[3].push_back(texture);
	image.loadFromFile("Textures\\TRDC031.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[3].push_back(texture);
	image.loadFromFile("Textures\\TRDC032.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[3].push_back(texture);
	image.loadFromFile("Textures\\TRDC033.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[3].push_back(texture);

	roads[4] = std::vector < std::shared_ptr<sf::Texture>>();
	image.loadFromFile("Textures\\TRDC040.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[4].push_back(texture);
	image.loadFromFile("Textures\\TRDC041.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[4].push_back(texture);

	roads[5] = std::vector < std::shared_ptr<sf::Texture>>();
	image.loadFromFile("Textures\\TRDC050.png");
	image.createMaskFromColor(tran, 0);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromImage(image);
	roads[5].push_back(texture);
	
	this->battleBackgrouds->loadFromFile("Textures\\CmBkDrMt.png");
	this->battleUnitsSheets[Monster::PIKEMAN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::MARKSMEN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ARCHER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::SWORDSMAN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::CRUSADER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ANGEL] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::PIKEMAN]->loadFromFile("Textures\\Pikeman.png");
	this->battleUnitsSheets[Monster::ARCHER]->loadFromFile("Textures\\Archer.png");
	this->battleUnitsSheets[Monster::MARKSMEN]->loadFromFile("Textures\\Marksman.png");
	this->battleUnitsSheets[Monster::SWORDSMAN]->loadFromFile("Textures\\Swordsman.png");
	this->battleUnitsSheets[Monster::CRUSADER]->loadFromFile("Textures\\Crusader.png");
	this->battleUnitsSheets[Monster::ANGEL]->loadFromFile("Textures\\Angel.png");
	this->allHeroesPortraits->loadFromFile("Textures\\Heroes Portraits.png");
	this->allCreaturePortraits->loadFromFile("Textures\\Creatures Portraits.png");
	this->fogOfWarFullHide->loadFromFile("Textures\\fog.png");
	//this->fogOfWarPartialHide->loadFromFile("Textures\\");
	this->heroMoveArrows->loadFromFile("Textures\\arrows.png");
	this->heroOnMapSheet->loadFromFile("Textures\\heroes_texture.png");
	this->castleTown->loadFromFile("Textures\\Castle.png");
	this->mapObjects[{Obj::HERO, 0}] = this->heroOnMapSheet;
	this->mapObjects[{Obj::TAVERN, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::ARENA, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::CRATER, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::STABLES, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::TRADING_POST, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::MOUNTS, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::MOUNTS, 1}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::DIRT_HILLS, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::DIRT_HILLS, 1}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::DIRT_HILLS, 2}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::DIRT_HILLS, 3}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::MOUND, 0}] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::TOWN_WALL, 0}] = std::make_shared<sf::Texture>();
	this->mapDwelling[Dwelling::Guardhouse] = std::make_shared<sf::Texture>();
	this->mapDwelling[Dwelling::ArchersTower] = std::make_shared<sf::Texture>();
	this->mapDwelling[Dwelling::GriffinTower] = std::make_shared<sf::Texture>();
	this->mapDwelling[Dwelling::Barracks] = std::make_shared<sf::Texture>();
	this->mapObjects[{Obj::TAVERN, 0}]->loadFromFile("Textures\\Tavern.png");
	this->mapObjects[{Obj::ARENA, 0}]->loadFromFile("Textures\\Arena.png");
	this->mapObjects[{Obj::MOUNTS, 0}]->loadFromFile("Textures\\AvLMtDr4.png");
	this->mapObjects[{Obj::MOUNTS, 1}]->loadFromFile("Textures\\AvLMtDr5.png");
	this->mapObjects[{Obj::DIRT_HILLS, 0}]->loadFromFile("Textures\\AVLXdt00.png");
	this->mapObjects[{Obj::DIRT_HILLS, 1}]->loadFromFile("Textures\\AVLXdt01.png");
	this->mapObjects[{Obj::DIRT_HILLS, 2}]->loadFromFile("Textures\\AVLXdt02.png");
	this->mapObjects[{Obj::DIRT_HILLS, 3}]->loadFromFile("Textures\\AVLXdt03.png");
	this->mapObjects[{Obj::TOWN_WALL, 0}]->loadFromFile("Textures\\Town_wall.png");
	this->mapObjects[{Obj::CRATER, 0}]->loadFromFile("Textures\\Crater.png");
	this->mapObjects[{Obj::STABLES, 0}]->loadFromFile("Textures\\Stables.png");
	this->mapObjects[{Obj::TRADING_POST, 0}]->loadFromFile("Textures\\Trading Post.png");
	this->image.loadFromFile("Textures\\AVGpike0.png");
	sf::Color shadow = this->image.getPixel(30,60);
	this->image.createMaskFromColor(tran, 0);
	this->image.createMaskFromColor(shadow, 90);
	this->mapDwelling[Dwelling::Guardhouse]->loadFromImage(this->image);
	//this->image.createMaskFromColor();
	
	this->image.loadFromFile("Textures\\AVGcros0.png");
	this->image.createMaskFromColor(tran, 0);
	this->image.createMaskFromColor(shadow, 90);
	this->mapDwelling[Dwelling::ArchersTower]->loadFromImage(this->image);

	this->image.loadFromFile("Textures\\AVGgrff0.png");
	this->image.createMaskFromColor(tran, 0);
	this->image.createMaskFromColor(shadow, 90);
	this->mapDwelling[Dwelling::GriffinTower]->loadFromImage(this->image);

	this->mapDwelling[Dwelling::Barracks]->loadFromFile("Textures\\AVGswor0.png");
	this->mapObjects[{Obj::TOWN, 0}] = this->castleTown;
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

sf::IntRect Graphics::selectTownLevel(int level)
{
	switch (level)
	{
	case TownLevel::NoFort: return sf::IntRect(0, 0, 192, 160);
	case TownLevel::Fort: return sf::IntRect(192, 0, 192, 160);
	case TownLevel::Citadel: return sf::IntRect(384, 0, 192, 160);
	case TownLevel::Castle: return sf::IntRect(576, 0, 192, 160);
	default: return sf::IntRect(0, 0, 192, 160);
		break;
	}
}

sf::IntRect Graphics::selectPortrait(Monster type)
{
	return Graphics::Get().creaturePortraits[type];
}

sf::IntRect Graphics::selectPortriat(HeroName portrait)
{
	return Graphics::Get().portriats[portrait];
}

sf::IntRect Graphics::selectSmallPortrait(HeroName portrait)
{
	return Graphics::Get().smallPortraits[portrait];
}

sf::IntRect Graphics::selectHeroOnMap(HeroClass hc)
{
	return Graphics::Get().heroesOnMap[hc];
}

void Graphics::updateRoadTexture(const sf::Vector2i& mapPos)
{
	Graphics& graphics = Graphics::Get();
	Maps::Tile& tile = world.GetTile(mapPos);
	if (tile.GetRoad() == Maps::RoadType::NO_ROAD)
		return;
	int result = 4, rand1 = std::rand() % 2, rand2 = (std::rand() % 2) + 2;
	std::set<int> neighbourIndexes;
	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1),
		sf::Vector2i(-1, +0),   /* source pos */   sf::Vector2i(+1, +0),
		sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1)
	};
	for (int i = 0; i < 8; i++)
	{
		if (world.isInTheMap(mapPos + dirs[i]))
		{
			Maps::Tile& temp = world.GetTile(mapPos + dirs[i]);
			if (temp.GetRoad() != tile.GetRoad())
				continue;
			neighbourIndexes.insert(i);
		}
	}
	tile.roadSprite.setTexture(*graphics.roads[result][0]);
	if (neighbourIndexes.count(1)) {
		result = 4;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(1, -1);
		tile.roadSprite.setOrigin(0, TILEWIDTH);
	}
	if (neighbourIndexes.count(6) ) {
		result = 4;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(3)) {
		result = 4;
		tile.roadSprite.setTexture(*graphics.roads[result][1]);
		tile.roadSprite.setScale(-1, 1);
		tile.roadSprite.setOrigin(TILEWIDTH, 0);
	}
	if (neighbourIndexes.count(4)) {
		result = 4;
		tile.roadSprite.setTexture(*graphics.roads[result][1]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(1) && neighbourIndexes.count(6)) {
		result = 3;
		tile.roadSprite.setTexture(*graphics.roads[result][rand1]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(4)) {
		result = 3;
		tile.roadSprite.setTexture(*graphics.roads[result][rand2]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(4) && neighbourIndexes.count(6)) {
		result = 0;
		if (neighbourIndexes.count(2) || neighbourIndexes.count(5)) result = 1;
		tile.roadSprite.setTexture(*graphics.roads[result][rand1]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(1) && neighbourIndexes.count(4)) {
		result = 0;
		if (neighbourIndexes.count(7) || neighbourIndexes.count(0)) result = 1;
		tile.roadSprite.setTexture(*graphics.roads[result][rand1]);
		tile.roadSprite.setScale(1, -1);
		tile.roadSprite.setOrigin(0, TILEWIDTH);
	}
	if (neighbourIndexes.count(1) && neighbourIndexes.count(3)) {
		result = 0;
		if (neighbourIndexes.count(2) || neighbourIndexes.count(5)) result = 1;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(-1, -1);
		tile.roadSprite.setOrigin(TILEWIDTH, TILEWIDTH);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(6)) {
		result = 0;
		if (neighbourIndexes.count(7) || neighbourIndexes.count(0)) result = 1;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(-1, 1);
		tile.roadSprite.setOrigin(TILEWIDTH, 0);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(6) &&
		neighbourIndexes.count(1)) {
		result = 2;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(-1, 1);
		tile.roadSprite.setOrigin(TILEWIDTH, 0);
	}
	if (neighbourIndexes.count(4) && neighbourIndexes.count(6) &&
		neighbourIndexes.count(1)) {
		result = 2;
		tile.roadSprite.setTexture(*graphics.roads[result][rand1]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(4) &&
		neighbourIndexes.count(1)) {
		result = 2;
		tile.roadSprite.setTexture(*graphics.roads[result][rand2]);
		tile.roadSprite.setScale(1, -1);
		tile.roadSprite.setOrigin(0, TILEWIDTH);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(4) &&
		neighbourIndexes.count(6)) {
		result = 2;
		tile.roadSprite.setTexture(*graphics.roads[result][rand2]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
	if (neighbourIndexes.count(3) && neighbourIndexes.count(4) &&
		neighbourIndexes.count(1) && neighbourIndexes.count(6)) {
		result = 5;
		tile.roadSprite.setTexture(*graphics.roads[result][0]);
		tile.roadSprite.setScale(1, 1);
		tile.roadSprite.setOrigin(0, 0);
	}
}
