#include "pch.h"
#include "MapObject.h"
#include "World.h"

static int countID = 0;
int MP2::ObjectInstance::getWidth() const
{
	if (this->getHeight() > 0)
		return (int)usedTiles[0].size();
	return 0;
}

int MP2::ObjectInstance::getHeight() const
{
	return (int)usedTiles.size();
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
	this->ownerColor = ow;
}

void MP2::ObjectInstance::setTexture(sf::Texture & sheetTexture)
{
	//int heightPixel = this->getHeight()*(int)TILEWIDTH;
	//int widthPixel = this->getWidth()*(int)TILEWIDTH;
	//sf::IntRect rect(0, 0, widthPixel, heightPixel);
	//rect.left = ((int)rand() % sheetTexture.getSize().x / widthPixel) * widthPixel;
	this->sprite.setTexture(sheetTexture);
	//this->sprite.setTextureRect(rect);
	this->sprite.setOrigin( // change orgin to RIGHT-BOTTOM corner
		(this->getWidth() - 1)*TILEWIDTH,
		(this->getHeight() - 1)*TILEWIDTH);
}

void MP2::ObjectInstance::initObjAnimaiton()
{
	int heightPixel = this->getHeight()*(int)TILEWIDTH;
	int widthPixel = this->getWidth()*(int)TILEWIDTH;
	if(type != Obj::DWELLING)
		this->animationComponent = new AnimotionComponent(this->sprite, *graphics.mapObjects[{this->type, this->subType}]);
	else
		this->animationComponent = new AnimotionComponent(this->sprite, *graphics.mapDwelling[this->subType]);
	this->animationComponent->addAnimotion("IDLE", 3.f, 0, 0, this->numberOfFrameAnimation, 0, widthPixel, heightPixel, false);

}

void MP2::ObjectInstance::initObj()
{

	if (mapObjectsStats.find({ this->type, this->subType }) == mapObjectsStats.end())
	{
		std::cout << "error: object type not exist" << this->type << std::endl;
		assert(0);
	}
	MapObjectParametrs& stats = mapObjectsStats[{this->type, this->subType}];
	this->instanceName = stats.name;
	this->setSize(stats.width, stats.height);
	this->usedTiles = stats.usedTlies;
	this->visitDir = stats.visitDir;
	this->blockVisit = stats.blockVisit;
	this->numberOfFrameAnimation = stats.frameAnimation;
	this->setOwner(Color::UNUSED);

	this->priority = 2;

	if (this->type == Obj::DWELLING)
		this->setTexture(*graphics.mapDwelling[this->subType]);
	else
		this->setTexture(*graphics.mapObjects[{this->type, this->subType}]);
	this->initObjAnimaiton();
}

void MP2::ObjectInstance::setType(int32_t type, int subType)
{
	this->type = Obj(type);
	this->subType = subType;
}

std::string MP2::ObjectInstance::getObjectName() const
{
	return this->instanceName;
}

std::string MP2::ObjectInstance::getHoverText(const HeroInstance * hero) const
{
	return this->getObjectName();
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
	else std::cout<<"obiekt zostl wstawiony: Poza mape"<<std::endl;
}

bool MP2::ObjectInstance::isVisitable() const
{
	for (auto & line : usedTiles)
		for (auto & tile : line)
			if (tile == BlockMapBits::VISITABLE)
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

void MP2::ObjectInstance::onHeroVisit(const HeroInstance * h)
{
	switch (type)
	{
	case Obj::TAVERN:
	{
		PI->openWindow(h->ownerColor,this);
		break;
	}
	}
}

void MP2::ObjectInstance::afterAddToMap()
{
	
}

void MP2::ObjectInstance::load(std::fstream & file)
{
	int temp;
	file >> pos.x >> pos.y;
	this->setTilePos(sf::Vector2i(pos.x, pos.y));
	file >> temp >> subType;
	this->setType(Obj(temp),subType);
	file >> ownerColor >> id;
	this->setOwner(this->ownerColor);
	initObj();
}

void MP2::ObjectInstance::save(std::fstream & file)
{
	file <<" "<< pos.x << " " << pos.y << " ";
	file << type.num << " " << subType << " ";
	file << ownerColor << " " << id << " ";
}

int & MP2::ObjectInstance::getCountID()
{
	return countID;
}

void MP2::ObjectInstance::animationUpdate(const float& dt)
{
	if(this->animationComponent)
		this->animationComponent->paly("IDLE", dt);
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
	this->toDelete = false;
	this->id = countID++;
	this->pos = sf::Vector2i(-1, -1);
	this->type = Obj::NO_OBJ;
	this->subType = -1;
	this->blockVisit = false;
	this->numberOfFrameAnimation = 0;
}

MP2::ObjectInstance::~ObjectInstance()
{
	delete this->animationComponent;
}
