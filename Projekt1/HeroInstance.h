#pragma once
#include "MapObject.h"
#include "MovmentComponent.h"

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
	std::shared_ptr<Pathfinder> pathfinder;
	std::shared_ptr<Path> currentPath;

	bool moveHero(sf::Vector2i dest);
	bool makePath(sf::Vector2i dest);
	void showPath();
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

	void animationUpdate(const float& dt) override;
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	void save(std::fstream& file) override;
	void load(std::fstream& file) override;
};

