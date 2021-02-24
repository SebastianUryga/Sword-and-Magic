#include "pch.h"
#include "Direction.h"
#include "Tiles.h"

int Direction::Get(int from, int to)
{
	for (int direction = 0x0001; 0x0100 > direction; direction = direction << 1)
		if (to == Maps::GetDirectionIndex(from, direction))
			return direction;

	return to == from ? CENTER : UNKNOWN;
}

int Direction::reflect(int direct)
{
	{
		switch (direct)
		{
		case TOP_LEFT:		return BOTTOM_RIGHT;
		case TOP:		return BOTTOM;
		case TOP_RIGHT:		return BOTTOM_LEFT;
		case RIGHT:		return LEFT;
		case BOTTOM_RIGHT:	return TOP_LEFT;
		case BOTTOM:		return TOP;
		case BOTTOM_LEFT:	return TOP_RIGHT;
		case LEFT:		return RIGHT;
		case CENTER:		return CENTER;
		default: break;
		}

		return UNKNOWN;
	}
}
