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
	PainterHelper p;  //��ͼ����
	int x, y;   //����
	int place;  //��ʾ��ǰ���ڵĵط�
	int direct;
	bool f;   //Ϊtrue��ʾ���� Ϊfalse��ʾ������
	bool type;
	int atk;
	bool Is_First;
	bool If_Through;
};

