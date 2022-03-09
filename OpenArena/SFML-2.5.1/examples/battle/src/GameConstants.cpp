#include "GuiHandler.h"


std::map<BattleObstacle::Type, BattleObstacleParametrs> battleObstacleParametrs
{
	{BattleObstacle::Type::ROCK1, {{{1,1},{0,0}}}},
	{BattleObstacle::Type::ROCK2, {{{1,1},{0,0}}}},
	{BattleObstacle::Type::ROCK3, {{{1,1}}} },
	{ BattleObstacle::Type::ROCK4, {{{1,1},{0,0}} }},
	{BattleObstacle::Type::SCIELETON1, {{{1,1,1},{1,0,0}}} }
};