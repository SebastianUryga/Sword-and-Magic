#include "Configuration.h"

Configuration& Config = Configuration::Get();

Configuration::~Configuration()
{
}

Configuration& Configuration::Get()
{
	static Configuration config;
	return config;
}

bool Configuration::load()
{
	std::string path = "res/config.txt";
	std::fstream file;
	file.open(path);
	if(file.fail() || file.bad())
		return false;
	file >> battlefiledTileWidth >> battlefiledTileHegiht;
	if (battlefiledTileHegiht < 5) battlefiledTileHegiht = 5;
	if (battlefiledTileHegiht > 20) battlefiledTileHegiht = 20;
	if (battlefiledTileWidth < 8) battlefiledTileWidth = 8;
	if (battlefiledTileWidth > 35) battlefiledTileWidth = 35;
	file >> battleTileOffset.x >> battleTileOffset.y;
	if (battleTileOffset.x < 0) battleTileOffset.x = 0;
	if (battleTileOffset.x > 10) battleTileOffset.x = 10;
	if (battleTileOffset.y > 10) battleTileOffset.y = 10;
	if (battleTileOffset.y < 0) battleTileOffset.y = 0;
	file >> battlefieldOffset.x >> battlefieldOffset.y;
	file.close();
	
	tileWidth = ((float)windowSize.x - (battlefieldOffset.x + 20)) / (float)battlefiledTileWidth;
	tileHeight = ((float)windowSize.y - (battlefieldOffset.y + 170)) / (float)battlefiledTileHegiht;
	return true;
}

bool Configuration::save()
{
	std::string path = "res/config.txt";
	std::fstream file;
	file.open(path);
	if (file.fail() || file.bad())
		return false;
	file.clear();
	file << battlefiledTileWidth << " " << battlefiledTileHegiht << std::endl;
	file << battleTileOffset.x << " " << battleTileOffset.y << std::endl;
	file << battlefieldOffset.x << " " << battlefieldOffset.y << std::endl;
	file.close();

	tileWidth = ((float)windowSize.x - (battlefieldOffset.x+20)) / (float)battlefiledTileWidth;
	tileHeight = ((float)windowSize.y - (battlefieldOffset.y+170)) / (float)battlefiledTileHegiht;

	return true;
}
