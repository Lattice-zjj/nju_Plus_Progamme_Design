#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "PainterHelper.h"
#include "Normal.h"
class Tank
{
public:
	Tank();
	~Tank();
	void Move(int turn);
	void Print();
	void Reset();
	bool Check();
	bool ifmy() {
		if (type == 0) return true; else return false;
	}
	friend class GameStart;
	friend class Tools;
protected:
	int x, y;//坐标
	int direct;//方向
	int atk;//攻击力
	int blood;//血量
	int color;//颜色
	int type;//类型 是我方 还是敌方
	int model;//型号
	int speed;//速度
	int ShootSpeed;//射速
	int grade;//等级
	bool overen;//是否把对方全部over 
	bool alive;//是否存在
	bool stop;//是否被暂停
	char tank_figure[4][10][10][10];//图像
	PainterHelper p;
};

