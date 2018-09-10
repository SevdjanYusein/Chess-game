#pragma once
#include "Figure.h"
#include <cmath>

class Bishop : public Figure
{
private:

public:
	Bishop(Type _type, Color _color, int _X, int _Y);
	//virtual void changeType(const Type& _type);
	virtual bool validMove(int x, int y);
	//virtual char printFigure();
};