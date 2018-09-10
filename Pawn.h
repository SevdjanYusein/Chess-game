#pragma once
#include "Figure.h"

class Pawn : public Figure
{
private:

public:
	Pawn(Type _type, Color _color, int _X, int _Y);
	//virtual void changeType(const Type& _type);
	virtual bool validMove(int x, int y);
	//virtual char printFigure();
};