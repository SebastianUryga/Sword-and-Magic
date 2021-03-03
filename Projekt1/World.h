#pragma once
#include "interface_gamearea.h"
#include "Tiles.h"
//#include "HeroInstance.h"

namespace Maps
{
	class Tile;
}
class Kingdom;

class World
{
private:
	//Variables
	int width;
	int height;
	
	std::vector<Maps::Tile> vec_tiles;
	std::vector<Kingdom*> vec_kingdoms;
	std::vector<MP2::ObjectInstance*> vec_objects;
	std::vector < HeroInstance* > allHeroes;
	World() :width(0), height(0) {};
public:
	std::vector<HeroInstance*> vec_heros;
	std::vector<std::vector<sf::Vector2i>> guardingCreaturePositions;

	void initAllHeroes();
	void initKingdoms();
	void initFogOfWar();
	void ClearFog(int color);

	void Reset();
	void NewMaps(int sw, int sh);

	void sortObjects();
	void addBlockVisTiles(MP2::ObjectInstance * obj); // mozna zrobiæ zeby bylo ladniej
	void removeBlockVisTiles(MP2::ObjectInstance * obj, bool total);
	void addMapObject(MP2::ObjectInstance* obj);
	void removeMapObject(sf::Vector2i pos);
	void changeObjPos(int id, sf::Vector2i oldPos,sf::Vector2i newPos);
	void revealTilesInRange(sf::Vector2i pos, int radious, int playerColor);

	virtual ~World();
	
	bool canMoveBetween(const sf::Vector2i &src, const sf::Vector2i &dst) const;
	//Accesors
	sf::Vector2i guardingCreaturePosition(sf::Vector2i pos) const;
	bool isInTheMap(const sf::Vector2i& pos);
	static World &	Get();
	Maps::Tile & GetTile(int x, int y);
	Maps::Tile & GetTile(int index);
	Maps::Tile & GetTile(sf::Vector2i pos);
	MP2::ObjectInstance GetObject(int id);
	MP2::ObjectInstance* GetObjectByPos(sf::Vector2i pos);
	std::vector<MP2::ObjectInstance*> & GetAllMapsObjects() { return vec_objects; }
	Kingdom & GetKingdom(int color);
	HeroInstance * getRandomHero();
	

	int w() const;
	int h() const;
	//Functions

	bool load(std::string path);
	void save(std::string path);
};

extern World & world;