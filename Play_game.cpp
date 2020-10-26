#include "Play_game.h"



using namespace std;

Play_game::Play_game()
{
}


Play_game::~Play_game()
{
}


void Play_game::Play_1(Array_data a,int color,const char *player_role,int order,int state)
{
	Game g;
	Show show;//显示对象
	Judge judge;
	int current_result = 0;//裁判判决结果,1为执黑胜，2为执白胜，0为未分胜负,3为平局
	char col = ' ';
	int row = -1;

	while (1)
	{
		//循环一盘棋局

		if (state == 0)
		{
			//当前落子

			if (color == 0)
			{
				//执黑"●"
				//博弈
				cout << "\nRound "<< order << ": " << player_role << " (●) please input piece position (eg:A1 or a1):";//按照棋盘样式输入，字母为列，数字为行
				//scanf("%c%d",&col,&row);
				cin >> col >> row;
				while (cin.fail())
				{
					system("cls");//清屏
					a.Show_data();
					cin.clear(); //清除流标记
					cin.sync();  //清空流
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
				}


				//裁判判定当前是否合法
				if (order == 1)
				{
					//第一回合
					while (judge.Rule_order(color, row, col) != 1)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1,22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
						cout << "\nThe first piece must be in the position: TianYuan (H8 or h8) for Round 1.\nPlease input piece position again:";
						scanf("%c%d", &col, &row);
					}
				}
				//输入范围合法判断,行列输入颠倒也要识别
				while (((col > 79 && col < 97) || col < 65 || col >111) || row > 15 || row < 1)
				{
					system("cls");//清屏
					a.Show_data();
					//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
					//col输入非法
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}
				//输入不可是已存在棋子位置
				while (1)
				{
					//将输入的坐标转为数字传递,且符合Array_data数组坐标
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;//同col处理

					int temp = 0;
					temp = a.Read_data(row, col);
					if (temp == 1 || temp == 2)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
										   //col输入棋子位置已存在棋子
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//清屏
							a.Show_data();
							cin.clear(); //清除流标记
							cin.sync();  //清空流
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
						break;//未占有当前已有棋子，结束循环
				}


				//只对执黑方进行禁手判定
				int judge_result = 10;//-1是长连禁手，-2是双活三禁手，-3是双四禁手
				//int judge_double_3 = 10;
				//int judge_double_4 = 10;
				judge_result = judge.Rule_disallowed_moves(a, row, col);

				//cout << judge_long;
				if (judge_result == -1)//-1则触犯长连
				{
					current_result = 2;//白棋胜
					cout << "\nLong Ban.\n";
				}
				else if (judge_result == -2)//-2即触犯双活三禁手
				{
					current_result = 2;
					cout << "\nDouble_3 Ban.\n";
				}
				else if (judge_result == -3)//-3即触犯双四禁手
				{
					current_result = 2;
					cout << "\nDouble_4 Ban.\n";
				}
				else
				{
					//所有规则都合法,写入
					a.Write_data(row, col, 1, color, state);//最后一个参数state=0表示当前落子
					system("cls");//清屏
					a.Show_data();

					//胜负判断(包括平局)
					int judge_temp = 0;
					judge_temp = judge.Judgement(a, row, col, color);
					if (judge_temp == 1)
					{
						current_result = 1;
					}
					else if (judge_temp == 2)
					{
						current_result = 3;//和棋
					}

					state = 1;
					//order ++;//回合数加1
					//Play_1(a, color, player_role, order, state, row, col);
				}

			}
			else
			{
				//执白"○"◎
				//博弈
				if (strcmp(player_role,"Player1") == 0)
				{
					//若当前玩家角色是从Player1开始，则白棋为Player2
					cout << "\nRound " << order << ": " << "Player2" << " (○) please input piece position (eg:A1 or a1):";//按照棋盘样式输入，字母为列，数字为行
				}
				else
				{
					cout << "\nRound " << order << ": " << "Player1" << " (○) please input piece position (eg:A1 or a1):";
				}
				cin >> col >> row;
				while (cin.fail())
				{
					system("cls");//清屏
					a.Show_data();
					cin.clear(); //清除流标记
					cin.sync();  //清空流
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
				}

				//裁判判定当前是否合法
				//输入范围合法判断
				while ((col > 79 && col < 97) || col < 65 || col >111 || row > 15 || row < 1)
				{
					system("cls");//清屏
					a.Show_data();
					//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
									   //col输入非法
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//输入不可是已存在棋子位置
				while (1)
				{
					//将输入的坐标转为数字传递,且符合Array_data数组坐标
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;

					int temp = 0;
					temp = a.Read_data(row, col);
					cout << temp;
					//if (temp == "▲" || temp == "●" || temp == "△" || temp == "○")
					if (temp != 0)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
										   //col输入棋子位置已存在棋子
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//清屏
							a.Show_data();
							cin.clear(); //清除流标记
							cin.sync();  //清空流
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
					{
						cout << temp;
						break;//未占有当前已有棋子，结束循环
					}

				}

				//范围合法,写入
				a.Write_data(row, col, 1, color, state);//最后一个参数state=0表示当前落子
				system("cls");//清屏
				a.Show_data();
				//判断胜负
				int judge_temp = 0;
				judge_temp = judge.Judgement(a, row, col, color);
				if (judge_temp == 1)
				{
					current_result = 2;
				}
				else if (judge_temp == 2)
				{
					current_result = 3;
				}

				state = 1;
				order++;//回合数加1
				//Play_1(a, color, player_role, order, state, row, col);
			}
		}
		else
		{
			//state =1,非当前落子
			a.Write_data(row, col, 1, color, state);//更新棋盘中棋子样式
			state = 0;
			if (color == 0)
			{
				color = 1;//转换为白棋
			}
			else
			{
				color = 0;//转换为黑棋
			}
		}


		if (current_result == 0)
		{
			continue;//当前棋局未结束
		}
		else if (current_result == 1)
		{
			//执黑玩家胜利
			cout << "\n " << player_role << " wins!\n";
			
			break;//当前棋局结束
		}
		else if (current_result == 2)
		{
			//执白玩家胜利
			if (strcmp(player_role,"Player1") == 0)
			{
				cout << "\n	Player2 wins!\n";
			}
			else
			{
				cout << "\n Player1 wins!\n";
			}

			break;//当前棋局结束
		}
		else
		{
			//当所有棋子下满且未分胜负时
			cout << "\n This game draws!\n";

			break;//当前棋局结束
		}
	}

	//调用是否进行新开始一盘的对象
	Play_again(g);
	
}

void Play_game::Play_2(Array_data a, int color, const char *player_role, int order, int state)
{
	Game g;
	Show show;//显示对象
	Judge judge;
	int current_result = 0;//裁判判决结果,1为执黑胜，2为执白胜，0为未分胜负,3为平局
	char col = ' ';
	int row = -1;

	int account_color = -1;//用于机器人判断时知道执子颜色，依据account
	if (strcmp(player_role, "Machine") == 0)
	{
		account_color = 1;//黑
	}
	else
	{
		account_color = 2;//白
	}

	while (1)
	{
		//循环一盘棋局

		if (state == 0)
		{
			//当前落子

			if (color == 0)
			{
				//执黑"●"
				//博弈
				if (strcmp(player_role, "Machine") == 0)
				{
					//机器执黑
					if (order == 1)
					{
						row = 8;
						col = 'H';
						a.write_row_col(row,col);
					}
					else
					{
						int* temp = new int[2];

						temp = score_account(a, judge, account_color);


						row = 15 - temp[0];
						col = (char)(64 + temp[1]);

						delete[] temp;

						a.write_row_col(row, col);
					}
				}
				else
				{
					if (order > 1)
					{
						//非第一回合
						cout << "\nMachine last piece position: "<< a.read_col() << a.read_row();//输出上回合机器所下的位置
					}
					//玩家执黑
					cout << "\nRound " << order << ": " << player_role << " (●) please input piece position (eg:A1 or a1):";//按照棋盘样式输入，字母为列，数字为行
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//裁判判定当前是否合法
				if (order == 1)
				{
					//第一回合
					while (judge.Rule_order(color, row, col) != 1)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1,22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
						cout << "\nThe first piece must be in the position: TianYuan (H8 or h8).\nPlease input piece position again:";
						scanf("%c%d", &col, &row);
					}
				}
				//输入范围合法判断,行列输入颠倒也要识别
				while (((col > 79 && col < 97) || col < 65 || col >111) || row > 15 || row < 1)
				{
					system("cls");//清屏
					a.Show_data();
					//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
					//col输入非法
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}
				//输入不可是已存在棋子位置
				while (1)
				{
					//将输入的坐标转为数字传递,且符合Array_data数组坐标
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;//同col处理

					int temp = 0;
					temp = a.Read_data(row, col);
					if (temp == 1 || temp == 2)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
						//col输入棋子位置已存在棋子
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//清屏
							a.Show_data();
							cin.clear(); //清除流标记
							cin.sync();  //清空流
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
						break;//未占有当前已有棋子，结束循环
				}


				//只对执黑方进行禁手判定
				int judge_result = 10;//-1是长连禁手，-2是双活三禁手，-3是双四禁手
									  //int judge_double_3 = 10;
									  //int judge_double_4 = 10;
				judge_result = judge.Rule_disallowed_moves(a, row, col);

				//cout << judge_long;
				if (judge_result == -1)//-1则触犯长连
				{
					current_result = 2;//白棋胜
					cout << "\nLong Ban.\n";
				}
				else if (judge_result == -2)//-2即触犯双活三禁手
				{
					current_result = 2;
					cout << "\nDouble_3 Ban.\n";
				}
				else if (judge_result == -3)//-3即触犯双四禁手
				{
					current_result = 2;
					cout << "\nDouble_4 Ban.\n";
				}
				else
				{
					//所有规则都合法,写入
					a.Write_data(row, col, 1, color, state);//最后一个参数state=0表示当前落子
					system("cls");//清屏
					a.Show_data();

					//胜负判断(包括平局)
					int judge_temp = 0;
					judge_temp = judge.Judgement(a, row, col, color);
					if (judge_temp == 1)
					{
						current_result = 1;
					}
					else if (judge_temp == 2)
					{
						current_result = 3;//和棋
					}

					state = 1;
					//order ++;//回合数加1
					//Play_1(a, color, player_role, order, state, row, col);
				}

			}
			else
			{
				//执白"○"◎
				//博弈
				if (strcmp(player_role, "Player") == 0)
				{
					//若当前玩家角色是从Player开始，则白棋为Machine
					//cout << "\nRound " << order << ": " << "Machine" << " (○) please input piece position (eg:A1 or a1):";//按照棋盘样式输入，字母为列，数字为行
					int* temp = new int[2];

					temp = score_account(a, judge, account_color);


					row = 15 - temp[0];
					col = (char)(64 + temp[1]);

					delete[] temp;

					a.write_row_col(row, col);
				}
				else
				{
					cout << "\nMachine last piece position: " << a.read_col() << a.read_row() << "\n";//输出上回合机器所下的位置
					cout << "Round " << order << ": " << "Player" << " (○) please input piece position (eg:A1 or a1):";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//裁判判定当前是否合法
				//输入范围合法判断
				while ((col > 79 && col < 97) || col < 65 || col >111 || row > 15 || row < 1)
				{
					system("cls");//清屏
					a.Show_data();
					//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
					//col输入非法
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//清屏
						a.Show_data();
						cin.clear(); //清除流标记
						cin.sync();  //清空流
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//输入不可是已存在棋子位置
				while (1)
				{
					//将输入的坐标转为数字传递,且符合Array_data数组坐标
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;

					int temp = 0;
					temp = a.Read_data(row, col);
					cout << temp;
					//if (temp == "▲" || temp == "●" || temp == "△" || temp == "○")
					if (temp != 0)
					{
						system("cls");//清屏
						a.Show_data();
						//show.gotoxy(1, 22);//从棋盘后空一行进行提示信息显示，因此从此处开始清除信息
						//col输入棋子位置已存在棋子
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//清屏
							a.Show_data();
							cin.clear(); //清除流标记
							cin.sync();  //清空流
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
					{
						cout << temp;
						break;//未占有当前已有棋子，结束循环
					}

				}

				//范围合法,写入
				a.Write_data(row, col, 1, color, state);//最后一个参数state=0表示当前落子
				system("cls");//清屏
				a.Show_data();
				//判断胜负
				int judge_temp = 0;
				judge_temp = judge.Judgement(a, row, col, color);
				if (judge_temp == 1)
				{
					current_result = 2;
				}
				else if (judge_temp == 2)
				{
					current_result = 3;
				}

				state = 1;
				order++;//回合数加1
						//Play_1(a, color, player_role, order, state, row, col);
			}
		}
		else
		{
			//state =1,非当前落子
			a.Write_data(row, col, 1, color, state);//更新棋盘中棋子样式
			state = 0;
			if (color == 0)
			{
				color = 1;//转换为白棋
			}
			else
			{
				color = 0;//转换为黑棋
			}
		}


		if (current_result == 0)
		{
			continue;//当前棋局未结束
		}
		else if (current_result == 1)
		{
			//执黑玩家胜利
			cout << "\n " << player_role << " wins!\n";

			break;//当前棋局结束
		}
		else if (current_result == 2)
		{
			//执白玩家胜利
			if (strcmp(player_role, "Player") == 0)
			{
				cout << "\n	Machine wins!\n";
			}
			else
			{
				cout << "\n Player wins!\n";
			}

			break;//当前棋局结束
		}
		else
		{
			//当所有棋子下满且未分胜负时
			cout << "\n This game draws!\n";

			break;//当前棋局结束
		}
	}

	//调用是否进行新开始一盘的对象
	Play_again(g);
}

void Play_game::Play_again(Game g)
{
	char answer = ' ';
	cout << "\n Do you want to play again? Y/N\n";
	cin >> answer;
	
	if (answer == 'Y' || answer == 'y')
	{
		system("cls");
		g.Run_Game(g);
	}
	else
	{
		system("exit");
	}
}

int* Play_game::score_account(Array_data a,Judge judge,int color)
{
	int x = 4;//row 0
	int y = 1;//col 1

	int i = 1;

	int op_color = -1;//非当前执子颜色
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	//计分过程分值最高的空格坐标
	int max_score_row = 0;
	int max_score_col = 1;
	int max_score = 0;

	while (x <= 14)
	{
		y = 1;//y重置
		while (y <= 15)
		{
			int machine_score = 0;//机器人考虑自身取分
			int human_score = 0;//机器人考虑人类棋局取分

			i = 1;//每一格结束重新初始化

			while (a.account_data[x][y] == 0 && i < 5)
			{
				//当前遍历棋格为空格,且搜索范围小于2
				//横
				if ((y - i) > 0 && (y + i) < 16)
				{
					if (a.account_data[x][y - i] != 0 || a.account_data[x][y + i] != 0)
					{
						//左右存在已下棋子
						//能成死二
						if (judge.Alive_2(a, x, y, 'h', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//能成活二
						if (judge.Alive_2(a, x, y, 'h', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 10;
						}
						//能成死三
						if (judge.Alive_3(a, x, y, 'h', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 50;
						}
						//能成活三
						if (judge.Alive_3(a, x, y, 'h', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 200;
						}
						//能成死四
						if (judge.Alive_4(a, x, y, 'h', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 500000;
						}
						//能成活四
						if (judge.Alive_4(a, x, y, 'h', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//竖
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y] != 0 || a.account_data[x + i][y] != 0)
					{
						//上下存在已下棋子
						//能成死二
						if (judge.Alive_2(a, x, y, 's', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 's', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//能成活二
						if (judge.Alive_2(a, x, y, 's', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 's', op_color) == 1)
						{
							human_score -= 10;
						}
						//能成死三
						if (judge.Alive_3(a, x, y, 's', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 's', op_color) == 2)
						{
							human_score -= 50;
						}
						//能成活三
						if (judge.Alive_3(a, x, y, 's', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 's', op_color) == 1)
						{
							human_score -= 200;
						}
						//能成死四
						if (judge.Alive_4(a, x, y, 's', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 's', op_color) == 2)
						{
							human_score -= 500000;
						}
						//能成活四
						if (judge.Alive_4(a, x, y, 's', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 's', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//左斜
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y + i] != 0 || a.account_data[x + i][y - i] != 0)
					{
						//右上左下存在已下棋子
						//能成死二
						if (judge.Alive_2(a, x, y, 'z', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//能成活二
						if (judge.Alive_2(a, x, y, 'z', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 10;
						}
						//能成死三
						if (judge.Alive_3(a, x, y, 'z', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 50;
						}
						//能成活三
						if (judge.Alive_3(a, x, y, 'z', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 200;
						}
						//能成死四
						if (judge.Alive_4(a, x, y, 'z', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 500000;
						}
						//能成活四
						if (judge.Alive_4(a, x, y, 'z', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//右斜
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y - i] != 0 || a.account_data[x + i][y + i] != 0)
					{
						//上下存在已下棋子
						//能成死二
						if (judge.Alive_2(a, x, y, 'f', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//能成活二
						if (judge.Alive_2(a, x, y, 'f', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 10;
						}
						//能成死三
						if (judge.Alive_3(a, x, y, 'f', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 50;
						}
						//能成活三
						if (judge.Alive_3(a, x, y, 'f', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 200;
						}
						//能成死四
						if (judge.Alive_4(a, x, y, 'f', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 500000;
						}
						//能成活四
						if (judge.Alive_4(a, x, y, 'f', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//与方向无关，即综合多方向
				//能成双活二
				if (judge.Double_2_judge(a, x, y, color) == 1)
				{
					machine_score += 20;
				}
				if (judge.Double_2_judge(a, x, y, op_color) == 1)
				{
					human_score -= 20;
				}
				//能成死三活三
				//不同方向上的三三结合，且一个为死三，一个为活三
				//横，活
				if (judge.Alive_3(a, x, y, 'h', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//竖，活
				if (judge.Alive_3(a, x, y, 's', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 's', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//左斜，活
				if (judge.Alive_3(a, x, y, 'z', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//右斜，活
				if (judge.Alive_3(a, x, y, 'f', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//能成双活三
				if (judge.Double_3_judge(a, x, y, color) == -1)
				{
					if (color == 1)
					{
						//机器执黑禁手
						machine_score -= 10000000;
					}
					else
					{
						machine_score += 500000;
					}
				}
				if (judge.Double_3_judge(a, x, y, op_color) == -1)
				{
					if (op_color == 1)
					{
						//对手执黑
						human_score += 10000000;//机器不用堵
					}
					else
					{
						human_score -= 500000;
					}
					
				}
				//能成双四
				if (judge.Double_4_judge(a, x, y, color) == -1)
				{
					if (color == 1)
					{
						machine_score -= 10000000;
					}
					else
					{
						machine_score += 10000000;
					}
				}
				if (judge.Double_4_judge(a, x, y, op_color) == -1)
				{
					if (op_color == 1)
					{
						human_score += 10000000;
					}
					else
					{
						human_score -= 100000000;
					}
					
				}
				//长连禁手，长连只对黑子进行计数
				if (judge.LongConnect_judge(a, x, y, 1, 'h') == -1)
				{
					if (color == 1)
					{
						//机器
						machine_score -= 10000000;
					}
					else
					{
						//玩家
						human_score += 10000000;
					}
					
				}

				//能成死四活三
				//造成不同方向上的四三结合
				//横四
				if (judge.Alive_4(a, x, y, 'h', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'h', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//竖四
				if (judge.Alive_4(a, x, y, 's', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 's', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//左斜，四
				if (judge.Alive_4(a, x, y, 'z', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'z', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//右斜，四
				if (judge.Alive_4(a, x, y, 'f', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'f', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}

				//能成五（执白为五或五以上）,长连禁手
				if (judge.Judgement(a, x, y, color) == 1)
				{
					machine_score += 10000000000;
				}
				if (judge.Judgement(a, x, y, op_color) == 1)
				{
					human_score -= 1000000000;
				}
				//计算并存储当前空格最终得分
				a.score[x][y] = machine_score - human_score;
				//更新最大分值及对应坐标
				if (max_score < a.score[x][y])
				{
					max_score = a.score[x][y];
					max_score_row = x;
					max_score_col = y;
				}
				else if (max_score == a.score[x][y])
				{
					srand((int)time(0));
					int temp = random(1);
					if (temp == 0)
					{
						max_score = a.score[x][y];
						max_score_row = x;
						max_score_col = y;
					}
				}

				i += 1;

			}
			y += 1;
		}
		x += 1;
	}	

	int* temp = new int[2];
	
	temp[0] = max_score_row;
	temp[1] = max_score_col;

	return temp;
}