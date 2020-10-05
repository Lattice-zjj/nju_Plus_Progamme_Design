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
	int x, y;//����
	int direct;//����
	int atk;//������
	int blood;//Ѫ��
	int color;//��ɫ
	int type;//���� ���ҷ� ���ǵз�
	int model;//�ͺ�
	int speed;//�ٶ�
	int ShootSpeed;//����
	int grade;//�ȼ�
	bool overen;//�Ƿ�ѶԷ�ȫ��over 
	bool alive;//�Ƿ����
	bool stop;//�Ƿ���ͣ
	char tank_figure[4][10][10][10];//ͼ��
	PainterHelper p;
};

