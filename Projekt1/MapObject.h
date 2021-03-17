#pragma once
#include"InfoWindows.h"
#include"Pathfinder.h"
#include"AnimotionComponent.h"

class AnimotionComponent;
class Graphics;
class HeroInstance;
namespace MP2
{
	class ObjectInstance
	{
	public:
		enum BlockMapBits
		{
			VISIBLE = 1,
			VISITABLE = 2,
			BLOCKED = 4
		};
		bool toDelete;
		/// directions from which object can be entered, format same as for moveDir in HeroInstance(but 0 - 7)
		uint16_t visitDir;
		/// Position of bottom-right corner of object on map
		sf::Vector2i pos;
		/// Type of object, e.g. town, hero, creature.
		Obj type;
		/// Subtype of object, depends on type
		int subType;
		/// Index of object in map's list of objects
		int id;
		/// Current owner of an object
		int ownerColor;
		/// If true hero can visit this object only from neighbouring tiles and can't stand on this object
		bool blockVisit;
		/// tiles that are covered by this object, uses BlockMapBits enum as flags
		std::vector<std::vector<int8_t>> usedTiles;
		int priority;
		AnimotionComponent* animationComponent;
		sf::Sprite sprite;

		std::string instanceName;
		std::string typeName;
		std::string subTypeName;

		ObjectInstance();
		~ObjectInstance();

		int getWidth() const; //returns width of object graphic in tiles
		int getHeight() const; //returns height of object graphic in tiles
		bool visitableAt(int x, int y) const; //returns true if object is visitable at location (x, y)
		bool blockingAt(int x, int y) const; //returns true if object is blocking location (x, y)
		int getOwner() const;
		virtual sf::Vector2i getSightCenter() const;
		virtual int getSightRadius() const;
		virtual void setOwner(int ow);

		virtual void setTexture(sf::Texture& sheetTexture);
		virtual void initObjAnimaiton();
		virtual void initObj();
		virtual void setType(int32_t type);
		// Returns generic name of object
		virtual std::string getObjectName() const;
		// Returns hover name, including visited/not visited info
		virtual std::string getHoverText(const HeroInstance * hero) const;

		void setSize(unsigned width,unsigned height);
		virtual void setTilePos(const sf::Vector2i& pos);

		bool isVisitable() const; //returns true if object is visitable
		bool isVisitableFrom(int dir) const;
		sf::Vector2i getVisitablePos() const;
		

		virtual void onHeroVisit(const HeroInstance * h) const;

		virtual void afterAddToMap();

		virtual void load(std::fstream& file);
		virtual void save(std::fstream& file);


		virtual void animationUpdate(const float& dt);
		virtual void update(const float& dt);
		virtual void render(sf::RenderTarget* target);

	private:
		int numberOfFrameAnimation;
	};

	enum
	{
		OBJ_ZERO,
		OBJ_TREES,
		OBJ_MOUNTS1,
		OBJ_MOUNTS2,
		OBJ_CRATER,
		OBJ_WATERLAKE,
		OBJ_STUMP,
		OBJ_ARENA,
		OBJ_STABLE,
		OBJ_MONSTER,
		OBJ_CASTLE,
		OBJ_HEROES,
		OBJ_RESOURCE
	};
	bool isActionObject(int obj);
	bool isCaptureObject(int obj);
	bool isPickupObject(int obj);

}

