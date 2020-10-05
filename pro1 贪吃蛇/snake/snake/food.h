#pragma once
#define MAX 500
#include <windows.h>
#include <stdio.h>
class food
{
public:
	food();
	~food(){}
	void inifood();//绘制食物
	void SetFoodFlag(int x);//设置食物是否存在
	void SetFdx(int x) { fdx = x; }//设置食物的横坐标
	void SetFdy(int y) { fdy = y; }//设置食物的纵坐标
	void SetKind(int x) { kind = x; }//设置食物的种类
	int GetFdx() const { return fdx; }//获取食物的横坐标
	int GetFdy() const { return fdy; }//获取食物的纵坐标
	int GetFoodFlag() const { return flag; }//获取食物是否存在的消息
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
	int flag, fdx, fdy;//flag表示食物是否存在 fdx表示食物的横坐标 fdy表示食物的纵坐标
	int kind;//表示食物的种类 0为普通食物 1为特殊食物
	int hour_begin, min_begin, sec_begin;
};

