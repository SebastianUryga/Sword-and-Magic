#include "pch.h"
#include "HeroInstance.h"
#include "World.h"


bool HeroInstance::moveHero(sf::Vector2i dest)
{
	if (currentPath && isStanding)
	{
		this->movmentComponent->StartMoving();
		isStanding = false;
		return true;
	}
	return false;
}

bool HeroInstance::makePath(sf::Vector2i dest)
{
	
	this->currentPath = std::make_shared<Path>();
	bool ret = this->pathfinder->getPath(*this->currentPath, dest);
	if (ret && this->currentPath->nodes.size())
	{
		std::cout << "cost is " << this->currentPath->nodes[0].cost << std::endl;
		this->movmentComponent->setNewPath(this->currentPath);
		
	}
	else
		this->currentPath = nullptr;
	// ustawienie strza³ek TODO
	Interface::GetHeroMoveArrows().calcuateArrows(this->currentPath); //showPath
	return ret;
}

void HeroInstance::calcuatePaths()
{
	this->pathfinder->initializeGraph();
	this->pathfinder->calculatePaths();
}

HeroInstance::HeroInstance() : MP2::ObjectInstance()
{
	this->isStanding = true;
	this->type = Obj::HERO;
	this->movement = getMaxMovePoints();
	this->lastMove = movment_state::MOVING_DOWN;
}


HeroInstance::~HeroInstance()
{
}

int HeroInstance::getTileCost(const Maps::Tile & dest, const Maps::Tile & from) const
{
	unsigned ret = 100;
	//if there is road both on dest and src tiles - use road movement cost
	if (dest.GetRoad() != Maps::RoadType::NO_ROAD && from.GetRoad() != Maps::RoadType::NO_ROAD)
	{
		int road = std::min(dest.GetRoad(), from.GetRoad()); //used road ID
		switch (road)
		{
		case Maps::RoadType::DIRT_ROAD:
			ret = 75;
			break;
		case Maps::RoadType::GRAVEL_ROAD:
			ret = 65;
			break;
		case Maps::RoadType::COBBLESTONE_ROAD:
			ret = 50;
			break;
		default:
			std::cout << "Unknown road type:" << road << std::endl;
			break;
		}
	}
	return ret;
}

int HeroInstance::getMaxMovePoints() const
{
	return 1500;
}


void HeroInstance::initHero()
{
	this->pathfinder = std::make_shared<Pathfinder>(sf::Vector2i (world.w(), world.h()), this);
	//this->pathfinder->initializeGraph();
	this->currentPath = nullptr;
	this->movmentComponent = new MovmentComponent(this->sprite);
	this->setTexture(*graphics.heroOnMap);
}

int HeroInstance::getSightRadius() const
{
	return 5;// + bonus
}

void HeroInstance::initObj()
{
	switch (this->subType)
	{
	case 1:
	default:
		this->setOwner(Color::BLUE);
		this->instanceName = "Hero";
		this->setSize(3, 2);
		this->usedTiles = { { 2,1,1 }, {1,1,1} };
		this->visitDir = DIRECTION_ALL;
		this->blockVisit = true;
		break;
	}
	this->initHero();
	this->initObjAnimaiton();
}

void HeroInstance::initObjAnimaiton()
{
	this->animationComponent = new AnimotionComponent(this->sprite, *graphics.heroOnMap);
	this->animationComponent->addAnimotion("IDLE_DOWN", 10.f, 0, 0, 0, 0, 96, 64, false);
	this->animationComponent->addAnimotion("IDLE_DOWN_RIGHT", 10.f, 1, 0, 0, 0, 96, 64, false);
	this->animationComponent->addAnimotion("IDLE_DOWN_LEFT", 10.f, 1, 0, 0, 0, 96, 64, true);
	this->animationComponent->addAnimotion("IDLE_RIGHT", 10.f, 2, 0, 0, 0, 96, 64, false);
	this->animationComponent->addAnimotion("IDLE_LEFT", 10.f, 2, 0, 0, 0, 96, 64, true);
	this->animationComponent->addAnimotion("IDLE_UP_RIGHT", 10.f, 3, 0, 0, 0, 96, 64, false);
	this->animationComponent->addAnimotion("IDLE_UP_LEFT", 10.f, 3, 0, 0, 0, 96, 64, true);
	this->animationComponent->addAnimotion("IDLE_UP", 10.f, 4, 0, 0, 0, 96, 64, false);
	this->animationComponent->addAnimotion("MOVE_DOWN", 1.f, 5, 0, 7, 0, 96, 64, false);
	this->animationComponent->addAnimotion("MOVE_DOWN_RIGHT", 1.f, 13, 0, 7, 0, 96, 64, false);
	this->animationComponent->addAnimotion("MOVE_DOWN_LEFT", 1.f, 13, 0, 7, 0, 96, 64, true);
	this->animationComponent->addAnimotion("MOVE_RIGHT", 1.f, 21, 0, 7, 0, 96, 64, false);
	this->animationComponent->addAnimotion("MOVE_LEFT", 1.f, 21, 0, 7, 0, 96, 64, true);
	this->animationComponent->addAnimotion("MOVE_UP_RIGHT", 1.f, 29, 0, 7, 0, 96, 64, false);
	this->animationComponent->addAnimotion("MOVE_UP_LEFT", 1.f, 29, 0, 7, 0, 96, 64, true);
	this->animationComponent->addAnimotion("MOVE_UP", 1.f, 37, 0, 7, 0, 96, 64, false);

}

void HeroInstance::setTexture(sf::Texture & sheetTexture)
{
	int heightPixel = this->getHeight()*(int)TILEWIDTH;
	int widthPixel = this->getWidth()*(int)TILEWIDTH;
	sf::IntRect rect(0, 0, widthPixel, heightPixel);
	
	this->sprite.setTexture(sheetTexture);
	this->sprite.setTextureRect(rect);
	this->sprite.setOrigin( // change orgin to hero's visitable tile
		(this->getWidth() - 2)*TILEWIDTH,
		(this->getHeight() - 1)*TILEWIDTH);
}

void HeroInstance::setType(int type)
{
	assert(type == Obj::HERO);
}

void HeroInstance::setTilePos(const sf::Vector2i& pos)
{
	MP2::ObjectInstance::setTilePos(pos);
	
}

void HeroInstance::afterAddToMap()
{
	world.vec_heros.push_back(this);
	std::cout << "dodaem herosa "<<this->id << std::endl;
}

void HeroInstance::animationUpdate(const float & dt)
{
	if (this->movmentComponent->getState(IDLE))
	{
		if (lastMove == MOVING_DOWN)
			this->animationComponent->paly("IDLE_DOWN", dt);
		if (lastMove == MOVING_UP)
			this->animationComponent->paly("IDLE_UP", dt);
		if (lastMove == MOVING_UP_RIGHT)
			this->animationComponent->paly("IDLE_UP_RIGHT", dt);
		if (lastMove == MOVING_DOWN_RIGHT)
			this->animationComponent->paly("IDLE_DOWN_RIGHT", dt);
		if (lastMove == MOVING_RIGHT)
			this->animationComponent->paly("IDLE_RIGHT", dt);
		if (lastMove == MOVING_LEFT)
			this->animationComponent->paly("IDLE_LEFT", dt);
		if (lastMove == MOVING_DOWN_LEFT)
			this->animationComponent->paly("IDLE_DOWN_LEFT", dt);
		if (lastMove == MOVING_UP_LEFT)
			this->animationComponent->paly("IDLE_UP_LEFT", dt);
	}
	else if (this->movmentComponent->getState(MOVING_UP_RIGHT))
	{
		this->animationComponent->paly("MOVE_UP_RIGHT", dt);
		lastMove = MOVING_UP_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->paly("MOVE_RIGHT", dt);
		lastMove = MOVING_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN_RIGHT))
	{
		this->animationComponent->paly("MOVE_DOWN_RIGHT", dt);
		lastMove = MOVING_DOWN_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->paly("MOVE_LEFT", dt);
		lastMove = MOVING_LEFT;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->paly("MOVE_DOWN", dt);
		lastMove = MOVING_DOWN;
	}
	else if (this->movmentComponent->getState(MOVING_UP))
	{
		this->animationComponent->paly("MOVE_UP", dt);
		lastMove = MOVING_UP;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN_LEFT))
	{
		this->animationComponent->paly("MOVE_DOWN_LEFT", dt);
		lastMove = MOVING_DOWN_LEFT;
	}
	else if (this->movmentComponent->getState(MOVING_UP_LEFT))
	{
		this->animationComponent->paly("MOVE_UP_LEFT", dt);
		lastMove = MOVING_UP_LEFT;
	}
}

void HeroInstance::update(const float & dt)
{
	MP2:ObjectInstance::update(dt);
	this->animationUpdate(dt);
	this->movmentComponent->update(dt);

	if (this->movmentComponent->isHeroChangedPos())
	{
		sf::Vector2i heroPos = this->movmentComponent->getActualHeroTilePos();
		//erace arrow
		Interface::GetHeroMoveArrows().eraseArrow(heroPos);
		//scoute
		world.revealTilesInRange(heroPos, this->getSightRadius(), this->getOwner());
		//this->sprite.setPosition(spritePos * TILEWIDTH);
	}
		
	if (this->movmentComponent->isPathEnded())
	{
		this->isStanding = true;
		//this->setTilePos(this->movmentComponent->getActualHeroTilePos());
		world.changeObjPos(this->id, this->pos, this->movmentComponent->getActualHeroTilePos());
		for (auto i : world.vec_heros)
		{
			i->pathfinder->initializeGraph();
			i->pathfinder->calculatePaths();
		}
	}
}

void HeroInstance::render(sf::RenderTarget * target)
{
	MP2:ObjectInstance::render(target);
}

void HeroInstance::save(std::fstream & file)
{
	MP2::ObjectInstance::save(file);
	//zapisz patrol
	// umiejetonsci
}

void HeroInstance::load(std::fstream & file)
{
	MP2::ObjectInstance::load(file);
}
