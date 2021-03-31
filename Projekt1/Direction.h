#pragma once
#include "Tiles.h"
namespace Direction
{
	enum : uint16_t
	{
		UNKNOWN = 0x0000,
		TOP_LEFT = 0x0001,
		TOP = 0x0002,
		TOP_RIGHT = 0x0004,
		RIGHT = 0x0008,
		BOTTOM_RIGHT = 0x0010,
		BOTTOM = 0x0020,
		BOTTOM_LEFT = 0x0040,
		LEFT = 0x0080,
		CENTER = 0x0100
	};
	
	int Get(int from, int to);
	int reflect(int direct);
	

#define DIRECTION_TOP_ROW	(Direction::TOP_LEFT | Direction::TOP | Direction::TOP_RIGHT)
#define DIRECTION_BOTTOM_ROW	(Direction::BOTTOM_LEFT | Direction::BOTTOM | Direction::BOTTOM_RIGHT)
#define DIRECTION_CENTER_ROW	(Direction::LEFT | Direction::CENTER | Direction::RIGHT)
#define DIRECTION_LEFT_COL	(Direction::TOP_LEFT | Direction::LEFT | Direction::BOTTOM_LEFT)
#define DIRECTION_CENTER_COL	(Direction::TOP | Direction::CENTER | Direction::BOTTOM)
#define DIRECTION_RIGHT_COL	(Direction::TOP_RIGHT | Direction::RIGHT | Direction::BOTTOM_RIGHT)
#define DIRECTION_ALL		(DIRECTION_TOP_ROW | DIRECTION_BOTTOM_ROW | DIRECTION_CENTER_ROW)
#define DIRECTION_AROUND	(DIRECTION_TOP_ROW | DIRECTION_BOTTOM_ROW | Direction::LEFT | Direction::RIGHT)
}