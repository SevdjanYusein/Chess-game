#pragma once
#include "Figure.h"

class Knight : public Figure
{
private:

public:
	Knight(Type _type, Color _color, int _X, int _Y);
	//virtual void changeType(const Type& _type);
	virtual bool validMove(int x, int y);
	//virtual char printFigure();
};