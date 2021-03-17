#pragma once
#include "MapObject.h"
#include "MovmentComponent.h"
#include "GameConstants.h"

namespace MP2
{
	class ObjectInstance;
}

struct Troop
{
	Monster monster;
	int count;
};

class HeroInstance : public MP2::ObjectInstance
{
private:
	//std::set<SpellID> spells;
	//std::set<ObjectInstanceID> visitedObjects;
	//Patrol patrol;
	movment_state lastMove;
	bool isStanding;

	MovmentComponent* movmentComponent;

	
public:
	std::vector<Troop> troops;

	HeroName name;
	std::shared_ptr<Pathfinder> pathfinder;
	std::shared_ptr<Path> currentPath;
	
	bool moveHero();
	bool makePath(sf::Vector2i dest);
	void calcuatePaths();

	int movement;
	HeroInstance();
	virtual ~HeroInstance();

	int getTileCost(const Maps::Tile & dest, const Maps::Tile & from) const;
	int getMaxMovePoints() const;
	
	void initHero();

	int getSightRadius() const override;
	void initObj() override;
	void initObjAnimaiton() override;
	void setTexture(sf::Texture& sheetTexture) override;
	void setType(int type) override;
	void setTilePos(const sf::Vector2i& pos) override;
	void afterAddToMap() override;
	virtual std::string getObjectName() const;
	std::string getHoverText(const HeroInstance* hero) const override;
	void onHeroVisit(const HeroInstance * h) const override;
	void animationUpdate(const float& dt) override;
	void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target);

	void save(std::fstream& file) override;
	void load(std::fstream& file) override;
};
