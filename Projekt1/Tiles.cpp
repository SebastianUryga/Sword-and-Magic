#include "pch.h"
#include "Tiles.h"

int Maps::GetDirectionIndex(int from, int dir)
{
	switch (dir)
	{
	case Direction::TOP:		return from - world.w();
	case Direction::TOP_RIGHT:	return from - world.w() + 1;
	case Direction::RIGHT:		return from + 1;
	case Direction::BOTTOM_RIGHT:	return from + world.w() + 1;
	case Direction::BOTTOM:		return from + world.w();
	case Direction::BOTTOM_LEFT:	return from + world.w() - 1;
	case Direction::LEFT:		return from - 1;
	case Direction::TOP_LEFT:	return from - world.w() - 1;
	default: break;
	}

	return -1;
}
std::string Maps::Ground::String(int ground)
{
	std::string str_ground[] = { "Desert", "Snow", "Swamp", "Wasteland", "Beach",
			"Lava", "Dirt", "Grass", "Water", "Unknown" };

	switch (ground)
	{
	case DESERT:	return str_ground[0];
	case SNOW:	return str_ground[1];
	case SWAMP:	return str_ground[2];
	case WASTELAND:	return str_ground[3];
	case BEACH:	return str_ground[4];
	case LAVA:	return str_ground[5];
	case DIRT:	return str_ground[6];
	case GRASS:	return str_ground[7];
	case WATER:	return str_ground[8];
	default: break;
	}

	return str_ground[8];
}

int Maps::Ground::GetPenalty(int index, int direction, int pathfinding)
{
	int result = 100;

	if (direction & (Direction::TOP_RIGHT | Direction::BOTTOM_RIGHT | Direction::BOTTOM_LEFT | Direction::TOP_LEFT))
		result += result * 55 / 100;

	return result;
}

void Maps::Tile::Init(int index)
{
	this->visitable = false;
	this->blocked = false;
	this->fog_colors = Color::UNUSED;
	this->SetIndex(index);
	this->SetRoad(RoadType::NO_ROAD);
	this->groundSprite.setPosition(index % world.w() * TILEWIDTH, index / world.w() * TILEWIDTH);
	this->groundRect = sf::IntRect(std::rand() % 6 * (int)TILEWIDTH, std::rand() % 2 * (int)TILEWIDTH, 32, 32);
	this->roadSprite.setPosition(this->groundSprite.getPosition());
	this->roadSprite.move(0, TILEWIDTH / 2);
}

Maps::Tile::Tile()
{
	this->roadType = RoadType::NO_ROAD;
}


Maps::Tile::~Tile()
{
	this->objects.clear();
}

// Acesors
MP2::ObjectInstance* Maps::Tile::GetObjectPtr() const
{
	if(this->objects.size())
		return *(this->objects.end()-1);
	return nullptr;
}

int Maps::Tile::GetIndex() const
{
	return this->maps_index;
}

int Maps::Tile::GetGround() const
{
	return this->ground;
}

int Maps::Tile::GetRoad() const
{
	return this->roadType;
}
bool Maps::Tile::isBlocked() const
{
	return this->blocked;
}
bool Maps::Tile::isVisitable() const
{
	return this->visitable;
}
//Modifires
void Maps::Tile::SetIndex(int index)
{
	this->maps_index = index;
	//set sprite position
	sf::Vector2f pos(index % world.w()* TILEWIDTH, index / world.w()* TILEWIDTH);
	this->groundSprite.setPosition(pos);
	this->shape = sf::FloatRect(pos.x, pos.y, TILEWIDTH, TILEWIDTH);
}

void Maps::Tile::SetObjectType(int type)
{
	this->objectType = Obj(type);
}

void Maps::Tile::SetObject(MP2::ObjectInstance* object)
{
	*(this->objects.end()-1) = object;
}

void Maps::Tile::addMapObject(MP2::ObjectInstance * object)
{
	this->objects.push_back(object);

	this->objectType = this->GetObjectPtr()->type;
}

void Maps::Tile::removeMapObject(MP2::ObjectInstance* object)
{
	for(int i = 0 ; i < objects.size() ; i++)
	{
		if (objects[i]->toDelete || object->id == objects[i]->id)
		{
			objects[i] = nullptr;
			objects.erase(objects.begin() + i);
		}
		if (!objects.empty())
			this->objectType = this->GetObjectPtr()->type;
		else
			this->SetObjectType(MP2::OBJ_ZERO);
	}
}

void Maps::Tile::SetRoad(int road)
{
	if (this->GetGround() == road)
		return;
	this->roadType = road;

	sf::Vector2i mapPos(
		this->maps_index % world.w(),
		this->maps_index / world.w());

	Graphics::updateRoadTexture(mapPos);
	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1),
		sf::Vector2i(-1, +0),   /* source pos */   sf::Vector2i(+1, +0),
		sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1)
	};
	for (int i = 0; i < 8; i++)
	{
		if (world.isInTheMap(mapPos + dirs[i]))
			Graphics::updateRoadTexture(mapPos + dirs[i]);
	}
}

void Maps::Tile::SetGround(int ground)
{
	this->ground = ground;
	this->setGroundTexture(*graphics.grounds[ground]);
}

void Maps::Tile::setFogTexture(sf::Texture & texture,int color)
{
	this->fogRect.left = ((int)rand() % texture.getSize().x / (int)TILEWIDTH) * (int)TILEWIDTH;
	this->fogRect.top = ((int)rand() % texture.getSize().y / (int)TILEWIDTH) * (int)TILEWIDTH;
	this->fogSprite.setTexture(texture);
	this->fogSprite.setTextureRect(this->fogRect);
}

void Maps::Tile::setGroundTexture(sf::Texture & texture)
{
	this->groundRect.left = ((int)rand() % texture.getSize().x / (int)TILEWIDTH) * (int)TILEWIDTH;
	this->groundRect.top = ((int)rand() % texture.getSize().y / (int)TILEWIDTH) * (int)TILEWIDTH;
	this->groundSprite.setTexture(texture);
	this->groundSprite.setTextureRect(this->groundRect);
}

bool Maps::Tile::isWater() const
{
	return ground == Ground::WATER;
}

bool Maps::Tile::isFog(int color) const
{
	if (this->fog_colors & color)
		return true;
	return false;
}

void Maps::Tile::ClearFog(int color)
{
	fog_colors &= ~color;
}

void Maps::Tile::updatePassable()
{
	this->visitable = false;
	this->blocked = false;
	for (auto obj : this->objects)
	{
		if (obj->visitableAt(
			this->maps_index % world.w(),
			this->maps_index / world.w()))
		{
			this->visitable = true;
		}
			
		if (obj->blockingAt(
			this->maps_index % world.w(),
			this->maps_index / world.w()))
		{
			this->blocked = true;
		}		
	}
}

void Maps::Tile::update()
{
	this->updatePassable();
}

void Maps::Tile::renderGround(sf::RenderTarget * target)
{
	static sf::RectangleShape shape;
	target->draw(this->groundSprite);
	//if(this->visitable || this->blocked)
	if (this->GetGround()==RoadType::GRAVEL_ROAD)
	{
		shape.setPosition(groundSprite.getPosition());
		shape.setSize(sf::Vector2f(30, 30));
		if (this->visitable)
			shape.setFillColor(sf::Color(59,59,59,20));
		else
			shape.setFillColor(sf::Color(59, 59, 59, 20));

		target->draw(shape);
	}
	
}

void Maps::Tile::renderRoad(sf::RenderTarget * target)
{
	if (this->roadType == RoadType::NO_ROAD)
		return;
	target->draw(this->roadSprite);
}

void Maps::Tile::renderFog(sf::RenderTarget * target)
{
	target->draw(this->fogSprite);
}

void Maps::Tile::load(std::fstream& file)
{
	int temp = 0;
	file >> maps_index >> ground >> temp;
	Init(maps_index);
	SetGround(ground);
	SetRoad(temp);
}

void Maps::Tile::save(std::fstream & file)
{
	file << maps_index <<" "<< ground << " " << roadType << " ";
}
