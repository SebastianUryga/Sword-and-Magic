#include "pch.h"
#include "HeroInstance.h"
#include "World.h"


bool HeroInstance::moveHero()
{
	if (currentPath && isStanding)
	{
		this->movmentComponent->startMoving();
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
		this->movmentComponent->setNewPath(this->currentPath);
	}
	else
		this->currentPath = nullptr;

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
	this->ownerColor = Color::UNUSED;
}


HeroInstance::~HeroInstance()
{

	MP2::ObjectInstance::~ObjectInstance();
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
	this->priority = 5;
	this->pathfinder = std::make_shared<Pathfinder>(sf::Vector2i (world.w(), world.h()), this);
	//this->pathfinder->initializeGraph();
	this->currentPath = nullptr;
	this->movmentComponent = new MovmentComponent(this->sprite);
	this->setTexture(*graphics.heroOnMapSheet);
}

int HeroInstance::getSightRadius() const
{
	return 5;// + bonus
}

void HeroInstance::setOwner(int ow)
{
	Kingdom & player = world.GetKingdom(this->getOwner());
	auto hero = std::find(player.heroes.begin(), player.heroes.end(), this);
	if (hero != player.heroes.end())
		player.heroes.erase(hero);

	MP2::ObjectInstance::setOwner(ow);
	player = world.GetKingdom(ow);
	player.heroes.push_back(this);
	if(PI->gameArea)
		PI->gameArea->playerListOfHero->update();

	world.revealTilesInRange(
		this->getVisitablePos(),
		this->getSightRadius(),
		this->ownerColor
	);
}

void HeroInstance::initObj()
{
	// init simple Troops
	troops.resize(7);

	switch (this->subType)
	{
	case HeroClass::KNIGHT:
		troops = { {Monster::PIKEMAN, 5},{Monster::SWORDSMAN, 4},{Monster::ARCHER, 2},
		{Monster::ARCHER, 4} ,{Monster::PIKEMAN, 2}, {Monster::NO_CREATURE, 0} ,{Monster::NO_CREATURE, 0} };
		break;
	case HeroClass::CLERIC:
		troops = { {Monster::PIKEMAN, 15},{Monster::GRIFFIN, 5},{Monster::ARCHER, 5},
		{Monster::MARKSMEN, 7} ,{Monster::NO_CREATURE, 0}, {Monster::NO_CREATURE, 0} ,{Monster::NO_CREATURE, 0} };
		break;
	default:
		troops = { {Monster::NO_CREATURE, 0},{Monster::NO_CREATURE, 0},
		{Monster::NO_CREATURE, 0}, {Monster::NO_CREATURE, 0}, {Monster::NO_CREATURE, 0},
		{Monster::NO_CREATURE, 0},{Monster::NO_CREATURE, 0} };
		
		break;
	}
	//this->setOwner(Color::BLUE);//  do zmiany
	this->setSize(3, 2);
	this->usedTiles = { { 2,1,1 }, {1,1,1} };
	this->visitDir = DIRECTION_ALL;
	this->blockVisit = true;
	this->initHero();
	this->initObjAnimaiton();
}

void HeroInstance::initObjAnimaiton()
{
	this->animationComponent = new AnimotionComponent(this->sprite, *graphics.heroOnMapSheet);
	sf::IntRect squre = Graphics::selectHeroOnMap((HeroClass)this->subType);
	sf::Vector2f orgin(TILEWIDTH, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_DOWN",10.f,squre.left,
		squre.top, 0, 0, 96, 64, false, orgin,TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_DOWN_RIGHT", 10.f, squre.left+1,
		squre.top, 0, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_DOWN_LEFT", 10.f, 1,
		squre.top, 0, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_RIGHT", 10.f, 2,
		squre.top, 0, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_LEFT", 10.f, 2,
		squre.top, 0, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_UP_RIGHT", 10.f, 3,
		squre.top, 0, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_UP_LEFT", 10.f, 3,
		squre.top, 0, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("IDLE_UP", 10.f, 4,
		squre.top, 0, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_DOWN", 1.f, 5,
		squre.top, 7, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_DOWN_RIGHT", 1.f, 13,
		squre.top, 7, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_DOWN_LEFT", 1.f, 13,
		squre.top, 7, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_RIGHT", 1.f, 21,
		squre.top, 7, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_LEFT", 1.f, 21,
		squre.top, 7, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_UP_RIGHT", 1.f, 29,
		squre.top, 7, 0, 96, 64, false, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_UP_LEFT", 1.f, 29,
		squre.top, 7, 0, 96, 64, true, orgin, TILEWIDTH);
	this->animationComponent->addAnimotion("MOVE_UP", 1.f, 37,
		squre.top, 7, 0, 96, 64, false, orgin, TILEWIDTH);

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

void HeroInstance::setType(int type, int subType)
{
	assert(type == Obj::HERO);
	this->subType = subType;
}

void HeroInstance::setTilePos(const sf::Vector2i& pos)
{
	if (world.isInTheMap(pos))
	{
		this->pos = pos;
		if(isStanding)
			this->sprite.setPosition(sf::Vector2f(pos.x*TILEWIDTH, pos.y*TILEWIDTH));
	}
	else std::cout << "obiekt nie zostl wstawiony: Poza mapa" << std::endl;
	
}

void HeroInstance::afterAddToMap()
{
	std::vector<HeroInstance*> & vec = world.vec_heros;
	auto hero = std::find(vec.begin(), vec.end(), this);
	if (hero == vec.end())
	{
		vec.push_back(this);
		PI->playerHeroes.push_back(this);
		if (PI->gameArea)
			PI->gameArea->playerListOfHero->addHero(this);
	}
	else
		std::cout << "Hero is already existing in world" << std::endl;
}

std::string HeroInstance::getObjectName() const
{
	return MP2::ObjectInstance::getObjectName();
}

std::string HeroInstance::getHoverText(const HeroInstance * hero) const
{
	return std::string(this->subTypeName);
}

void HeroInstance::onHeroVisit(const HeroInstance * h)
{
	// if enemy start battle
	// if fiend open exchangeing window
}

void HeroInstance::animationUpdate(const float & dt)
{
	if (this->movmentComponent->getState(IDLE))
	{
		if (lastMove == MOVING_DOWN)
			this->animationComponent->play("IDLE_DOWN", dt, false);
		if (lastMove == MOVING_UP)
			this->animationComponent->play("IDLE_UP", dt,false);
		if (lastMove == MOVING_UP_RIGHT)
			this->animationComponent->play("IDLE_UP_RIGHT", dt, false);
		if (lastMove == MOVING_DOWN_RIGHT)
			this->animationComponent->play("IDLE_DOWN_RIGHT", dt, false);
		if (lastMove == MOVING_RIGHT)
			this->animationComponent->play("IDLE_RIGHT", dt, false);
		if (lastMove == MOVING_LEFT)
			this->animationComponent->play("IDLE_LEFT", dt, true);
		if (lastMove == MOVING_DOWN_LEFT)
			this->animationComponent->play("IDLE_DOWN_LEFT", dt, true);
		if (lastMove == MOVING_UP_LEFT)
			this->animationComponent->play("IDLE_UP_LEFT", dt, true);
	}
	else if (this->movmentComponent->getState(MOVING_UP_RIGHT))
	{
		this->animationComponent->play("MOVE_UP_RIGHT", dt, false);
		lastMove = MOVING_UP_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("MOVE_RIGHT", dt, false);
		lastMove = MOVING_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN_RIGHT))
	{
		this->animationComponent->play("MOVE_DOWN_RIGHT", dt, false);
		lastMove = MOVING_DOWN_RIGHT;
	}
	else if (this->movmentComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("MOVE_LEFT", dt, true);
		lastMove = MOVING_LEFT;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("MOVE_DOWN", dt, false);
		lastMove = MOVING_DOWN;
	}
	else if (this->movmentComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("MOVE_UP", dt, false);
		lastMove = MOVING_UP;
	}
	else if (this->movmentComponent->getState(MOVING_DOWN_LEFT))
	{
		this->animationComponent->play("MOVE_DOWN_LEFT", dt, true);
		lastMove = MOVING_DOWN_LEFT;
	}
	else if (this->movmentComponent->getState(MOVING_UP_LEFT))
	{
		this->animationComponent->play("MOVE_UP_LEFT", dt, true);
		lastMove = MOVING_UP_LEFT;
	}
}

void HeroInstance::update(const float & dt)
{
	this->animationUpdate(dt);
	this->movmentComponent->update(dt);
	if (!this->isStanding)
	{PI->focusOn(this->sprite.getPosition());
	}
		
	if (this->movmentComponent->isHeroChangedPos())
	{
		sf::Vector2i heroPos = this->movmentComponent->getActualHeroTilePos();
		//erace arrow
		world.changeObjPos(this->id, this->pos, heroPos);
		/*this->pos = heroPos;
		world.sortObjects();
		std::cout <<pos.x<< " " << pos.y << std::endl;*/
		Interface::GetHeroMoveArrows().eraseArrow(heroPos);
		//subtract movmentpoint
		auto pn = this->pathfinder->getNode(heroPos);
		this->movement = pn->moveRemains;
		//if (pn.moveRemains != this->movement) std::cout << "klopoty z ruchem" << std::endl;
		//scoute
		world.revealTilesInRange(heroPos, this->getSightRadius(), this->getOwner());
	}
		
	if (this->movmentComponent->isPathEnded())
	{
		sf::Vector2i heroPos = this->movmentComponent->getActualHeroTilePos();
		if (this->currentPath->nodes[0].accessible == PathNode::BLOCKVIS &&
			heroPos == this->currentPath->nodes[1].coord)
		{
			PathNode* pn = this->pathfinder->getNode(this->currentPath->endPos());
			this->movement = pn->moveRemains;
			Maps::Tile & dest = world.GetTile(pn->coord);
			dest.GetObjectPtr()->onHeroVisit(this);
		}
			
		this->isStanding = true;
		this->currentPath = nullptr;
		world.changeObjPos(this->id, this->pos, heroPos);
		
		PI->canCalcuatePaths = true;
		//compiutingPahts.join();
		
		/*this->pathfinder->initializeGraph();
		this->pathfinder->calculatePaths();*/
	}
}

void HeroInstance::render(sf::RenderTarget * target)
{
	MP2::ObjectInstance::render(target);
}

void HeroInstance::save(std::fstream & file)
{
	file << name << " ";
	MP2::ObjectInstance::save(file);
	for (auto troop : this->troops)
	{
		file << " " << troop.monster.monster << " " << troop.count << " ";
	}
	//zapisz garnizon
	// umiejetonsci
}

void HeroInstance::load(std::fstream & file)
{
	MP2::ObjectInstance::load(file);
	for (auto& troop : this->troops)
	{
		int type;
		file >> type >> troop.count;
		Monster temp(type);
		troop.monster = temp;
	}
}
