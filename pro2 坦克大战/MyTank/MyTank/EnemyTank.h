#pragma once
#include "Tank.h"
#include<time.h>
#include "AStar.h"
class EnemyTank :
	public Tank
{
public:
	EnemyTank();
	~EnemyTank();
	bool AutoMove();
	void RandMove();
	virtual void reset() {}
	friend class GameStart;
protected:
	int* BsetDir;
	int step;
	int num;//每种拥有的数量
	int score;//每种的分数
};
class ZhuangTank :public EnemyTank {
public:
	ZhuangTank() {
		reset();
	}
	void reset() {
		x = 2; y = 2; type = 1; color = 4;
		ShootSpeed = 0;
		score = 1000;
		grade = 1;
		stop = false;
	}
};

class LightTank :public EnemyTank {
public:
	LightTank() {
		reset();
	}
	void reset() {
		x = 13; y = 2; type = 2; color = 5; speed = 120;
		blood = 2000;
		ShootSpeed = 600;
		score = 2000;
		grade = 1;
		stop = false;
	}
};

class HeavyTank :public EnemyTank {
public:
	HeavyTank() {
		reset();
	}
	void reset() {
		x = 33; y = 2; type = 3; color = 6;
		atk = 2; blood = 5000;
		score = 4000;
		ShootSpeed = 0;
		grade = 1;
		stop = false;
	}
};
