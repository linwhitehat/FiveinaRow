#pragma once

#include "ChessBoard.h"
#include "Chessman.h"
#include "Show.h"
#include "Player.h"
#include "Array_data.h"
class Game
{
public:
	Game();
	~Game();
	Array_data Chess_data;//棋局数据对象
	ChessBoard Board;//棋盘对象
	Show display;
	Player player;//玩家对象

	void Load_Game();//初始化棋局游戏
	void show(Array_data a);
	void Play_1(Array_data a);//人人模式
	void Play_2(Array_data a);//人机模式
	void Run_Game(Game g);//开始玩游戏
};

