#include "Figure.h"

// blacks are with Capital letters
// first figures must be for black side
char figureSymbols[] = { 'P','B','R','K','Q','N', 
						'p','b','r','k','q','n' };
//wchar_t figureSymbols[] = { L'\u265F',L'\u265D',L'\u265C',L'\u265A',L'\u265B',L'\u265E',
//							L'\u2659',L'\u2657',L'\u2656',L'\u2654',L'\u2655',L'\u2658' };



bool Figure::inBounds(const int & x, const int & y)
{
	if ((x <= 7 && x >= 0) && (y <= 7 && y >= 0)) return true;
	return false;
}

Figure::Figure(Type _type, Color _color, int _X, int _Y)
{
	m_type = _type;
	m_color = _color;
	m_X = _X;
	m_Y = _Y;
	if (m_color == white) m_symbol = figureSymbols[m_type + 6];
	else m_symbol = figureSymbols[m_type];
}

void Figure::setType(const Type& _type)
{
	m_type = _type;
}

void Figure::setPossition(int _X, int _Y)
{
	m_X = _X;
	m_Y = _Y;
}

int Figure::getType()
{
	return static_cast<int>(m_type);
}

int Figure::getX() const
{
	return m_X;
}

int Figure::getY() const
{
	return m_Y;
}

Color Figure::getColor()const
{
	return m_color;
}

char Figure::getFigureSymbol()const
{
	return m_symbol;
}
