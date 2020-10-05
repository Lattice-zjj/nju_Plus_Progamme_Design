#pragma once
#include <windows.h>
#include <stdio.h>
class block
{
public:
	block();
	~block(){}
	void iniblock();//绘制障碍物
	void SetblockFlag(int x);//设置障碍物是否存在
	void SetBdx(int x) { fdx = x; }//设置障碍物的横坐标
	void SetBdy(int y) { fdy = y; }//设置障碍物的纵坐标
	int GetBdx() const { return fdx; }//获取障碍物的横坐标
	int GetBdy() const { return fdy; }//获取障碍物的纵坐标
	int GetBlockFlag() const { return flag; }//返回障碍物是否存在
	void gotoxy(int x, int y)
	{
		COORD pos;
		pos.X = 2 * x;
		pos.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	void color(int b)
	{
		HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
		SetConsoleTextAttribute(hConsole, b);
	}

private:
	int flag, fdx, fdy;//flag表示障碍物是否存在 fdx表示障碍物的横坐标 fdy表示障碍物的纵坐标
	int kind;//表示障碍物的种类
};

