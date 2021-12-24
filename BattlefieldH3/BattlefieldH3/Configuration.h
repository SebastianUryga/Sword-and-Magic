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
	sf::Vector2i battleTileOffset = { 1,6 };
	sf::Vector2f battlefieldOffset = { 20.f,250.f };
	sf::Vector2u windowSize;
	static Configuration& Get();

	bool load();
	bool save();
};

extern Configuration& Config;