#pragma once
#include"PCH.hpp"

class GameConstants
{
};



struct BattleObstacle
{
    enum class Type : int
    {
        ROCK1 = 0 , ROCK2 = 1, ROCK3 = 2 , ROCK4 = 3, MUSHROOM, SCIELETON1
    };
    Type type;
    sf::Sprite sprite;
    sf::Vector2i pos;
    std::vector<std::vector<bool>> usedTiles;
};

struct BattleObstacleParametrs
{
	std::vector<std::vector<bool>> usedTiles;
};

extern std::map<BattleObstacle::Type, BattleObstacleParametrs> battleObstacleParametrs;
