#pragma once
#define MAX 500
#include <windows.h>
#include <stdio.h>
class food
{
public:
	food();
	~food(){}
	void inifood();//����ʳ��
	void SetFoodFlag(int x);//����ʳ���Ƿ����
	void SetFdx(int x) { fdx = x; }//����ʳ��ĺ�����
	void SetFdy(int y) { fdy = y; }//����ʳ���������
	void SetKind(int x) { kind = x; }//����ʳ�������
	int GetFdx() const { return fdx; }//��ȡʳ��ĺ�����
	int GetFdy() const { return fdy; }//��ȡʳ���������
	int GetFoodFlag() const { return flag; }//��ȡʳ���Ƿ���ڵ���Ϣ
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
	int flag, fdx, fdy;//flag��ʾʳ���Ƿ���� fdx��ʾʳ��ĺ����� fdy��ʾʳ���������
	int kind;//��ʾʳ������� 0Ϊ��ͨʳ�� 1Ϊ����ʳ��
	int hour_begin, min_begin, sec_begin;
};

