#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Figure.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"

using namespace std;

const int boardSize = 9;

class Board
{
private:
	wstring board[boardSize][boardSize];
	vector<Figure*> blackFigures;
	vector<Figure*> whiteFigures;
	bool whitesTurn;

	void addFigure(const Type& _type, const Color& _color, const int& _X, const int& _Y);
	
	void chooseFigure(char start_end[6], int& _xS, int& _yS, int& _xE, int& _yE);
	bool isLegit(int x, int y);		//->funkciq
	Figure* findFigure(const int& x, const int& y);
	bool removeEnemyFigure(int x, int y);
	bool isKing(const int& endX, const int& endY);
	void moveFigure(Figure * fig, int x, int y);
	void resetTable();

	bool validMoveRook(Figure * fig, int x, int y);
	bool validMoveBishop(Figure * fig, int x, int y);
	
	bool validMove(Figure* fig, int x, int y);
	void updateBoard();
	void visualizeBoard();

	void newGame();
	void playGame();
	void restoreGame();
	void saveCurrentState();
	void readLog();
public:
	Board();	
	void showMenu();
};