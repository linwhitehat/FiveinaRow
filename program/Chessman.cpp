#include "Chessman.h"



Chessman::Chessman()
{
}


Chessman::~Chessman()
{
}

const char* Chessman::chessman_type(int type,int state)
{
	if (type == 0)
	{
		//黑棋
		if (state == 0)
		{
			//当前落子
			return "▲";
		}
		else
		{
			return "●";
		}
	}
	else
	{
		//白棋
		if (state == 0)
		{
			//当前落子
			return "△";
		}
		else
		{
			return "○";
		}
	}
}