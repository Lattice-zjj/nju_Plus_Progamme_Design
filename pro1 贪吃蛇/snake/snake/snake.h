#pragma once
#define MAX 500
#define Azure 0xA4D3EE
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
enum way //���������Ҽ���ӦӢ��
{
	right = 72,
	left = 75,
	down = 77,
	up = 80
};
class snake
{
public:
	snake();
	~snake(){}
	void inisnake();//������
	void snakemove();//�ı����ƶ��ķ���
	void moveway();//�ƶ���
	bool die() { if (flag) return false; else return true; }//�������Ƿ�������Ϣ
	void seteatgrade(int x) { eatgrade = x; }//���·���
	void SetNum(int x) { num = x; }//�����ߵĽ���
	int GetNum() const { return num; }//��ȡ�ߵĽ���
	int GetEatgrade() const { return eatgrade; }//��ȡ�ߵ�ǰ����ķ���
	int GetXy_x(int i) const { return xy_x[i]; }//��ȡ��i���ߵĺ�����
	int GetXy_y(int i) const { return xy_y[i]; }//��ȡ��i���ߵ�������
	friend void snakedie();//���ж����Ƿ�������ȫ�ֺ�����Ϊ��Ԫ
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
	int num;//����
	int xy_x[MAX];//ÿ���ߵĺ�����
	int xy_y[MAX];//ÿ���ߵ�������
	char way;//��ǰǰ���ķ���
	int eatgrade;//��ǰ�ĵ÷�
	bool flag;//���Ϊtrue��˵����û�����������߾�����
	int lastx;
	int lasty;
};

