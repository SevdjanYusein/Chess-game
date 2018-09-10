#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Board.h"


const wstring abc[9] = { L"\u0020",L"\u0041",L"\u0042",L"\u0043",L"\u0044",
						L"\u0045",L"\u0046",L"\u0047",L"\u0048" };	//' ', A, B, C, D, E, F, G, H
const wstring num[9] = { L"\u0020",L"\u0031",L"\u0032",L"\u0033",L"\u0034",
						L"\u0035",L"\u0036",L"\u0037",L"\u0038" };	//1, 2, 3, 4, 5, 6, 7, 8

static string previousGame = "previousGame.txt";
static char figureSymbolsForFileOutput[] = { 'P','B','R','K','Q','N', 'p','b','r','k','q','n' };


int determineFigureType(const char& symbol)
{
	switch (symbol)
	{
	case 'P': case 'p':
	{
		return 0;
		break;
	}
	case 'B': case 'b':
	{
		return 1;
		break;
	}
	case 'R': case 'r':
	{
		return 2;
		break;
	}
	case 'K': case 'k':
	{
		return 3;
		break;
	}
	case 'Q': case 'q':
	{
		return 4;
		break;
	}
	case 'N': case 'n':
	{
		return 5;
		break;
	}
	}
	return -1;
}

char determineFigureSymbol(int _type, int _color)
{
	Type type = static_cast<Type>(_type);
	Color color = static_cast<Color>(_color);
	if (color == white) return figureSymbolsForFileOutput[type + 6];
	return  figureSymbolsForFileOutput[type];
}


bool isFromAtoH(const char& c)
{
	if ((c >= 'A' && c <= 'H') || (c >= 'a' && c <= 'h')) return true;
	return false;
}

bool isFrom1to8(const char& c)
{
	if (c >= '1' && c <= '8') return true;
	return false;
}

bool validInput(const char* input)
{
	if (isFromAtoH(input[0]) && isFromAtoH(input[3]))
	{
		if (isFrom1to8(input[1]) && isFrom1to8(input[4])) return true;
	}
	return false;
}

// creates a figure and adds it to correct vector
void Board::addFigure(const Type& _type, const Color& _color, const int& _X, const int& _Y)
{
	Figure* newFigure = nullptr;
	switch (_type)
	{
	case pawn:
	{
		newFigure = new Pawn(_type, _color, _X, _Y);
		break;
	}
	case bishop:
	{
		newFigure = new Bishop(_type, _color, _X, _Y);
		break;
	}
	case rook:
	{
		newFigure = new Rook(_type, _color, _X, _Y);
		break;
	}
	case king:
	{
		newFigure = new King(_type, _color, _X, _Y);
		break;
	}
	case queen:
	{
		newFigure = new Queen(_type, _color, _X, _Y);
		break;
	}
	case knight:
	{
		newFigure = new Knight(_type, _color, _X, _Y);
		break;
	}
	}
	if (newFigure->getColor() == black)
	{
		blackFigures.push_back(newFigure);
	}
	else whiteFigures.push_back(newFigure);
}

void Board::updateBoard()
{
	for (int i = 0; i < 9; ++i)
	{
		board[8 - i][0] = num[i];			// first column
		board[8][i] = abc[i];				// last row
	}
	for (int i = 0; i < boardSize - 1; i++)
	{
		for (int j = 1; j < boardSize; j++)
		{
			board[i][j] = L"\u002d";		// '-'
		}
	}
	for (unsigned int i = 0; i < blackFigures.size(); i++)
	{
		const int xB = blackFigures[i]->getX();
		const int yB = blackFigures[i]->getY();
		board[yB][xB + 1] = blackFigures[i]->getFigureSymbol();
	}
	for (unsigned int j = 0; j < whiteFigures.size(); j++)
	{
		const int xW = whiteFigures[j]->getX();
		const int yW = whiteFigures[j]->getY();
		board[yW][xW + 1] = whiteFigures[j]->getFigureSymbol();
	}
}

Board::Board()
{
	updateBoard();
	whitesTurn = true;
}

void Board::chooseFigure(char start_end[6], int& _xS, int& _yS, int& _xE, int& _yE)
{
	//ako ne raboti -> promeni tipa na char
	char start[] = { start_end[0],start_end[1],'\0' };
	char end[] = { start_end[3],start_end[4],'\0' };

	if (start[0] >= 'A' && start[0] <= 'H')	_xS = start[0] - 'A';
	else if (start[0] >= 'a' && start[0] <= 'h')	_xS = start[0] - 'a';
	_yS = 8 - (start[1] - '0');

	if (end[0] >= 'A' && end[0] <= 'H')	_xE = end[0] - 'A';
	else if (end[0] >= 'a' && end[0] <= 'h')	_xE = end[0] - 'a';
	_yE = 8 - (end[1] - '0');
}

bool Board::isLegit(int x, int y)
{
	return (y < 8 && y >= 0 && x>0 && x < 9);
}

Figure * Board::findFigure(const int& x, const int& y)
{
	for (int i = 0; i < whiteFigures.size(); i++)
	{
		if (x == whiteFigures[i]->getX() && y == whiteFigures[i]->getY())
			return whiteFigures[i];
	}
	for (int i = 0; i < blackFigures.size(); i++)
	{
		if (x == blackFigures[i]->getX() && y == blackFigures[i]->getY())
			return blackFigures[i];
	}
	return nullptr;
}

bool Board::removeEnemyFigure(int x, int y)
{
	if (board[y][x + 1] != L"\u002d")
	{
		Figure* f = findFigure(x, y);
		if (f != nullptr)
		{
			if (f->getColor() == white && whitesTurn == false)
			{
				int poss;
				for (poss = 1; poss < whiteFigures.size(); poss++)
				{
					if (whiteFigures[poss] == f)
					{
						whiteFigures.erase(whiteFigures.begin() + poss);
						return true;
					}
				}
			}
			else if (f->getColor() == black && whitesTurn == true)
			{
				int poss;
				for (poss = 1; poss < blackFigures.size(); poss++)
				{
					if (blackFigures[poss] == f)
					{
						blackFigures.erase(blackFigures.begin() + poss);
						return true;
					}
				}
			}
		}
		return false;
	}
	return true;
}

bool Board::isKing(const int & endX, const int & endY)
{
	Figure* piece = whiteFigures[0];
	if ((piece->getX() == endX) && (piece->getY() == endY)) return true;
	piece = blackFigures[0];
	if ((piece->getX() == endX) && (piece->getY() == endY))	return true;
	return false;
}

void Board::moveFigure(Figure * fig, int x, int y)
{
	board[fig->getY()][fig->getX() + 1] = L"\u002d";
	board[y][x + 1] = fig->getFigureSymbol();
	fig->setPossition(x, y);
}

void Board::resetTable()
{
	for (int i = 0; i < boardSize - 1; i++)
	{
		for (int j = 1; j < boardSize; j++)
		{
			board[i][j] = L"\u002d";		// '-'
		}
	}
}

bool Board::validMoveRook(Figure * fig, int x, int y)
{

	int sX, sY;
	sX = fig->getX();
	sY = fig->getY();
	Rook fig1(rook, white, sX, sY);
	if (!fig1.validMove(x, y))
	{
		return false;
	}
	Figure* temp = nullptr;
	bool flag = true;
	if (sX == x)
	{
		if (sY > y)
		{
			for (int i = sY - 1; i > y; i--)
			{
				temp = findFigure(x, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
		else
		{
			for (int i = sY + 1; i < y; i++)
			{
				temp = findFigure(x, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
	}
	else if (sY == y)
	{
		if (sX > x)
		{
			for (int i = sX - 1; i > x; i--)
			{
				temp = findFigure(i, y);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
		else
		{
			for (int i = sX + 1; i < x; i++)
			{
				temp = findFigure(i, y);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
	}
	return flag;
}

bool Board::validMoveBishop(Figure * fig, int x, int y)
{

	int sX, sY;
	sX = fig->getX();
	sY = fig->getY();
	Bishop fig1(bishop, white, sX, sY);
	if (!fig1.validMove(x, y))
	{
		return false;
	}
	Figure* temp = nullptr;
	bool flag = true;
	if (sX < x)
	{
		if (sY < y)
		{
			for (int i = sY + 1, j = sX + 1; i > y - 1, j > x - 1; i++, j++)
			{
				temp = findFigure(j, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
		else
		{
			for (int i = sY - 1, j = sX + 1; i > y + 1, j > x - 1; i--, j++)
			{
				temp = findFigure(j, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
	}
	else
	{
		if (sY < y)
		{
			for (int i = sY + 1, j = sX - 1; i > y - 1, j > x + 1; i++, j--)
			{
				temp = findFigure(j, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
		else
		{
			for (int i = sY - 1, j = sX - 1; i > y + 1, j > x + 1; i--, j--)
			{
				temp = findFigure(j, i);
				if (temp != nullptr)
				{
					flag = false;
					break;
				}
			}
		}
	}
	return flag;
}

bool Board::validMove(Figure* fig, int x, int y)
{
	// check for path
	Figure* figureAtEnd = findFigure(x, y);
	if (isKing(x, y) == true)
	{
		return false;
	}
	if (!fig->getColor() == whitesTurn)
	{
		return false;
	}
	int sX, sY;
	sX = fig->getX();
	sY = fig->getY();
	Figure* temp = nullptr;
	switch (fig->getType())
	{
	case pawn:
	{
		if (!fig->validMove(x, y))
		{
			return false;
		}
		if ((sX == x) && (figureAtEnd == nullptr))
		{
			moveFigure(fig, x, y);
		}
		else if (sX != x && figureAtEnd != nullptr)
		{
			if (removeEnemyFigure(x, y)) moveFigure(fig, x, y);
			else return false;
		}
		else if ((sX == x) && (figureAtEnd != nullptr))
		{
			return false;
		}
		break;
	}
	case rook:
	{
		if (validMoveRook(fig, x, y))
		{
			// if figure at end is friend figure we cant remove it
			if (figureAtEnd != nullptr && removeEnemyFigure(x, y))moveFigure(fig, x, y);
			else if (figureAtEnd == nullptr) moveFigure(fig, x, y);
			else return false;
		}
		else return false;
		break;
	}
	case bishop:
	{
		if (validMoveBishop(fig, x, y))
		{
			// if figure at end is friend figure we cant remove it
			if (figureAtEnd != nullptr && removeEnemyFigure(x, y))moveFigure(fig, x, y);
			else if (figureAtEnd == nullptr) moveFigure(fig, x, y);
			else return false;
		}
		else return false;
		break;
	}
	case knight: case king:
	{
		if (!fig->validMove(x, y))
		{
			return false;
		}
		// if figure at end is friend figure we cant remove it
		// if figure at end is friend figure we cant remove it
		if (figureAtEnd != nullptr && removeEnemyFigure(x, y))moveFigure(fig, x, y);
		else if (figureAtEnd == nullptr) moveFigure(fig, x, y);
		else return false;
		break;
	}
	case queen:
	{
		if (validMoveRook(fig, x, y) || validMoveBishop(fig, x, y))
		{
			// if figure at end is friend figure we cant remove it
			if (figureAtEnd != nullptr && removeEnemyFigure(x, y))moveFigure(fig, x, y);
			else if (figureAtEnd == nullptr) moveFigure(fig, x, y);
			else return false;
		}
		else return false;
		break;
	}
	}
	return true;
}
void Board::visualizeBoard()
{
	updateBoard();
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			wcout << board[i][j] << " ";
		}
		cout << endl;
	}
}


void Board::newGame()
{
	whiteFigures.clear();
	blackFigures.clear();

	addFigure(king, black, 4, 0);
	addFigure(queen, black, 3, 0);
	addFigure(bishop, black, 2, 0);
	addFigure(bishop, black, 5, 0);
	addFigure(rook, black, 0, 0);
	addFigure(rook, black, 7, 0);
	addFigure(knight, black, 1, 0);
	addFigure(knight, black, 6, 0);

	addFigure(pawn, black, 0, 1);
	addFigure(pawn, black, 1, 1);
	addFigure(pawn, black, 2, 1);
	addFigure(pawn, black, 3, 1);
	addFigure(pawn, black, 4, 1);
	addFigure(pawn, black, 5, 1);
	addFigure(pawn, black, 6, 1);
	addFigure(pawn, black, 7, 1);


	addFigure(king, white, 4, 7);
	addFigure(queen, white, 3, 7);
	addFigure(bishop, white, 2, 7);
	addFigure(bishop, white, 5, 7);
	addFigure(rook, white, 0, 7);
	addFigure(rook, white, 7, 7);
	addFigure(knight, white, 1, 7);
	addFigure(knight, white, 6, 7);

	addFigure(pawn, white, 0, 6);
	addFigure(pawn, white, 1, 6);
	addFigure(pawn, white, 2, 6);
	addFigure(pawn, white, 3, 6);
	addFigure(pawn, white, 4, 6);
	addFigure(pawn, white, 5, 6);
	addFigure(pawn, white, 6, 6);
	addFigure(pawn, white, 7, 6);
}

void Board::restoreGame()
{
	fstream file;
	file.open("previousGame.txt", ios::in);
	if (!file.good())
	{
		cout << "No old game found, or file corrupt \n";
		return;
	}
	string line = "";
	getline(file, line);
	size_t sizeOfLine = line.length();
	for (int i = 0; i < sizeOfLine; i += 3)
	{
		addFigure((Type)determineFigureType(line[i]), black, (int)(line[i + 1] - '0'), (int)(line[i + 2] - '0'));
	}
	getline(file, line);
	sizeOfLine = line.length();
	for (int i = 0; i < sizeOfLine; i += 3)
	{
		addFigure((Type)determineFigureType(line[i]), white, (int)(line[i + 1] - '0'), (int)(line[i + 2] - '0'));
	}
	file.close();
}

void Board::saveCurrentState()
{
	fstream file;
	file.open("previousGame.txt", ios::out);
	size_t vectorSize = blackFigures.size();
	for (int i = 0; i < vectorSize; i++)
	{
		file << determineFigureSymbol(blackFigures[i]->getType(), black)
			<< blackFigures[i]->getX()
			<< blackFigures[i]->getY();
	}
	file << "\n";
	vectorSize = whiteFigures.size();
	for (int i = 0; i < vectorSize; i++)
	{
		file << determineFigureSymbol(whiteFigures[i]->getType(), white)
			<< whiteFigures[i]->getX()
			<< whiteFigures[i]->getY();
	}
	file.close();
}

void Board::readLog()
{
	fstream log;
	log.open("gameLog.txt", ios::in);
	string line = "";
	while (log.good())
	{
		getline(log, line);
		cout << line;
	}
	log.close();
}

void Board::playGame()
{
	char userInput[20];
	system("cls");
	visualizeBoard();
	bool wrongInput = false;
	fstream log;
	log.open("gameLog.txt", ios::out);
	while (true)
	{
		wrongInput = false;
		std::cout << "What is your next move: ";
		std::cin.getline(userInput, 20);
		if (!strcmp(userInput, "QUIT"))
		{
			saveCurrentState();
			break;
		}
		else if (!strcmp(userInput, "RESET"))
		{
			resetTable();
			newGame();
			updateBoard();
			break;
		}
		else if (!strcmp(userInput, "DRAW"))
		{
			std::cout << "Does the other player agree with the draw? (y/n): ";
			char c;
			std::cin >> c;
			if (c == 'y')
			{
				std::cout << "It's a draw!!!\n";
				break;
			}
			else
			{
				std::cout << "Continue playing!\n";
			}
		}
		else
		{

			if (strlen(userInput) == 5)
			{
				int startX, startY, endX, endY;
				chooseFigure(userInput, startX, startY, endX, endY);
				Figure* piece = findFigure(startX, startY);
				if (piece != nullptr)
				{
					if (validMove(piece, endX, endY) == true)
					{
						//write in log file
						if (whitesTurn) log << " whites: " << userInput << endl;
						else			log << " blacks: " << userInput << endl;
						whitesTurn = !whitesTurn;
					}
					else
					{
						wrongInput = true;
					}
				}
				else wrongInput = true;
			}
			else wrongInput = true;
			if (wrongInput == true)
			{
				std::cout << "Wrong input!\n";
			}
			else
			{
				system("cls");
				visualizeBoard();
			}
		}
	}
	log.close();
}

void Board::showMenu()
{
	int userChoice;
	while (true)
	{
		system("cls");
		cout << "\t\t\t\tMain Menu\n\n";
		cout << "1. Start new game.\n";
		cout << "2. Continue previous game.\n";
		cout << "3. Show log of previous game.\n";
		cout << "0. To exit.\n\n";
		cout << "Input choice: ";
		cin >> userChoice;
		switch (userChoice)
		{
		case 0:
		{
			exit(EXIT_SUCCESS);
			break;
		}
		case 1:
		{
			system("cls");
			newGame();
			playGame();
			break;
		}
		case 2:
		{
			system("cls");
			restoreGame();
			playGame();
			break;
		}
		case 3:
		{
			system("cls");
			readLog();
			cin.get();
			break;
		}
		default:
		{
			cout << "Invalid input! Try again!!\n";
			cin.get();
			break;
		}
		}
	}
}
