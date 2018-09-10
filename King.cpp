#include "King.h"

King::King(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool King::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	if (x == xS || y == yS)
	{
		return (abs(x - xS) == 1 || abs(y - yS) == 1);
	}
	else if (abs(x - xS) == abs(y - yS))
	{
		return (abs(x - xS) == 1 && abs(y - yS) == 1);
	}
	return false;
}
