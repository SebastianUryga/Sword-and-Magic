#pragma once

namespace Color
{
	enum
	{
		NONE = 0x00,
		RED = 0x01,
		BLUE = 0x02,
		GREEN = 0x04,
		YELLOW = 0x08,
		ORANGE = 0x10,
		PURPLE = 0x20,
		UNUSED = 0x80,
		ALL = BLUE | GREEN | RED | YELLOW | ORANGE | PURPLE
	};
	int getNextColor(int color);
}
