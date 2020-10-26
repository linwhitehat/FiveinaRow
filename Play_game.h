#pragma once

#include "Array_data.h"
#include "Judge.h"
#include "Show.h"
#include "Player.h"
#include "Game.h"

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define random(x)(rand()%2)//产生0或1的随机数

class Play_game
{
public:
	Play_game();
	~Play_game();

	void Play_1(Array_data a,int color,const char *player_role,int order,int state);//人人对战博弈,color是执黑判断,role是玩家角色,order是回合数,state是当前状态,x和y是上一步棋子的位置
	void Play_2(Array_data a,int color,const char *player_role,int order,int state);//人机对战博弈

	int*  score_account(Array_data a,Judge judge,int color);//机器计分处理,color用于判断机器所执子颜色

	void Play_again(Game g);//出现胜负是否重新开始一局游戏
};

