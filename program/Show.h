#pragma once
#include "Array_data.h"
#include "ChessBoard.h"
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include<windows.h>
class Show
{
public:
	Show();
	~Show();
	void ChessShow(int i, int j);//输出棋子
	void ChessBoardShow(Array_data a);//输出棋局
	void gotoxy(int x, int y);
};
