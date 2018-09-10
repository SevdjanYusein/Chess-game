#include "Queen.h"

Queen::Queen(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool Queen::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	return (x == xS || y == yS || (abs(x - xS) == abs(y - yS)));
}

