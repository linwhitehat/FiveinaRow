#pragma once

#include<iostream>


#include "Array_data.h"

class Player
{
public:
	Player();
	~Player();

	int Mode_choose();//人人和人机模式的选择
	void People_vs_People(Array_data a);//人人模式
	void People_vs_Machine(Array_data a);//人机模式

	int player1_color = 0;//玩家执子颜色，0为黑，1为白
	int player2_color = 1;

	int result = 0;//
	int order = 1;//回合数
};

