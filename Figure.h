#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

enum Type { pawn = 0, bishop, rook, king, queen, knight };
enum Color { black, white };
using namespace std;

class Figure
{
private:
	// blacks are with Capital letters
	Type m_type;
	Color m_color;
	int m_X;
	int m_Y;
	char m_symbol;
protected:
	bool inBounds(const int& x, const int& y);
public:

	Figure(Type _type, Color _color, int _X, int _Y);
	//	virtual void changeType(const Type& _type) = 0;
		virtual bool validMove(int x, int y) = 0;
	//	virtual char printFigure() = 0;

	int getX()const;
	int getY()const;
	Color getColor()const;
	char getFigureSymbol()const;

	void setType(const Type& _type);
	void setPossition(int _X, int _Y);
	int getType();
};