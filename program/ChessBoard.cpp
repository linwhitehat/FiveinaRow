#include<iostream>
#include<string.h>
#include "ChessBoard.h"
using namespace std;


const char * ChessBoard::ChessStyle(int i, int j)
{
	if (i == 0 && j == 1)
		return "©³";
	else if (i == 0 && j == (COL -1))
		return "©·";
	else if (i == (ROW - 2) && j == 1)
		return "©»";
	else if (i == (ROW -2) && j == (COL - 1))
		return "©¿";
	else if (j == 1)
		return "©Ä";
	else if (j == (COL - 1))
		return "©Ì";
	else if (i == 0)
		return "©Ó";
	else if (i == (ROW - 2))
		return "©Û";
	return "©à";
}
