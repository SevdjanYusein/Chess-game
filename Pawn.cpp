#include "Pawn.h"

Pawn::Pawn(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool Pawn::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	if (inBounds(x, y) == false)
	{
		return false;
	}
	else {
		if ((abs(xS - x) == 1) || (xS == x))
		{
			if ((yS - y) >= -1 && (yS - y) <= 1) 
			{
				return true;
			}
		}
	}
	return false;
}

