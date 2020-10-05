#pragma once
#define MAX 500
#define Azure 0xA4D3EE
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
enum way //将上下左右键对应英文
{
	right = 72,
	left = 75,
	down = 77,
	up = 80
};
class snake
{
public:
	snake();
	~snake(){}
	void inisnake();//绘制蛇
	void snakemove();//改变蛇移动的方向
	void moveway();//移动蛇
	bool die() { if (flag) return false; else return true; }//返回蛇是否死的信息
	void seteatgrade(int x) { eatgrade = x; }//更新分数
	void SetNum(int x) { num = x; }//更新蛇的节数
	int GetNum() const { return num; }//获取蛇的节数
	int GetEatgrade() const { return eatgrade; }//获取蛇当前所获的分数
	int GetXy_x(int i) const { return xy_x[i]; }//获取第i节蛇的横坐标
	int GetXy_y(int i) const { return xy_y[i]; }//获取第i节蛇的纵坐标
	friend void snakedie();//将判断蛇是否死亡的全局函数作为友元
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
	int num;//节数
	int xy_x[MAX];//每节蛇的横坐标
	int xy_y[MAX];//每节蛇的纵坐标
	char way;//当前前进的方向
	int eatgrade;//当前的得分
	bool flag;//如果为true，说明蛇没有死，否则蛇就死了
	int lastx;
	int lasty;
};

