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

void Configuration::unlockNextLevel(int level)
{
	if (level < 1 || level > 10)
		return;
	std::fstream file;
	file.open("config.txt");
	this->load(file, false);
	if(this->availableLevels < level)
		this->availableLevels = level;
	this->save(file);
	file.close();
}

bool Configuration::load(std::fstream& file, bool ignoreMapSize)
{
	if (!file.is_open())
		return false;
	
	if(file.fail() || file.bad())
		return false;

	if (ignoreMapSize)
	{
		int nothing;
		file >> nothing >> nothing;
		file >> nothing >> nothing;
		file >> nothing >> nothing;
		file >> nothing >> nothing;
	}
	else
	{
		file >> battlefiledTileWidth >> battlefiledTileHegiht;
		if (battlefiledTileHegiht < 5) battlefiledTileHegiht = 5;
		if (battlefiledTileHegiht > 40) battlefiledTileHegiht = 40;
		if (battlefiledTileWidth < 8) battlefiledTileWidth = 8;
		if (battlefiledTileWidth > 70) battlefiledTileWidth = 70;
		file >> battleTileOffset.x >> battleTileOffset.y;
		if (battleTileOffset.x < 0) battleTileOffset.x = 0;
		if (battleTileOffset.x > 10) battleTileOffset.x = 10;
		if (battleTileOffset.y > 10) battleTileOffset.y = 10;
		if (battleTileOffset.y < 0) battleTileOffset.y = 0;
		file >> battlefieldOffset.x >> battlefieldOffset.y;
		file >> PvP;
		file >> availableLevels;
	}
	tileWidth = ((float)windowSize.x - (battlefieldOffset.x + 20)) / (float)battlefiledTileWidth;
	tileHeight = ((float)windowSize.y - (battlefieldOffset.y + 170)) / (float)battlefiledTileHegiht;
	return true;
}

bool Configuration::load(std::string path)
{
	std::fstream file;
	file.open(path);
	return this->load(file, false);
}

bool Configuration::save(std::fstream& file)
{
	if (!file.is_open())
		return false;
	if (file.fail() || file.bad())
		return false;
	file.clear();
	file << battlefiledTileWidth << " " << battlefiledTileHegiht << std::endl;
	file << battleTileOffset.x << " " << battleTileOffset.y << std::endl;
	file << battlefieldOffset.x << " " << battlefieldOffset.y << std::endl;
	file << PvP << std::endl;
	file << availableLevels << std::endl;
	

	tileWidth = ((float)windowSize.x - (battlefieldOffset.x+20)) / (float)battlefiledTileWidth;
	tileHeight = ((float)windowSize.y - (battlefieldOffset.y+170)) / (float)battlefiledTileHegiht;

	return true;
}

bool Configuration::save(std::string path)
{
	std::fstream file;
	file.open(path);

	return save(file);
}
