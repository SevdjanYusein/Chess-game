#include "Bishop.h"

Bishop::Bishop(Type _type, Color _color, int _X, int _Y) :
	Figure(_type, _color, _X, _Y) {}

bool Bishop::validMove(int x, int y)
{
	int xS = getX();
	int yS = getY();
	return  (abs(x - xS) == abs(y - yS));
}
