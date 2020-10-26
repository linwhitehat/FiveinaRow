#pragma once

#include<iostream>

#include "Array_data.h"

class Judge
{
public:
	Judge();
	~Judge();

	int Rule_order(int color,int row,char col);//规则判断,color为当前落子颜色

	int Rule_disallowed_moves(Array_data a, int row,int col);//禁手规则,返回0表示未违反禁手规则
	int LongConnect_judge(Array_data a,int row,int col,int count,char flag);//长连禁手,row、col分别为横纵坐标,count为长度计数,flag是长连方位选择
	int Double_3_judge(Array_data a,int row,int col,int color);//双活三禁手,考虑以禁解禁的情况
	int Ban_lift_ban(Array_data a, int row, int col);//以禁解禁处理
	int Double_4_judge(Array_data a, int row, int col,int color);//双四禁手
	int Double_2_judge(Array_data a, int row, int col, int color);//双二判断
	int Alive_3(Array_data a,int row,int col,char flag,int color);//活三、死三、非三判断
	int Alive_4(Array_data a, int row, int col,char flag,int color);//活四、死四、非四判断,color为当前执子颜色(参照account中颜色定义)
	int Alive_2(Array_data a, int row, int col,char flag,int color);//活二、死二、非二判断

	int Judgement(Array_data a,int row,int col,int color);//判定输赢
};

