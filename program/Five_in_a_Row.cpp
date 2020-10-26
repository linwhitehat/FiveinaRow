/**
five_in_a_row
main.cpp
2018.10 by lin
*/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "Game.h"

using namespace std;

int main()
{
	//cout << "\n **Welcome to Five_In_Row Game**\n\tAuthor: Lin\n\n";
	Game game_1;//游戏对象
	
	game_1.Run_Game(game_1);//开始游戏

	return 0;
}