#include "pch.h"
#include "MapObject.h"
#include "World.h"

static int countID = 0;
int MP2::ObjectInstance::getWidth() const
{
	if (this->getHeight() > 0)
		return usedTiles[0].size();
	return 0;
}

int MP2::ObjectInstance::getHeight() const
{
	return usedTiles.size();
}

bool MP2::ObjectInstance::visitableAt(int x, int y) const
{
	if (!world.isInTheMap(sf::Vector2i(x, y)))
		return false;
	if (this->usedTiles[this->pos.y - y][this->pos.x - x] == BlockMapBits::VISITABLE)
		return true;
	return false;
}

bool MP2::ObjectInstance::blockingAt(int x, int y) const
{
	if(!world.isInTheMap(sf::Vector2i(x,y)))
		return false;
	if(this->usedTiles[this->pos.y-y][this->pos.x-x] == BlockMapBits::BLOCKED)
		return true;
	return false;
}

int MP2::ObjectInstance::getOwner() const
{
	return ownerColor;
}

sf::Vector2i MP2::ObjectInstance::getSightCenter() const
{
	return this->getVisitablePos();
}

int MP2::ObjectInstance::getSightRadius() const
{
	return 3;
}

void MP2::ObjectInstance::setOwner(int ow)
{
	ownerColor = ow;
}

void MP2::ObjectInstance::setTexture(sf::Texture & sheetTexture)
{
	int heightPixel = this->getHeight()*(int)TILEWIDTH;
	int widthPixel = this->getWidth()*(int)TILEWIDTH;
	sf::IntRect rect(0, 0, widthPixel, heightPixel);
	rect.left = ((int)rand() % sheetTexture.getSize().x / widthPixel) * widthPixel;
	
	this->sprite.setTexture(sheetTexture);
	this->sprite.setTextureRect(rect);
	this->sprite.setOrigin( // change orgin to RIGHT-BOTTOM corner
		(this->getWidth() - 1)*TILEWIDTH,
		(this->getHeight() - 1)*TILEWIDTH);
}

void MP2::ObjectInstance::initObjAnimaiton()
{
}

void MP2::ObjectInstance::initObj()
{
	switch (this->type)
	{
	case Obj::STABLES:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Stables";
		this->setSize(3, 2);
		this->usedTiles = { {2,4,1},{1,4,1} }; // BLOCKED = 4, VISITABLE = 2,VISIBLE = 1
		this->visitDir = DIRECTION_BOTTOM_ROW | DIRECTION_CENTER_ROW;
		break;
	case Obj::TRADING_POST:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Trading Post";
		this->setSize(3, 3);
		this->usedTiles = { {2,4,1}, {1,1,1}, {1,1,1} };
		this->visitDir = DIRECTION_BOTTOM_ROW | DIRECTION_CENTER_ROW;
		break;
	case Obj::CRATER:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Crater";
		this->setSize(2, 2);
		this->usedTiles = { {4,4},{4,4} };
		break;
	case Obj::MOUNTS1:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Mounts1";
		this->setSize(4, 3);
		this->usedTiles = { {1,4,1,1},{1,4,4,1},{1,4,4,4} };
		this->visitDir = Direction::UNKNOWN;
		break;
	case Obj::MOUNTS2:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Mounts2";
		this->setSize(4, 2);
		this->usedTiles = { {1,4,4,1},{1,1,4,4} };
		break;
	case Obj::ARENA:
		this->setOwner(Color::UNUSED);
		this->instanceName = "Arena";
		this->setSize(3, 3);
		this->usedTiles = { {4,2,4},{4,4,4},{1,1,1} };
		this->visitDir = DIRECTION_BOTTOM_ROW | DIRECTION_CENTER_ROW;
		break;

	default:
		std::cout << "error: object type not exist" << this->type << std::endl;
		assert(0);
		break;
	}

	//this->sprite.setOrigin( // change orgin to RIGHT-BOTTOM corner
	//	this->sprite.getLocalBounds().width,
	//	this->sprite.getLocalBounds().height);
	this->setTexture(*graphics.mapObjects[type]);
}

void MP2::ObjectInstance::setType(int32_t type)
{

	this->type = Obj(type);
	
}

void MP2::ObjectInstance::setSize(unsigned width, unsigned height)
{
	usedTiles.resize(height);
	for (auto & line : usedTiles)
		line.resize(width, 0);
}

void MP2::ObjectInstance::setTilePos(const sf::Vector2i& pos)
{
	if (world.isInTheMap(pos))
	{
		this->pos = pos;
		this->sprite.setPosition(sf::Vector2f(pos.x*TILEWIDTH, pos.y*TILEWIDTH));
	}
	else std::cout<<"obiekt nie zostl wstawiony: Poza mapa"<<std::endl;
}

bool MP2::ObjectInstance::isVisitable() const
{
	for (auto & line : usedTiles)
		for (auto & tile : line)
			if (tile & BlockMapBits::VISITABLE)
				return true;
	return false;
}

bool MP2::ObjectInstance::isVisitableFrom(int dir) const
{
	if (this->visitDir & dir) 
		return true;
	return false;
}

sf::Vector2i MP2::ObjectInstance::getVisitablePos() const
{
	for (int y = 0; y < getHeight(); y++)
		for (int x = 0; x < getWidth(); x++)
			if (usedTiles[y][x] & BlockMapBits::VISITABLE)
				return sf::Vector2i(pos.x - x, pos.y - y);

	//logGlobal->warn("Warning: getVisitableOffset called on non-visitable obj!");
	return sf::Vector2i(0, 0);
}

void MP2::ObjectInstance::onHeroVisit(const HeroInstance * h) const
{
}

void MP2::ObjectInstance::afterAddToMap()
{
	
}

void MP2::ObjectInstance::load(std::fstream & file)
{
	int temp;
	file >> pos.x >> pos.y;
	setTilePos(sf::Vector2i(pos.x, pos.y));
	file >> temp >> subType;
	setType(temp);
	file >> ownerColor;
	initObj();
}

void MP2::ObjectInstance::save(std::fstream & file)
{
	file <<" "<< pos.x << " " << pos.y << " ";
	file << type.num << " " << subType << " ";
	file << ownerColor;
	id = countID++;
}

void MP2::ObjectInstance::animationUpdate(const float& dt)
{
}

void MP2::ObjectInstance::update(const float & dt)
{
	this->animationUpdate(dt);
}

void MP2::ObjectInstance::render(sf::RenderTarget * target)
{
}


MP2::ObjectInstance::ObjectInstance()
{
	toDelete = false;
	id = countID++;
	pos = sf::Vector2i(-1, -1);
	type = Obj::NO_OBJ;
	subType = -1;
	blockVisit = false;
}

MP2::ObjectInstance::~ObjectInstance()
{
}
