#include "Rook.h"

Rook::Rook(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool Rook::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	return (((x == xS) && (y != yS)) || ((x != xS) && (y == yS)));
}

