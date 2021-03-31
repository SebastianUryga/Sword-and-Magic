#include "pch.h"
#include "TownInstance.h"



void TownInstance::putBuildingsOnMap(const sf::Vector2i pos)
{
	this->buldings[0]->mapObjectPos = sf::Vector2i(pos.x - 5, pos.y);
	this->buldings[1]->mapObjectPos = sf::Vector2i(pos.x - 5, pos.y + 2);
	this->buldings[2]->mapObjectPos = sf::Vector2i(pos.x - 3, pos.y + 2);
	this->buldings[3]->mapObjectPos = sf::Vector2i(pos.x, pos.y + 2);
	this->buldings[4]->mapObjectPos = sf::Vector2i(pos.x + 2, pos.y + 2);
	this->buldings[5]->mapObjectPos = sf::Vector2i(pos.x + 2, pos.y);
	for (auto& building : this->buldings)
	{
		building->owner = this;
		if (!world.isInTheMap(building->mapObjectPos))
			continue;
		building->visibleMapObject = new MP2::ObjectInstance();
		building->visibleMapObject->setType(Obj::DIRT_HILLS,std::rand()%4);
		building->visibleMapObject->setTilePos(building->mapObjectPos);
		building->visibleMapObject->initObj();
		world.addMapObject(building->visibleMapObject);
	}
}

void TownInstance::setObjectsToBuildings()
{
	for (auto b : this->buldings)
	{
		b->visibleMapObject = world.GetObject(b->objectId);
		b->setType(b->id);
	}
}

TownInstance::TownInstance()
	: MP2::ObjectInstance()
{
	this->buldings.resize(6);
	for (auto& i : this->buldings)
		i = new Building();
	
	this->ownerColor = Color::UNUSED;
	this->type = Obj::TOWN;
	this->subType = TownLevel::NoFort;
}


TownInstance::~TownInstance()
{
}

void TownInstance::setOwner(int ow)
{
	Kingdom & player = world.GetKingdom(this->getOwner());
	auto hero = std::find(player.castles.begin(), player.castles.end(), this);
	if (hero != player.castles.end())
		player.castles.erase(hero);

	MP2::ObjectInstance::setOwner(ow);
	player = world.GetKingdom(ow);
	player.castles.push_back(this);
	//PI->gameArea->playerListOfHero->update();
	world.revealTilesInRange(
		this->getVisitablePos(),
		MP2::ObjectInstance::getSightRadius(),
		this->ownerColor
	);
}

void TownInstance::initObj()
{
	troops.resize(7);
	troops = { {Monster::NO_CREATURE, 0},{Monster::NO_CREATURE, 0},
		{Monster::NO_CREATURE, 0}, {Monster::NO_CREATURE, 0}, {Monster::NO_CREATURE, 0},
		{Monster::NO_CREATURE, 0},{Monster::NO_CREATURE, 0} };

	this->setSize(6, 5);
	this->usedTiles = { {4,4,2,4,4,1}, {4,4,4,4,4,1 },
	{1,4,4,4,1,1 },{1,1,4,1,1,1 }, {1,1,1,1,1,1 } };
	this->visitDir = DIRECTION_BOTTOM_ROW;
	this->blockVisit = false;
	this->priority = 2;

	
	this->setTexture(*graphics.castleTown);
	//this->initObjAnimaiton();
}

void TownInstance::setTexture(sf::Texture & sheetTexture)
{
	MP2::ObjectInstance::setTexture(sheetTexture);
	this->sprite.setTextureRect(Graphics::selectTownLevel(this->subType));
}

void TownInstance::setType(int type, int subType)
{
	assert(type == Obj::TOWN);
	this->subType = subType;
	this->sprite.setTextureRect(Graphics::selectTownLevel(this->subType));
}

void TownInstance::setTilePos(const sf::Vector2i & pos)
{
	MP2::ObjectInstance::setTilePos(pos);
	this->buldings[0]->mapObjectPos = sf::Vector2i(this->pos.x - 5, this->pos.y);
	this->buldings[1]->mapObjectPos = sf::Vector2i(this->pos.x - 5, this->pos.y + 2);
	this->buldings[2]->mapObjectPos = sf::Vector2i(this->pos.x - 3, this->pos.y + 2);
	this->buldings[3]->mapObjectPos = sf::Vector2i(this->pos.x, this->pos.y + 2);
	this->buldings[4]->mapObjectPos = sf::Vector2i(this->pos.x + 2, this->pos.y + 2);
	this->buldings[5]->mapObjectPos = sf::Vector2i(this->pos.x + 2, this->pos.y);
	for (auto& building : this->buldings)
	{
		auto obj = building->visibleMapObject;
		if (!world.isInTheMap(building->mapObjectPos))
			assert(0);
		if (building->visibleMapObject)
			world.changeObjPos(obj->id, obj->pos, building->mapObjectPos);
	}
}

void TownInstance::afterAddToMap()
{
	std::vector<TownInstance*>& vec = world.vec_town;
	auto town = std::find(vec.begin(), vec.end(), this);
	if (town == vec.end())
		vec.push_back(this);
	else
		std::cout << "town is already existing in world" << std::endl;
}

void TownInstance::onHeroVisit(const HeroInstance * h)
{
	MP2::ObjectInstance::onHeroVisit(h);
	if (this->ownerColor != h->getOwner())
		this->setOwner(h->getOwner());
	// Open town Window
}

void TownInstance::update(const float & dt)
{
	MP2::ObjectInstance::update(dt);
}

void TownInstance::render(sf::RenderTarget * target)
{
	MP2::ObjectInstance::render(target);
}

void TownInstance::save(std::fstream & file)
{
	MP2::ObjectInstance::save(file);
	for (auto b : this->buldings)
	{
		file << b->visibleMapObject->id << " ";
		file << b->mapObjectPos.x << " " << b->mapObjectPos.y << " ";
		file << b->id << " ";
	}
	for (auto& troop : this->troops)
	{
		file << " " << troop.monster.monster << " " << troop.count << " ";
	}
}

void TownInstance::load(std::fstream & file)
{
	int type = 0;
	MP2::ObjectInstance::load(file);
	for (auto b : this->buldings)
	{
		file >> b->objectId;
		file >> b->mapObjectPos.x >> b->mapObjectPos.y;
		file >> type;
		b->id = BuildingID(type);
	}
	for (auto& troop : this->troops)
	{
		file >> type >> troop.count;
		Monster temp(type);
		troop.monster = temp;
	}
}

Building::Building()
{
	this->id = BuildingID::NONE;
	this->upgrade = BuildingID::NONE;
	this->cost = 0;
	this->owner = nullptr;
	this->visibleMapObject = nullptr;
	this->upgrade = NONE;
}

Building::~Building()
{
}

void Building::setType(BuildingID id)
{
	// to test
	
	this->id = id;
	BuildingStats stats = buildingStats[id];
	this->cost = stats.cost;
	this->name = stats.name;
	if (id == NONE)
		this->visibleMapObject->setType(stats.type);
	else
		this->visibleMapObject->setType(stats.type, stats.subType);
	this->visibleMapObject->initObj();
	this->upgrade = stats.upgrade;
}
