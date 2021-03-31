#include "pch.h"
#include "color.h"

int Color::getNextColor(int color)
{
	return color << 1;
}
