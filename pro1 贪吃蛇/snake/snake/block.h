#pragma once
#include <windows.h>
#include <stdio.h>
class block
{
public:
	block();
	~block(){}
	void iniblock();//�����ϰ���
	void SetblockFlag(int x);//�����ϰ����Ƿ����
	void SetBdx(int x) { fdx = x; }//�����ϰ���ĺ�����
	void SetBdy(int y) { fdy = y; }//�����ϰ����������
	int GetBdx() const { return fdx; }//��ȡ�ϰ���ĺ�����
	int GetBdy() const { return fdy; }//��ȡ�ϰ����������
	int GetBlockFlag() const { return flag; }//�����ϰ����Ƿ����
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
	int flag, fdx, fdy;//flag��ʾ�ϰ����Ƿ���� fdx��ʾ�ϰ���ĺ����� fdy��ʾ�ϰ����������
	int kind;//��ʾ�ϰ��������
};

