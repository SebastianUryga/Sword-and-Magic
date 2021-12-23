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
	std::string path = "config.txt";
	std::fstream file;
	file.open(path);
	if(file.fail() || file.bad())
		return false;
	file >> tileWidth >> tileHeight >> battlefiledTileWidth >> battlefiledTileHegiht;
	if (tileWidth < 30.f) tileWidth = 30.f;
	if (tileWidth > 100.f) tileWidth = 100.f;
	if (tileHeight < 30.f) tileHeight = 30.f;
	if (tileHeight > 100.f) tileHeight = 100.f;
	if (battlefiledTileHegiht < 5) battlefiledTileHegiht = 5;
	if (battlefiledTileHegiht > 20) battlefiledTileHegiht = 20;
	if (battlefiledTileWidth < 8) battlefiledTileWidth = 8;
	if (battlefiledTileWidth > 35) battlefiledTileWidth = 35;
	file >> battleTileOffset.x >> battleTileOffset.y;
	if (battleTileOffset.x < 0) battleTileOffset.x = 0;
	if (battleTileOffset.x > 10) battleTileOffset.x = 10;
	if (battleTileOffset.y > 10) battleTileOffset.y = 10;
	if (battleTileOffset.y < 0) battleTileOffset.y = 0;
	file.close();
}

bool Configuration::save()
{
	std::string path = "config.txt";
	std::fstream file;
	file.open(path);
	if (file.fail() || file.bad())
		return false;
	file.clear();
	file << tileWidth << " " << tileHeight << std::endl;
	file << battlefiledTileWidth << " " << battlefiledTileHegiht << std::endl;
	file << battleTileOffset.x << " " << battleTileOffset.y << std::endl;
	file.close();

}
