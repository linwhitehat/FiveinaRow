#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define ROW 16
#define COL 16

class Array_data
{
public:
	Array_data();
	~Array_data();
	int account_data[ROW][COL] = { 0 };//账本数据，用于判定和读取棋局数据使用,16*16但是只用15*15的数据,第一列和最后一行全0
	int score[ROW][COL] = { 0 };//计分数组

	void Write_data(int i,int j,int flag,int color,int state);//i,j表示坐标，flag为写数据情况,color为黑白判断,state为是否当前落子
	void TransferType(char *dst,const char *src);//将const char类型转为char进行存储
	void Show_data();//显示棋局内容
	int Read_data(int row,int col);//获取私有成员数据

	int read_row();
	char read_col();
	void write_row_col(int m_row, char m_col);

private:
	char ***data = new char**[ROW];	

	int machine_row = 0;//机器选择棋子位置横坐标
	char machine_col = ' ';//机器选择棋子位置纵坐标
	
	//1//char *last_row = new char[COL];
	//char *data[ROW][COL] = {};//数组初始化
};

