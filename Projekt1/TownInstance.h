
#pragma once
#include "MapObject.h"
#include "Fraction.h"
#include "Direction.h"
class TownInstance;

class Building
{
public:
	std::string name;
	BuildingID id;
	BuildingID upgrade;
	int cost;

	int objectId;
	MP2::ObjectInstance* visibleMapObject;
	sf::Vector2i mapObjectPos;

	TownInstance* owner;

	Building();
	virtual ~Building();

	void setType(BuildingID id);
};

class TownInstance :
	public MP2::ObjectInstance
{
public:
	Fraction* fraction;
	std::vector<Building*> buldings;
	std::vector<Troop> troops;
	void putBuildingsOnMap(const sf::Vector2i pos);
	void setObjectsToBuildings();
	TownInstance();
	virtual ~TownInstance();

	void setOwner(int ow) override;
	void initObj() override;
	void setTexture(sf::Texture& sheetTexture) override;
	void setType(int type, int subType = 0) override;
	void setTilePos(const sf::Vector2i& pos) override;
	void afterAddToMap() override;
	void onHeroVisit(const HeroInstance * h) override;
	void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target);

	void save(std::fstream& file) override;
	void load(std::fstream& file) override;
};
