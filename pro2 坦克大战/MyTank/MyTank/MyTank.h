#pragma once
#include "Tank.h"
class MyTank :
	public Tank
{
public:
	MyTank();
	~MyTank();
	void BuildUser();
	void resetxy();
	friend class GameStart;
	friend class Tools;
private:
	int ming;
	bool twice;
	bool twobullet;
};