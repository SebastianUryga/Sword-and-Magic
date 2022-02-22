#pragma once
#include "PCH.hpp"

class Configuration
{
public:
	Configuration() {}
	virtual ~Configuration();
	float tileWidth = 70.f;
	float tileHeight = 40.f;
	int battlefiledTileWidth = 24;
	int battlefiledTileHegiht = 12;
	sf::Vector2i battleTileOffset = { 1,7 };
	sf::Vector2f battlefieldOffset = { 20.f,250.f };
	sf::Vector2u windowSize;

	bool PvP = true;
	int availableLevels = 1;

	static Configuration& Get();
	void unlockNextLevel(int level);
	bool load(std::fstream& file, bool ignoreMapSize);
	bool load(std::string path);
	bool save(std::fstream& file);
	bool save(std::string path);
};

extern Configuration& Config;