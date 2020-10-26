#include "Player.h"
#include "Play_game.h"

using namespace std;

Player::Player()
{
}


Player::~Player()
{
}

int Player::Mode_choose()
{
	int mode = 0;

	cout << "\nPlease choose the mode for playing.\n mode 1: People vs People\n mode 2: People vs Machine\n Your chosen(1 or 2):";
	cin >> mode;

	while(mode != 1 && mode != 2)
	{
		cout << "Your chosen is wrong.\nPlease choose your mode(1 or 2) again:";
		cin.clear(); //清除流标记
		cin.sync();  //清空流
		cin >> mode;
	}

	return mode;
}

void Player::People_vs_People(Array_data a)
{
	int current_order = 0;//先手选择
	system("cls");//清屏
	a.Show_data();
	cout << "\nYour chosen is: People vs People\n Player List: Player_1 , Player_2\n Please choose who from Player List starts first.\n Your chosen(1 or 2):";
	cin >> current_order;
	while (current_order != 1 && current_order != 2)
	{
		cout << "Your chosen is wrong.Player List: Player_1 , Player_2\nPlease choose who(1 or 2) starts first again:";
		cin.clear(); //清除流标记
		cin.sync();  //清空流
		cin >> current_order;
	}


	if (current_order == 1)
	{
		//Player_1 use Black_piece
		player1_color = 0;
		player2_color = 1;
	}
	else
	{
		player1_color = 1;
		player2_color = 0;
	}

	Play_game play_1;//人人博弈对象

	int state = 0;//棋子状态，0为当前落子，1为前一落子

	 /*
		循环直到出现当前棋局游戏结束
	*/
	
	if (player1_color == 0)
	{
		//玩家一执黑
		play_1.Play_1(a, player1_color, "Player1", order, state);

	}
	else if(player1_color != 0)
	{
		//玩家2执黑
		play_1.Play_1(a, player2_color, "Player2", order, state);

	}
	
	
}

void Player::People_vs_Machine(Array_data a)
{
	int current_order = 0;//先手选择
	system("cls");//清屏
	a.Show_data();
	cout << "\nYour chosen is: People vs Machine\n Player List: Player , Machine\n Please choose who from Player List starts first.\n Your chosen(1 or 2):";
	cin >> current_order;
	while (current_order != 1 && current_order != 2)
	{
		cout << "Your chosen is wrong.Player List: Player , Machine\nPlease choose who(1 or 2) starts first again:";
		cin.clear(); //清除流标记
		cin.sync();  //清空流
		cin >> current_order;
	}


	if (current_order == 1)
	{
		//Player use Black_piece
		player1_color = 0;
		player2_color = 1;//机器
	}
	else
	{
		//机器执黑
		player1_color = 1;
		player2_color = 0;//机器
	}

	Play_game play_2;//人机博弈对象

	int state = 0;//棋子状态，0为当前落子，1为前一落子

				  /*
				  循环直到出现当前棋局游戏结束
				  */

	if (player1_color == 0)
	{
		//玩家执黑
		play_2.Play_2(a, player1_color, "Player", order, state);

	}
	else if (player1_color != 0)
	{
		//机器执黑
		play_2.Play_2(a, player2_color, "Machine", order, state);

	}
}