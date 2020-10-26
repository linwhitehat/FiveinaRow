#include "Show.h"


Show::Show()
{
}

Show::~Show()
{
}

void Show::ChessShow(int i, int j)
{
	
}

void Show::ChessBoardShow(Array_data a)
{
	a.Show_data();
}

void Show::gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}