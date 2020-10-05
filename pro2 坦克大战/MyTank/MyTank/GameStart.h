#pragma once
#include"Normal.h"
#include"PainterHelper.h"
#include "Tools.h"
#include "Bullet.h"
#include "Tank.h"
#include "EnemyTank.h"
#include "MyTank.h"
#include <time.h>
#include <vector>

class GameStart
{
public:
	GameStart();
	~GameStart(){}
	int start(MyTank* user1);
	void PrintSideInfor();
	void DrawMap();
	void GameOver(int f);
	void GameJudge();
	void DoKey();
	void CrashJudge(Bullet& bullet);
	void FoodEaten();
	void BuildBullet(Tank& tank, int x = 2);
	void Init();
	void BulletsCrash();
	void ToolCheck();
private:
	pair<bool,bool> over;//该场游戏是否结束以及是输是赢
	bool running;//是否继续运行
	PainterHelper p;
	MyTank* userTank;//用户坦克
	vector<Bullet> bullet;//存放子弹
	vector<EnemyTank*> root;//存放敌坦克指针
	int bul_num;//子弹的数量
	int num_of_enemy;//打败的敌人数量
	Tools food;//道具
	DWORD clock_enemy[3];
	DWORD clock_enemy_move[3];
	DWORD clock_en_bullet[3];
	DWORD clock_key;
	DWORD clock_my_bullet;
	DWORD clock_bullet;
	DWORD clock_food;
	DWORD clock_display;
	DWORD middle_bullet;
	DWORD clock_stop;
	DWORD clock_return;
	bool display;
	bool Stop;
};

