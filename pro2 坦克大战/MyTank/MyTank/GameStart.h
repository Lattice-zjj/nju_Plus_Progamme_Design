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
	pair<bool,bool> over;//�ó���Ϸ�Ƿ�����Լ�������Ӯ
	bool running;//�Ƿ��������
	PainterHelper p;
	MyTank* userTank;//�û�̹��
	vector<Bullet> bullet;//����ӵ�
	vector<EnemyTank*> root;//��ŵ�̹��ָ��
	int bul_num;//�ӵ�������
	int num_of_enemy;//��ܵĵ�������
	Tools food;//����
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

