#include "Array_data.h"
#include "ChessBoard.h"
#include "Chessman.h"
//using namespace std;

ChessBoard cb;
Chessman cm;

Array_data::Array_data()
{
	int i ,j = 0;
	for (i = 0; i < ROW; i++)
	{
		data[i] = new char*[COL];
		for (j = 0; j < COL; j++)
		{
			data[i][j] = new char[10];
		}
	}
	/*1
	for (j = 0; j < COL-1; j++)
	{
		last_row[j] = (char)(65 + j);
	}
	*/
}

Array_data::~Array_data()
{
}

void Array_data::Write_data(int x, int y,int flag,int color,int state)
{
	if (flag == 0)
	{//初次初始化棋盘
		int i, j = 0;
		for (i = 0; i<ROW; i++)
			for (j = 0; j < COL; j++)
			{
				if (i == (ROW - 1))
				{
					//最后一行，标出列数的行
					if (j == 1)
						TransferType(data[i][j], " A");
					else if (j == 2)
						TransferType(data[i][j], " B");
					else if (j == 3)
						TransferType(data[i][j], " C");
					else if (j == 4)
						TransferType(data[i][j], " D");
					else if (j == 5)
						TransferType(data[i][j], " E");
					else if (j == 6)
						TransferType(data[i][j], " F");
					else if (j == 7)
						TransferType(data[i][j], " G");
					else if (j == 8)
						TransferType(data[i][j], " H");
					else if (j == 9)
						TransferType(data[i][j], " I");
					else if (j == 10)
						TransferType(data[i][j], " J");
					else if (j == 11)
						TransferType(data[i][j], " K");
					else if (j == 12)
						TransferType(data[i][j], " L");
					else if (j == 13)
						TransferType(data[i][j], " M");
					else if (j == 14)
						TransferType(data[i][j], " N");
					else if (j == 15)
						TransferType(data[i][j], " O");
					else
						TransferType(data[i][j], " ");
				}
				else
				{
					if (j == 0)
					{
						//第一列,标出行数的列
						if ((15 - i) < 10)
						{
							sprintf(data[i][j], " %d", (15 - i));//1-9
						}
						else
						{
							sprintf(data[i][j], "%d", (15 - i));//10-15
						}
						//cout << data[i][j];	
					}
					else
					{
						//正式棋盘
						//i:0-14
						//j:1-15
						TransferType(data[i][j], cb.ChessStyle(i, j));
						//cout << data[i][j];
					}
				}
				
				
			}
	}
	else
	{
		//输入棋子坐标，读取棋子
		TransferType(data[x][y],cm.chessman_type(color,state));
		//账本记录
		if (color == 0)
		{
			account_data[x][y] = 1;//黑
		}
		else
		{
			account_data[x][y] = 2;//白
		}
	}


	/*1
	for (j = 0; j < COL; j++)
	{
		cout << last_row[j];
	}
	*/
}

void Array_data::TransferType(char *dest,const char *src)
{
	strcpy(dest, src);
}

void Array_data::Show_data()
{
	cout << "\n **Welcome to Five_In_Row Game**\n\tAuthor: Lin\n\tBlack:● White:○\n\n";
	//cout << data[i][j];

	int i, j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			cout << data[i][j];
		}
		cout << "\n";
	}
}

int Array_data::Read_data(int row,int col)
{
	//row和col是已经转为array_data的对应坐标

	if (account_data[row][col] == 1)
	{
		return 1;
	}
	else if (account_data[row][col] == 2)
	{
		return 2;
	}
	else
		return 0;
}

void Array_data::write_row_col(int m_row, char m_col)
{
	machine_row = m_row;
	machine_col = m_col;
}

int Array_data::read_row()
{
	return machine_row;
}

char Array_data::read_col()
{
	return machine_col;
}