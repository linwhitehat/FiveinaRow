#include "Judge.h"



Judge::Judge()
{
}


Judge::~Judge()
{
}


int Judge::Rule_order(int color,int row,char col)
{
	//行棋顺序判定
	int order_judge = 0;
	//判定是否为棋局第一子
	//第一回合
	//判定是否是黑方先落第一子
	if (color == 0)
	{
		//当前棋子为黑子
		//判定第一子是否落在天元位置,h8
		if (row == 8 && (col == 'H' || col == 'h'))
		{
			order_judge = 1;//合规
		}
		else
			return order_judge;
	}
	else
		return order_judge;

	return order_judge;
}

int Judge::Rule_disallowed_moves(Array_data a,int row,int col)
{
	//int count = 1;//int h, s, z, f = 1;//横竖正斜反斜四个方向,以当前子为基点，已有计数1
	int long_result = 0;//长连禁手
	int double_3_result = 0;//双活3禁手
	int double_4_result = 0;//双四禁手
	
	//双活三禁手
	double_3_result = Double_3_judge(a, row, col,1);
	if (double_3_result != 0)
	{
		double_3_result  = -2;
		return double_3_result;
	}
	//四四禁手
	double_4_result = Double_4_judge(a, row, col,1);
	if (double_4_result != 0)
	{
		double_4_result = -3;
		return double_4_result;
	}
	//长连禁手
	/**横向*/
	long_result = LongConnect_judge(a,row,col,1,'h');
	if (long_result != 0)
	{
		return long_result;//-1
	}
	/**纵向*/
	long_result = LongConnect_judge(a, row, col, 1, 's');
	if (long_result != 0)
	{
		return long_result;
	}
	/**左斜 “/”*/
	long_result = LongConnect_judge(a, row, col, 1, 'z');
	if (long_result != 0)
	{
		return long_result;
	}
	/**右斜 “\”*/
	long_result = LongConnect_judge(a, row, col, 1, 'f');
	if (long_result != 0)
	{
		return long_result;
	}

	//不可返回多个值
	//return long_result,double_3_result,double_4_result;//无触犯禁手,0
	return 0;
}

int Judge::LongConnect_judge(Array_data a,int row,int col,int count,char flag)
{
	int i = 1;
	int result = 0;

	//根据测试方位处理坐标
	if (flag == 'h')
	{
		//为了避免count的重复计算，还没找出原因之前使用这个方式进行再次初始化
		count = 1;
		//向左检测
		while ((col - i) > 0 && a.Read_data(row, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//向左延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右检测
		while ((col + i) < 16 && a.Read_data(row, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else if (flag == 's')
	{
		count = 1;
		//向上检测
		while ((row - i) > -1 && a.Read_data(row - i, col) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//向上延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向下检测
		while ((row + i) < 15 && a.Read_data(row + i, col) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else if (flag == 'z')
	{
		count = 1;
		//向左下检测
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//向左下延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右上检测
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else
	{
		//向左上检测
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//向左下延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右下检测
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}

	return result;//未触犯禁手,0
}

int Judge::Alive_3(Array_data a, int row, int col,char flag,int color)
{
	//返回0是非三，1是活三，2为死三
	int result = 0;
	int count = 1;//连子长度
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

	if (flag == 'h')
	{
		//直三横
		//向左检测
		while ((col - i) > 0 && a.Read_data(row, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				//当前落子在account数组中记录,将account账单数据变为非私有数据
				a.account_data[row][col] = color;

				if ((col - i - 1) > 0 && (col + 1) < 16)
				{
					//存在三连子情况下判断活子情况
					if ((Alive_4(a, row, col + 1, flag,color) == 1) || (Alive_4(a, row, col - i - 1, flag,color) == 1))
					{
						//活三
						result = 1;
					}
					else if ((Alive_4(a, row, col + 1, flag,color) == 0) && (Alive_4(a, row, col - i - 1, flag,color) == 0))
					{
						//非三
						result = 0;
					}
					else
					{
						//死三
						result = 2;
					}
				}
				else
				{
					//三连子的某一侧不存在空格，处于棋盘边缘
					if ((col == 15 && Alive_4(a, row, col - i - 1, flag,color) == 0) || ((col - i) == 1 && Alive_4(a, row, col + 1, flag,color) == 0))
					{
						//当前点所在是最后一列，三子最左边一子的左边为白棋
						//当前点三子的最左边一子在第一列，当前子的右边为白棋
						//非三
						result = 0;
					}
					else
					{
						//死三
						result = 2;
					}

				}

				//活三判断结束，恢复account中数据
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;//向左延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右检测
		while ((col + i) < 16 && a.Read_data(row, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((col - 1) > 0 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row, col + i + 1, flag,color) == 1 || Alive_4(a, row, col - 1, flag,color) == 1)
					{
						result = 1;//活三
					}
					else if (Alive_4(a, row, col + i + 1, flag,color) == 0 && Alive_4(a, row, col - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((col == 1 && Alive_4(a, row, col + i + 1, flag,color) == 0) || ((col + i) == 15 && Alive_4(a, row, col - 1, flag,color) == 0))
					{
						//当前点在第一列，三子的最右边一子的右边为白棋
						//当前点的三子最右边一子在最后一列，当前子的左边一子为白棋
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;
		}

		//跳三横向
		int left_neighbor = -1;//当前落子的左邻点
		int right_neighbor = -1;//当前落子的右邻点

		if (col - 3 > 0)
		{
			//左邻点存在
			left_neighbor = a.Read_data(row, col - 1);
			if (left_neighbor == 0)
			{
				//左邻点为空
				if ((a.Read_data(row, col - 2) == color) && (a.Read_data(row, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//左2左3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((col + 1 < 16) && (a.Read_data(row, col - 2) == color) && (a.Read_data(row, col + 1) == color))
				{
					a.account_data[row][col] = color;
					//左2右1为黑棋
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (left_neighbor == color)
			{
				//左邻点为黑棋
				if ((a.Read_data(row, col - 2) == 0) && (a.Read_data(row, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//左2为空左三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col + 3 < 16)
		{
			//右邻点存在
			right_neighbor = a.Read_data(row, col + 1);
			if (right_neighbor == 0)
			{
				//右邻点为空
				if ((a.Read_data(row, col + 2) == color) && (a.Read_data(row, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//右2右3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((col - 1>0) && (a.Read_data(row, col + 2) == color) && (a.Read_data(row, col - 1) == color))
				{
					a.account_data[row][col] = color;
					//右2左1为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (right_neighbor == color)
			{
				//右邻点为黑棋
				if ((a.Read_data(row, col + 2) == 0) && (a.Read_data(row, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//右2为空右三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col - 2 == 1)
		{
			//边缘区域，只有死三和非三
			if (a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == color && a.Read_data(row, col + 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col + 2 == 15)
		{
			if (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == color && a.Read_data(row, col - 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		
		//死三三种特殊情况
		if ((a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == color && a.Read_data(row, col - 3) == 0 && a.Read_data(row, col - 4) == color) || (a.Read_data(row,col-1)==0 && a.Read_data(row,col-2) == 0 && a.Read_data(row,col-3) == color && a.Read_data(row,col-4) == color) || (a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == 0 && a.Read_data(row, col - 3) == color && a.Read_data(row, col - 4) == color && a.Read_data(row,col-5) == op_color))
		{
			//left
			result = 2;
		}
		else if ((a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == color && a.Read_data(row, col + 3) == 0 && a.Read_data(row, col + 4) == color) || (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == 0 && a.Read_data(row, col + 3) == color && a.Read_data(row, col + 4) == color) || (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == 0 && a.Read_data(row, col + 3) == color && a.Read_data(row, col + 4) == color && a.Read_data(row, col + 5) == op_color))
		{
			result = 2;
		}


		return result;

	}


	if (flag == 's')
	{
		//竖
		//向上检测
		while ((row - i) > -1 && a.Read_data(row - i, col) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (row - i - 1) > -1)
				{
					if (Alive_4(a, row + 1, col, flag,color) == 1 || Alive_4(a, row - i - 1, col, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col, flag,color) == 0 && Alive_4(a, row - i - 1, col, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && Alive_4(a, row - i - 1, col, flag,color) == 0) || ((row - i) == 0 && Alive_4(a, row + 1, col, flag,color) == 0))
					{
						//当前子在最后一行，三子的最上边一子的上一个子为白棋
						//当前子的三子的最上面一子在第一行，当前子的下面一个子为白棋
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;//向上延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向下检测
		while ((row + i) < 15 && a.Read_data(row + i, col) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (row + i + 1) < 15)
				{
					if (Alive_4(a, row - 1, col, flag,color) == 1 || Alive_4(a, row + i + 1, col, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col, flag,color) == 0 && Alive_4(a, row + i + 1, col, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && Alive_4(a, row + i + 1, col, flag,color) == 0) || ((row + i) == 14 && Alive_4(a, row - 1, col, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//跳三竖向
		int up_neighbor = -1;
		int down_neighbor = -1;

		if (row - 3 > -1)
		{
			//上邻点存在
			up_neighbor = a.Read_data(row - 1, col);
			if (up_neighbor == 0)
			{
				//上邻点为空
				if ((a.Read_data(row - 2, col) == color) && (a.Read_data(row - 3, col) == color))
				{
					a.account_data[row][col] = color;
					//up2up3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col) == color) && (a.Read_data(row + 1, col) == color))
				{
					a.account_data[row][col] = color;
					//up2down1为黑棋
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (up_neighbor == 1)
			{
				//up邻点为黑棋
				if ((a.Read_data(row - 2, col) == 0) && (a.Read_data(row - 3, col) == color))
				{
					a.account_data[row][col] = color;
					//up2为空down三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down邻点存在
			down_neighbor = a.Read_data(row + 1, col);
			if (down_neighbor == 0)
			{
				//down邻点为空
				if ((a.Read_data(row + 2, col) == color) && (a.Read_data(row + 3, col) == color))
				{
					a.account_data[row][col] = color;
					//down2down3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col) == color) && (a.Read_data(row - 1, col) == color))
				{
					a.account_data[row][col] = color;
					//down2up1为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (down_neighbor == 1)
			{
				//右邻点为黑棋
				if ((a.Read_data(row + 2, col) == 0) && (a.Read_data(row + 3, col) == color))
				{
					a.account_data[row][col] = color;
					//右2为空右三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//边缘区域，只有死三和非三
			if (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == color && a.Read_data(row + 1, col) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == color && a.Read_data(row - 1, col) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}

		//死三三种特殊情况
		if ((a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == color && a.Read_data(row - 3,col) == 0 && a.Read_data(row - 4, col) == color) || (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == 0 && a.Read_data(row - 3, col) == color && a.Read_data(row - 4, col) == color) || (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == 0 && a.Read_data(row - 3, col) == color && a.Read_data(row - 4, col) == color && a.Read_data(row - 5, col) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == color && a.Read_data(row + 3, col) == 0 && a.Read_data(row + 4, col) == color) || (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == 0 && a.Read_data(row + 3, col) == color && a.Read_data(row + 4, col) == color) || (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == 0 && a.Read_data(row + 3, col) == color && a.Read_data(row + 4, col) == color && a.Read_data(row + 5, col) == op_color))
		{
			result = 2;
		}

		return result;
	}


	if (flag == 'z')
	{
		//左斜
		//向左下检测
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (col + 1) < 16 && (row + i + 1) < 15 && (col - i - 1) > 0)
				{
					if (Alive_4(a, row - 1, col + 1, flag,color) == 1 || Alive_4(a, row + i + 1, col - i - 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col + 1, flag,color) == 0 && Alive_4(a, row + i + 1, col - i - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 15 && Alive_4(a, row + i + 1, col - i - 1, flag,color) == 0) || ((row + i) == 14 && (col - i) == 1 && Alive_4(a, row - 1, col + 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;//向左下延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右上检测
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (col - 1) > 0 && (row - i - 1) > -1 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row + 1, col - 1, flag,color) == 1 || Alive_4(a, row - i - 1, col + i + 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col - 1, flag,color) == 0 && Alive_4(a, row - i - 1, col + i + 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 1 && Alive_4(a, row - i - 1, col + i + 1, flag,color) == 0) || ((row - i) == 0 && (col + i) == 15 && Alive_4(a, row + 1, col - 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//跳三右上
		int up_right_neighbor = -1;
		//跳三左下
		int down_left_neighbor = -1;

		if (row - 3 > -1)
		{
			//右上邻点存在
			up_right_neighbor = a.Read_data(row - 1, col + 1);
			if (up_right_neighbor == 0)
			{
				//右上邻点为空
				if ((a.Read_data(row - 2, col + 2) == color) && (a.Read_data(row - 3, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//up2up3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col + 2) == color) && (a.Read_data(row + 1, col - 1) == color))
				{
					a.account_data[row][col] = color;
					//up2down1为黑棋
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (up_right_neighbor == 1)
			{
				//up_right邻点为黑棋
				if ((a.Read_data(row - 2, col + 2) == 0) && (a.Read_data(row - 3, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//up2为空down三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down邻点存在
			down_left_neighbor = a.Read_data(row + 1, col - 1);
			if (down_left_neighbor == 0)
			{
				//down_left邻点为空
				if ((a.Read_data(row + 2, col - 2) == color) && (a.Read_data(row + 3, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//down2down3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col - 2) == color) && (a.Read_data(row - 1, col + 1) == color))
				{
					a.account_data[row][col] = color;
					//down2up1为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (down_left_neighbor == 1)
			{
				//down_left邻点为黑棋
				if ((a.Read_data(row + 2, col - 2) == 0) && (a.Read_data(row + 3, col - 3) == color))
				{
					a.account_data[row][col] = color;
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//边缘区域，只有死三和非三
			if (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == color && a.Read_data(row + 1, col - 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == color && a.Read_data(row - 1, col + 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}

		//死三三种特殊情况
		if ((a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == color && a.Read_data(row - 3, col + 3) == 0 && a.Read_data(row - 4, col + 4) == color) || (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == 0 && a.Read_data(row - 3, col + 3) == color && a.Read_data(row - 4, col + 4) == color) || (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == 0 && a.Read_data(row - 3, col + 3) == color && a.Read_data(row - 4, col + 4) == color && a.Read_data(row - 5, col + 5) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == color && a.Read_data(row + 3, col - 3) == 0 && a.Read_data(row + 4, col - 4) == color) || (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == 0 && a.Read_data(row + 3, col - 3) == color && a.Read_data(row + 4, col - 4) == color) || (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == 0 && a.Read_data(row + 3, col - 3) == color && a.Read_data(row + 4, col - 4) == color && a.Read_data(row + 5, col - 5) == op_color))
		{
			result = 2;
		}

		return result;
	}


	if (flag == 'f')
	{
		//右斜,反斜
		//向左上检测
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (col + 1) < 16 && (row - i - 1) > -1 && (col - i - 1) > 0)
				{
					if (Alive_4(a, row + 1, col + 1, flag,color) == 1 || Alive_4(a, row - i - 1, col - i - 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col + 1, flag,color) == 0 && Alive_4(a, row - i - 1, col - i - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 15 && Alive_4(a, row - i - 1, col - i - 1, flag,color) == 0) || ((row - i) == 0 && (col - i) == 1 && Alive_4(a, row + 1, col + 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;//向左上延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右下检测
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (col - 1) > 0 && (row + i + 1) < 15 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row - 1, col - 1, flag,color) == 1 || Alive_4(a, row + i + 1, col + i + 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col - 1, flag,color) == 0 && Alive_4(a, row + i + 1, col + i + 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 1 && Alive_4(a, row + i + 1, col + i + 1, flag,color) == 0) || ((row + i) == 14 && (col + i) == 15 && Alive_4(a, row - 1, col - 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//跳三左上
		int up_left_neighbor = -1;
		//跳三右下
		int down_right_neighbor = -1;

		if (row - 3 > -1)
		{
			//left上邻点存在
			up_left_neighbor = a.Read_data(row - 1, col - 1);
			if (up_left_neighbor == 0)
			{
				//left上邻点为空
				if ((a.Read_data(row - 2, col - 2) == color) && (a.Read_data(row - 3, col - 3) == color))
				{
					a.account_data[row][col] = color;//
													 //up2up3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col - 2) == color) && (a.Read_data(row + 1, col + 1) == color))
				{
					a.account_data[row][col] = color;//
													 //up2down1为黑棋
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
			else if (up_left_neighbor == 1)
			{
				//up_left邻点为黑棋
				if ((a.Read_data(row - 2, col - 2) == 0) && (a.Read_data(row - 3, col - 3) == color))
				{
					a.account_data[row][col] = color;//
													 //up2为空down三为黑棋，满足三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down邻点存在
			down_right_neighbor = a.Read_data(row + 1, col + 1);
			if (down_right_neighbor == 0)
			{
				//down_right邻点为空
				if ((a.Read_data(row + 2, col + 2) == color) && (a.Read_data(row + 3, col + 3) == color))
				{
					a.account_data[row][col] = color;//
													 //down2down3为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col + 2) == color) && (a.Read_data(row - 1, col - 1) == color))
				{
					a.account_data[row][col] = color;//
													 //down2up1为黑棋，满足跳三的三连子
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
			else if (down_right_neighbor == 1)
			{
				//down_right邻点为黑棋
				if ((a.Read_data(row + 2, col + 2) == 0) && (a.Read_data(row + 3, col + 3) == color))
				{
					a.account_data[row][col] = color;//
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//活四必须填补空格
						result = 1;//活三
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//边缘区域，只有死三和非三
			if (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == color && a.Read_data(row + 1, col + 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == color && a.Read_data(row - 1, col - 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//死三
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}

		//死三三种特殊情况
		if ((a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == color && a.Read_data(row - 3, col - 3) == 0 && a.Read_data(row - 4, col - 4) == color) || (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == 0 && a.Read_data(row - 3, col - 3) == color && a.Read_data(row - 4, col - 4) == color) || (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == 0 && a.Read_data(row - 3, col - 3) == color && a.Read_data(row - 4, col - 4) == color && a.Read_data(row - 5, col - 5) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == color && a.Read_data(row + 3, col + 3) == 0 && a.Read_data(row + 4, col + 4) == color) || (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == 0 && a.Read_data(row + 3, col + 3) == color && a.Read_data(row + 4, col + 4) == color) || (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == 0 && a.Read_data(row + 3, col + 3) == color && a.Read_data(row + 4, col + 4) == color && a.Read_data(row + 5, col + 5) == op_color))
		{
			result = 2;
		}

		return result;
	}

	//补充死三的剩余两种情况
	
	return 0;
}

int Judge::Alive_4(Array_data a, int row, int col,char flag,int color)
{
	//返回0是非四,返回1是活四，2是死四
	int result = 0;
	int i = 1;
	int count = 1;//执黑连子长度

	int op_color = -1;//非当前执子颜色
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	if(flag == 'h')
	{
		//横
		//向左检测
		while ((col - i) > 0 && a.Read_data(row, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((col - i - 1) > 0 && (col + 1) < 16)
				{
					//存在四连子情况下判断活子情况
					if (a.Read_data(row, col - i - 1) == 0 && a.Read_data(row, col + 1) == 0)
					{
						//活四
						result = 1;
					}
					else if (a.Read_data(row, col - i - 1) == op_color && a.Read_data(row, col + 1) == op_color)
					{
						//非四
						result = 0;
					}
					else
					{
						//死四
						result = 2;
					}
				}
				else
				{
					//四连子的任一侧不存在空格，处于棋盘边缘
					if ((col == 15 && a.Read_data(row, col - i - 1) == op_color) || ((col - i) == 1 && a.Read_data(row, col + 1) == op_color))
					{
						//当前点所在是最后一列，四子最左边一子的左边为白棋
						//当前点四子的最左边一子在第一列，当前子的右边为白棋
						//非四
						result = 0;
					}
					else
					{
						//死四
						result = 2;
					}
					
				}
				break;
			}
			i += 1;//向左延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右检测
		while ((col + i) < 16 && a.Read_data(row, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((col - 1) > 0 && (col + i + 1) < 16)
				{
					if (a.Read_data(row, col + i + 1) == 0 && a.Read_data(row, col - 1) == 0)
					{
						result = 1;//活四
					}
					else if (a.Read_data(row, col + i + 1) == op_color && a.Read_data(row, col - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((col == 1 && a.Read_data(row, col + i + 1) == op_color) || ((col + i) == 15 && a.Read_data(row, col - 1) == op_color))
					{
						//当前点在第一列，四子的最右边一子的右边为白棋
						//当前点的四子最右边一子在最后一列，当前子的左边一子为白棋
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				
				break;
			}
			i += 1;
		}
		
		return result;

	}
	if(flag == 's')
	{
		//竖
		//向上检测
		while ((row - i) > -1 && a.Read_data(row - i, col) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (row - i - 1) > -1)
				{
					if (a.Read_data(row + 1, col) == 0 && a.Read_data(row - i - 1, col) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col) == op_color && a.Read_data(row - i - 1, col) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && a.Read_data(row - i - 1, col) == op_color) || ((row - i) == 0 && a.Read_data(row + 1, col) == op_color))
					{
						//当前子在最后一行，四子的最上边一子的上一个子为白棋
						//当前子的四子的最上面一子在第一行，当前子的下面一个子为白棋
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;//向上延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向下检测
		while ((row + i) < 15 && a.Read_data(row + i, col) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (row + i + 1) < 15)
				{
					if (a.Read_data(row - 1, col) == 0 && a.Read_data(row + i + 1, col) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col) == op_color && a.Read_data(row + i + 1, col) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && a.Read_data(row + i + 1, col) == op_color) || ((row + i) == 14 && a.Read_data(row - 1, col) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				break;
			}
			i += 1;
		}
		
		return result;
	}
	if(flag == 'z')
	{
		//左斜
		//向左下检测
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (col + 1) < 16 && (row + i + 1) < 15 && (col - i - 1) > 0)
				{
					if (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row + i + 1, col - i - 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col + 1) == op_color && a.Read_data(row + i + 1, col - i - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 15 && a.Read_data(row + i + 1, col - i - 1) == op_color) || ((row + i) == 14 && (col - i) == 1 && a.Read_data(row - 1, col + 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				break;
			}
			i += 1;//向左下延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右上检测
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (col - 1) > 0 && (row - i - 1) > -1 && (col + i + 1) < 16)
				{
					if (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row - i - 1, col + i + 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col - 1) == op_color && a.Read_data(row - i - 1, col + i + 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 1 && a.Read_data(row - i - 1, col + i + 1) == op_color) || ((row - i) == 0 && (col + i) == 15 && a.Read_data(row + 1, col - 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;
		}
		
		return result;
	}
	if(flag == 'f')
	{
		//右斜,反斜
		//向左上检测
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (col + 1) < 16 && (row - i - 1) > -1 && (col - i - 1) > 0)
				{
					if (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row - i - 1, col - i - 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col + 1) == op_color && a.Read_data(row - i - 1, col - i - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 15 && a.Read_data(row - i - 1, col - i - 1) == op_color) || ((row - i) == 0 && (col - i) == 1 && a.Read_data(row + 1, col + 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;//向左上延申
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//向右下检测
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (col - 1) > 0 && (row + i + 1) < 15 && (col + i + 1) < 16)
				{
					if (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row + i + 1, col + i + 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col - 1) == op_color && a.Read_data(row + i + 1, col + i + 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 1 && a.Read_data(row + i + 1, col + i + 1) == op_color) || ((row + i) == 14 && (col + i) == 15 && a.Read_data(row - 1, col - 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;
		}
		
		return result;
	}

	//return result;
	return 0;
}

int Judge::Alive_2(Array_data a,int row, int col, char flag, int color)
{
	//返回0是非二,返回1是活二，2是死二
	int result = 0;
	int i = 1;
	int count = 1;//连子长度

	int op_color = -1;//非当前执子颜色
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	if (flag == 'h')
	{
		//左侧
		while (col - i > 0 && i < 5)
		{
			if (a.account_data[row][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row, col - 1, flag, color) == 1 || Alive_3(a, row, col - 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row][col+1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((col - 3) > 0 && a.account_data[row][col - 3] == 0 && Alive_3(a, row, col - 3, flag, color) == 1) || (Alive_3(a, row, col - 1, flag, color) == 1) || ((col + 1) < 16 && a.account_data[row][col + 1] == 0 && Alive_3(a, row, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((col - 2) > 0 && a.account_data[row][col - 2] == 0 && Alive_3(a, row, col - 2, flag, color) == 1) || ((col - 3) > 0 && a.account_data[row][col - 3] == 0 && Alive_3(a, row, col - 3, flag, color) == 1) || ((col + 1) < 16 && a.account_data[row][col + 1] == 0 && Alive_3(a, row, col + 1, flag, color) == 1) || ((col + 2) < 16 && a.account_data[row][col + 2] == 0 && Alive_3(a, row, col + 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//右侧
		i = 1;
		while (col + i < 16 && i < 5)
		{
			if (a.account_data[row][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row, col + 1, flag, color) == 1 || Alive_3(a, row, col + 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((col + 3) < 16 && a.account_data[row][col + 3] == 0 && Alive_3(a, row, col + 3, flag, color) == 1) || (Alive_3(a, row, col + 1, flag, color) == 1) || ((col - 1) > 0 && a.account_data[row][col - 1] == 0 && Alive_3(a, row, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((col + 2) < 16 && a.account_data[row][col + 2] == 0 && Alive_3(a, row, col + 2, flag, color) == 1) || ((col + 3) < 16 && a.account_data[row][col + 3] == 0 && Alive_3(a, row, col + 3, flag, color) == 1) || ((col - 1) > 0 && a.account_data[row][col - 1] == 0 && Alive_3(a, row, col - 1, flag, color) == 1) || ((col - 2) > 0 && a.account_data[row][col - 2] == 0 && Alive_3(a, row, col - 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 's')
	{
		//up侧
		while (row - i > -1 && i < 4)
		{
			if (a.account_data[row - i][col] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col, flag, color) == 1 || Alive_3(a, row-2, col, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row+1][col] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col] == 0 && Alive_3(a, row - 3, col, flag, color) == 1) || (Alive_3(a, row - 1, col, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col] == 0 && Alive_3(a, row + 1, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col] == 0 && Alive_3(a, row - 2, col, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col] == 0 && Alive_3(a, row - 3, col, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col] == 0 && Alive_3(a, row + 1, col, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col] == 0 && Alive_3(a, row + 2, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//down侧
		i = 1;
		while (col + i < 15 && i < 4)
		{
			if (a.account_data[row + i][col] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col, flag, color) == 1 || Alive_3(a, row + 2, col, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col] == 0 && Alive_3(a, row + 3, col, flag, color) == 1) || (Alive_3(a, row + 1, col, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col] == 0 && Alive_3(a, row - 1, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col] == 0 && Alive_3(a, row + 2, col, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col] == 0 && Alive_3(a, row + 3, col, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col] == 0 && Alive_3(a, row - 1, col, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col] == 0 && Alive_3(a, row - 2, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 'z')
	{
		//左down侧
		while (col - i > 0 && i < 4)
		{
			if (a.account_data[row + i][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col - 1, flag, color) == 1 || Alive_3(a, row + 2, col - 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col - 3] == 0 && Alive_3(a, row + 3, col - 3, flag, color) == 1) || (Alive_3(a, row + 1, col - 1, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col +1] == 0 && Alive_3(a, row - 1, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col - 2] == 0 && Alive_3(a, row + 2, col - 2, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col -3] == 0 && Alive_3(a, row + 3, col - 3, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col + 1] == 0 && Alive_3(a, row - 1, col + 1, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col + 2] == 0 && Alive_3(a, row - 2, col + 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//右up侧
		i = 1;
		while (col + i < 16 && i < 4)
		{
			if (a.account_data[row - i][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col + 1, flag, color) == 1 || Alive_3(a, row - 2, col + 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col + 3] == 0 && Alive_3(a, row - 3, col + 3, flag, color) == 1) || (Alive_3(a, row - 1, col + 1, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col - 1] == 0 && Alive_3(a, row + 1, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col + 2] == 0 && Alive_3(a, row - 2, col + 2, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col + 3] == 0 && Alive_3(a, row - 3, col + 3, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col - 1] == 0 && Alive_3(a, row + 1, col - 1, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col - 2] == 0 && Alive_3(a, row + 2, col - 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 'f')
	{
		//左up侧
		while (col - i > 0 && i < 4)
		{
			if (a.account_data[row - i][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col - 1, flag, color) == 1 || Alive_3(a, row - 2, col - 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col - 3] == 0 && Alive_3(a, row - 3, col - 3, flag, color) == 1) || (Alive_3(a, row - 1, col - 1, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col + 1] == 0 && Alive_3(a, row + 1, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col - 2] == 0 && Alive_3(a, row - 2, col - 2, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col - 3] == 0 && Alive_3(a, row - 3, col - 3, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col + 1] == 0 && Alive_3(a, row + 1, col + 1, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col + 2] == 0 && Alive_3(a, row + 2, col +2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//右down侧
		i = 1;
		while (col + i < 16 && i < 4)
		{
			if (a.account_data[row + i][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//存在二连子
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col + 1, flag, color) == 1 || Alive_3(a, row + 2, col + 2, flag, color) == 1)
					{
						result = 1;//活二
					}
					else if (a.account_data[row - 1][col-1] == op_color)
					{
						result = 2;//死二
					}
					else
					{
						result = 0;//非二
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col + 3] == 0 && Alive_3(a, row + 3, col + 3, flag, color) == 1) || (Alive_3(a, row + 1, col + 1, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col - 1] == 0 && Alive_3(a, row - 1, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col + 2] == 0 && Alive_3(a, row + 2, col + 2, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col + 3] == 0 && Alive_3(a, row + 3, col + 3, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col - 1] == 0 && Alive_3(a, row - 1, col - 1, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col-2] == 0 && Alive_3(a, row - 2, col-2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}

	return 0;
}

/*
int Judge::Dead_4(Array_data a, int row, int col,char flag)
{
	//返回0是死四
	int result = 0;
	int count = 1;//连子长度



	return result;
}
*/

int Judge::Double_4_judge(Array_data a, int row, int col,int color)
{
	//黑方满足出现两个或以上活四或死四即可
	int result = 0;//触犯禁手为-1
	int count = 0;//可形成五子的四子数目

	if (Alive_4(a, row, col, 'h',color) == 1 || Alive_4(a, row, col, 'h',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 's',color) == 1 || Alive_4(a, row, col, 's',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 'z',color) == 1 || Alive_4(a, row, col, 'z',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 'f',color) == 1 || Alive_4(a, row, col, 'f',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}

	return result;
}

int Judge::Double_3_judge(Array_data a, int row, int col,int color)
{
	//双活三，除非遇到解禁，否则即为禁手
	int result = 0;//-1为触犯禁手
	int count = 0;//活三计数

	if (Alive_3(a, row, col, 'h',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 's',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 'z',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 'f',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}

	return result;
}

int Judge::Double_2_judge(Array_data a, int row, int col, int color)
{
	int result = 0;//1为双活二
	int count = 0;

	if (Alive_2(a, row, col, 'h', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 's', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 'z', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 'f', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}

	return 0;
}

int Judge::Ban_lift_ban(Array_data a, int row, int col)
{
	//以禁解禁
	//1为解禁，0为不解禁
	int ban_lift = 0;//1为解禁



	return ban_lift;
}

int Judge::Judgement(Array_data a, int row, int col,int color)
{
	//判断胜负
	int result = 0;//0为未分胜负，1为当前落子方胜,2为平局
	int j = 0;//循环四个方向

	int color_piece = 0;//根据黑白子决定连子颜色,进而匹配account中同色棋子

	if (color == 0)
	{
		//执黑
		color_piece = 1;
	}
	else
	{
		//执白
		color_piece = 2;
	}

	while (j < 4)
	{
		int i = 1;
		int count = 1;

		if (j == 0)
		{
			//横
			//向左检测
			while ((col - i) > 0 && a.Read_data(row, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//向左延申
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//向右检测
			while ((col + i) < 16 && a.Read_data(row, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else if (j == 1)
		{
			//竖
			//向上检测
			while ((row - i) > -1 && a.Read_data(row - i, col) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//向上延申
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//向下检测
			while ((row + i) < 15 && a.Read_data(row + i, col) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else if (j == 2)
		{
			//左斜
			//向左下检测
			while ((row + i) < 15 && a.Read_data(row + i, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//向左下延申
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//向右上检测
			while ((row - i) > -1 && a.Read_data(row - i, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else
		{
			//右斜
			//向左上检测
			while ((row - i) > -1 && a.Read_data(row - i, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//向左下延申
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//向右下检测
			while ((row + i) < 15 && a.Read_data(row + i, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}

		j += 1;
	}

	//平局判定，在111回合后才会判断
	//遍历棋局存在的空格数，若为0则和棋
	int m = 0;
	int n = 0;
	int blank_count = 0;
	for (m = 0; m < 15; m++)
	{
		for (n = 1; n < 16; n++)
		{
			if (a.Read_data(m, n) == 0)
			{
				blank_count += 1;
			}
			if (blank_count != 0)
			{
				break;
			}
		}
		if (blank_count != 0)
		{
			break;
		}
	}	
	if (blank_count == 0)
	{
		result = 2;
	}

	return result;
}