#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include"PainterHelper.h"
#include"Normal.h"
#include "Tank.h"
#include "MyTank.h"
#include "EnemyTank.h"
using namespace std;
class Tools
{
public:
	Tools() { 
		alive = false;
		paint.push_back("Ì¹");
		paint.push_back("¡ï");
		paint.push_back("Ê±");
		paint.push_back("Ìú");
		paint.push_back("Õ¨");
	}
	~Tools() {}
	void SetXy() {
		srand(time(NULL));
		alive = true;
		x = rand() % 36; y = rand() % 36;
		while (!(x > 1 && y > 1 && (!(x >= 16 && x <= 21 && y >= 33 && y <= 36)))) { x = rand() % 37; y = rand() % 37; }
		Print();
	}
	void SetType(int x) {
		type = x;
	}
	virtual void Print() {
		p.printfxywithcolor(x, y, 6, paint[type]);
	}
	void Reset() {
		p.MapDraw(Map[level][y][x], x, y);
	}
	void run(Tank* tank, vector<EnemyTank*> enemy, MyTank* user);
	void setBorder(int x) {
		for (int i = 33; i <= 36; i++) {
			for (int j = 16; j <= 21; j++){
				if (!(i == 36 && j == 18 || i == 36 && j == 19 || i == 35 && j == 18 || i == 35 && j == 19)) {
					Map[level][i][j] = x;
					p.MapDraw(x, j, i);
				}
			}
		}
	}
	friend class GameStart;
protected:
	bool alive;
	int x, y;
	vector<string> paint;
	int type;
	PainterHelper p;
};