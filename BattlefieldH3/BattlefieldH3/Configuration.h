#pragma once
#include "PCH.hpp"

class Configuration
{
public:
	Configuration() {}
	virtual ~Configuration();
	float tileWidth = 50.f;
	float tileHeight = 50.f;
	int battlefiledTileWidth = 24;
	int battlefiledTileHegiht = 12;
	sf::Vector2i battleTileOffset = { 1,3 };
	sf::Vector2u windowSize;
	static Configuration& Get();

	bool load();
	bool save();
};

extern Configuration& Config;