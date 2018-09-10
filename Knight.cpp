#include "Knight.h"

Knight::Knight(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool Knight::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	if (abs(x - xS) == 1) return (abs(y - yS) == 2);
	else if (abs(y - yS) == 1) return (abs(x - xS) == 2);
	return false;
}
