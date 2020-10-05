#pragma once
#include "PainterHelper.h"
#include "Normal.h"
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Print();
	void Reset();
	bool Move();
	friend class GameStart;

private:
	PainterHelper p;  //绘图工具
	int x, y;   //坐标
	int place;  //表示当前处于的地方
	int direct;
	bool f;   //为true表示存在 为false表示不存在
	bool type;
	int atk;
	bool Is_First;
	bool If_Through;
};

