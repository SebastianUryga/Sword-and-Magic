#pragma once
#include "Kingdom.h"
#include "GameConstants.h"
#include "PlayerInterface.h"
#define TILEWIDTH 32.f

namespace MP2
{
	class ObjectInstance;
}

namespace Maps
{
	int GetDirectionIndex(int from, int dir);

	namespace Ground
	{
		enum
		{
			UNKNOWN = 0x0000,
			DESERT = 0x0001,
			SNOW = 0x0002,
			SWAMP = 0x0004,
			WASTELAND = 0x0008,
			BEACH = 0x0010,
			LAVA = 0x0020,
			DIRT = 0x0040,
			GRASS = 0x0080,
			WATER = 0x0100,
			ALL = DESERT | SNOW | SWAMP | WASTELAND | BEACH | LAVA | DIRT | GRASS
		};

		std::string	String(int ground);
	
		int GetPenalty(int index, int direction, int pathfinding);
	}
	enum RoadType
	{
		NO_ROAD, DIRT_ROAD, GRAVEL_ROAD, COBBLESTONE_ROAD
	};
	class Tile : public IntObject
	{
	private:
		int ground;
		Obj objectType;
		int maps_index;
		int fog_colors;
		int roadType;
		
		sf::IntRect groundRect;
		sf::Sprite groundSprite;
		sf::IntRect fogRect;
		sf::Sprite fogSprite;
		sf::IntRect roadRect;
		sf::Sprite roadSprite;

	public:

		/// Map objects that belong to this tile
		std::vector<MP2::ObjectInstance*> objects;

		bool visitable;
		bool blocked;

		void Init(int index);

		Tile();
		virtual ~Tile();

		// Acesors
		MP2::ObjectInstance* GetObjectPtr() const;
		int GetIndex() const;
		int GetGround() const;
		int GetRoad() const;
		bool isBlocked() const;
		bool isVisitable() const;
		//Modifires
		void SetIndex(int index);
		void SetObjectType(int object);
		void SetObject(MP2::ObjectInstance* object);
		void addMapObject(MP2::ObjectInstance* object);
		void removeMapObject(MP2::ObjectInstance* object);
		/// Also set siutable texture
		void SetRoad(int road);
		void SetGround(int ground);
		void setGroundTexture(sf::Texture& texture);
		void setRoadTexture(sf::Texture& texture);
		void setFogTexture(sf::Texture& texture, int color);

		bool isWater() const;
		bool isFog(int color) const;
		void ClearFog(int color);

		void clickLeft(bool down, bool previousState) override;
		void clickRight(bool down, bool previousState) override;
		bool contains(sf::Vector2f pos) override;

		void updatePassable();
		void update();
		void renderGround(sf::RenderTarget* target = nullptr);
		void renderRoad(sf::RenderTarget* target = nullptr);
		void renderFog(sf::RenderTarget* target = nullptr);

		void load(std::fstream& file);
		void save(std::fstream& file);
	};

}