#define _CRT_SECURE_NO_WARNINGS
#include "food.h"
#include "snake.h"
#include "block.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <Mmsystem.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"WINMM.LIB")
using namespace std;
food Food;
food SpeFood;
snake Snake;
block Block[1000];
int num = 0;
int f = 0;
int step = 0;
int numscore = 0;
int numblock = 10;
int speed = 10;
int scorexi[20];
int hour_begin, sec_begin, min_begin;
bool openmusic = true;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//ȫ�־��
void again();//��ȡ�������Ҳ������ĵ�һ���ַ�
void foodxy();//����ʳ��
void eatfood();//�ж��Ƿ�Ե�ʳ��
void update1();//����ǰ���ݴ������飬����д��txt��
void up1();//��txt�е����ݶ�ȡ����ǰ��������
void start();//��ʼ����
void snakedie();//�ж����Ƿ������ĺ���
void blockxy(block& b);//�����ϰ���
void paint();
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
int main()
{
	SetConsoleTitleA("̰������Ϸ V 1.0 made by zhoujunjie");
	while (1) {
		up1();
		COORD dSiz = { 80, 40 };
		SetConsoleScreenBufferSize(hOut, dSiz);//���ô��ڻ�������С
		CONSOLE_CURSOR_INFO _guan_biao = { 1, FALSE };//���ù���С�����ع��
		SetConsoleCursorInfo(hOut, &_guan_biao);
		start();
		system("cls");
		time_t tt = time(NULL);
		tm t;//ʱ��ṹ��
		localtime_s(&t, &tt);//��ȡʱ��
		hour_begin = t.tm_hour;
		min_begin = t.tm_min;
		sec_begin = t.tm_sec;
		srand((unsigned int)time(NULL));//��Ϊ�������������

		SpeFood.SetKind(1);//��������ʳ���kindΪ1

		cout << "��������Ϸ����Ҫ���ϰ���������������0�������10����";
		cin >> numblock; cout << endl;
		cout << "��������Ϸ����Ҫ��̰�����ٶȣ�������Ϊ0�����Ϊ10��";
		cin >> speed; cout << endl;
		if (openmusic) {
			mciSendStringW(L"open love.mp3", 0, 0, 0);
			mciSendStringW(L"play love.mp3", 0, 0, 0);
		}
		system("cls");
		for (int i = 0; i <= 500 / 20 - 1; i++) {
			gotoxy(640 / 20, i); color(100); printf("��");
		}
		for (int i = 0; i <= 640 / 20; i++) {
			gotoxy(i, 500 / 20); color(100); printf("��");
		}

		while (1)//���ϵ�ѭ��
		{
			SetConsoleScreenBufferSize(hOut, dSiz);//���ô��ڻ�������С
			CONSOLE_CURSOR_INFO _guan_biao = { 1, FALSE };//���ù���С�����ع��
			SetConsoleCursorInfo(hOut, &_guan_biao);
			paint();
			if (Food.GetFoodFlag() == 0)
			{
				foodxy();//���û��ʳ���ˣ��Ͳ���һ���µ�ʳ��
			}
			for (int i = 0; i < numblock; i++) {//�����ϰ���
				if (Block[i].GetBlockFlag() == 0)
				{
					blockxy(Block[i]);
				}
			}
			if (Food.GetFoodFlag()) Food.inifood();
			if (SpeFood.GetFoodFlag()) SpeFood.inifood();//�滭ʳ��
			for (int i = 0; i < numblock; i++) {
				if (Block[i].GetBlockFlag()) Block[i].iniblock();
			}//�滭�ϰ���
			Snake.inisnake();//�滭��

			snakedie();//�ж����Ƿ�����
			eatfood();//�ж����Ƿ��ܳԵ�ʳ��
			Snake.moveway();//�ƶ���
			Sleep(100 - speed * 5);//�����ٶȲ������ı�sleep��ʱ�����ﵽ�ı����˶�������Ŀ��

			while (_kbhit()) //�����������ҵİ���
			{
				again();
				Snake.snakemove();
			}

			if (num == 5) { //�ﵽ5����ͨʳ��Ͳ�������ʳ��
				num = 0;
				SpeFood.SetFdx(rand() % 32 * 20);
				SpeFood.SetFdy(rand() % 24 * 20);
				for (int i = 0; i < Snake.GetNum(); i++)
				{
					if (SpeFood.GetFdx() == Snake.GetXy_x(i) && SpeFood.GetFdy() == Snake.GetXy_y(i))
					{
						SpeFood.SetFdx(rand() % 32 * 20);
						SpeFood.SetFdy(rand() % 24 * 20);
					}
				}
				SpeFood.SetFoodFlag(1);
				f = 1;
			}
			if (f == 1) {
				step++;
				if (step == 80) { //�����ﵽ80���ͻ���ʧ
					SpeFood.SetFoodFlag(0); f = 0; step = 0;
				}
			}

			if (Snake.die()) { //���������
				mciSendStringW(L"close love.mp3", 0, 0, 0);
				numscore++; scorexi[numscore] = Snake.GetEatgrade();
				update1();//���³ɼ�
				break;//�˳�
			}
		}
		break;
	}
	while (1);
	return 0;
}

void foodxy()
{
	//������ 0 10 20 30 n*10
	//ʳ�� ��� rand() % 650 ��ô����0 1 2 3 4 �߽��Բ���ʳ�� �����غϵ�

	Food.SetFdx(rand() % 32 * 20);
	Food.SetFdy(rand() % 24 * 20);
	Food.SetFoodFlag(1);

	for (int i = 0; i < Snake.GetNum(); i++)
	{
		if (Food.GetFdx() == Snake.GetXy_x(i) && Food.GetFdy() == Snake.GetXy_y(i))
		{
			Food.SetFdx(rand() % 32 * 20);
			Food.SetFdy(rand() % 24 * 20);
		}
	}
}

void blockxy(block &b)
{

	b.SetBdx(rand() % 32 * 20);
	b.SetBdy(rand() % 24 * 20);
	b.SetblockFlag(1);

	for (int i = 0; i < Snake.GetNum(); i++)
	{
		if (b.GetBdx() == Snake.GetXy_x(i) && b.GetBdy() == Snake.GetXy_y(i))
		{
			b.SetBdx(rand() % 32 * 20);
			b.SetBdy(rand() % 24 * 20);
		}
	}
}

void eatfood()
{

	if (Snake.GetXy_x(0) == Food.GetFdx() && Snake.GetXy_y(0) == Food.GetFdy())
	{
		Snake.SetNum(Snake.GetNum() + 1);
		Snake.seteatgrade(Snake.GetEatgrade() + 10);
		Food.SetFoodFlag(0);
		num++;
	}

	if (Snake.GetXy_x(0) == SpeFood.GetFdx() && Snake.GetXy_y(0) == SpeFood.GetFdy())
	{
		Snake.SetNum(Snake.GetNum() + 2);
		Snake.seteatgrade(Snake.GetEatgrade() + 20);
		SpeFood.SetFoodFlag(0);
	}

}
void again()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}

void update1() {
	for (int i = 1; i <= numscore - 1; i++)
		for (int j = i + 1; j <= numscore; j++)
			if (scorexi[i] < scorexi[j]) {
				int t = scorexi[i]; scorexi[i] = scorexi[j]; scorexi[j] = t;
			}
	ofstream outfile1("score.txt");
	outfile1 << "����" << endl;
	for (int i = 1; i <= numscore; i++) {
		outfile1 << scorexi[i] << endl;
	}
	int p = 0;
	if (numscore > 10) p = 10; else p = numscore;
	int hang = 40;
	gotoxy(1000 / 20, hang / 20); color(15); printf("���а�");
	hang += 32;
	for (int i = 1; i <= p; i++) {
		int t = scorexi[i];
		char st[100]; int l = 0;
		string s1="";
		while (t) {
			s1 = char(t % 10 + 48) + s1;
			t = t / 10;
		}
		if (s1 == "") s1 = "0";
		if (i == 10) {
			st[l++] = '1'; st[l++] = '0';
		}
		else st[l++] = char(i+48); 
		st[l++] = '.';
		int ll = s1.length();
		for (int j = 0; j < ll; j++) {
			st[l++] = s1[j];
		}
		st[l] = '\0';
		gotoxy(1000 / 20, hang / 20); color(15); printf(st);
		hang += 20;
	}
	
	if (numscore > 10) {
		for (int i = 11; i <= numscore; i++) scorexi[i] = 0;
		numscore = 10;
	}
	outfile1.close();
}

void up1() {
	ifstream myfile("score.txt");

	if (myfile) {

		int i = 1;
		int t = 0;
		char buffer[256];
		while (!myfile.fail()) {

			myfile.getline(buffer, 256);
			if (t == 0) {
				t = 1; continue;
			}
			istringstream iss(buffer);
			int x;
			iss >> x; scorexi[i] = x;
			i++;
			if (i == 20) break;
		}

		i--;
		numscore = i - 1;
		
	}
}

void start() {
	/*��ʼ������ѡ��*/
	gotoxy(6, 6);
	color(4);
	printf("̰   ��   ��   ��   Ϸ");
	gotoxy(6, 8);
	printf("  	  V 1.0");
	gotoxy(6, 10);
	printf("Made    by   Zhoujunjie");
	color(15);
	gotoxy(6, 21);
	printf("��ѡ��");
	gotoxy(6, 22);
	printf("(���¼�ѡ��,�س�ȷ��)");
	gotoxy(6, 23);
	printf("(+ ��ѡ������ - ��ѡ�������)");
	gotoxy(27, 22);
	color(25);
	printf("��ʼ��Ϸ");
	gotoxy(27, 24);
	color(15);
	printf("�˳���Ϸ");
	gotoxy(27, 26);
	color(100);
	printf("��������");
	color(15);
	/*���·����ѡ��ģ��*/
	int ch;//��¼����ֵ
	int key = 1;//��¼ѡ�����ʼѡ���һ��
	bool flag = false;//��¼�Ƿ����Enter����ǣ���ʼ��Ϊ��
	while ((ch = _getch()))
	{
		switch (ch)//��������
		{
		case '+':
			if (!openmusic) {
				openmusic = true;
				gotoxy(27, 26);
				color(100);
				printf("��������");
			}
			break;
		case '-':
			if (openmusic) {
				openmusic = false;
				gotoxy(27, 26);
				color(100);
				printf("��������");
			}
			break;
		case 72://UP�Ϸ����
			if (key > 1)//����ʱѡ����Ϊ��һ��ʱ��UP�Ϸ������Ч
			{
				gotoxy(27, 22);//����ѡ�������ñ���ɫ
				color(25);
				printf("��ʼ��Ϸ");

				gotoxy(27, 24);//����ѡ����ȡ���ұ���ɫ
				color(15);
				printf("�˳���Ϸ");

				--key;
			}
			break;

		case 80://DOWN�·����
			if (key < 2)
			{
				gotoxy(27, 22);
				color(15);
				printf("��ʼ��Ϸ");

				gotoxy(27, 24);
				color(25);
				printf("�˳���Ϸ");

				++key;
			}
			break;

		case 13://Enter�س���
			flag = true;
			break;
		default://��Ч����
			break;
		}
		if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��
	}
	if (key == 1) { color(15); system("cls"); return; }
	else {
		color(15); exit(-1);
	}
}

//�ж����Ƿ�����
void snakedie()
{
	{ //����
		char grade[100] = { 0 };
		sprintf(grade, "%d", Snake.eatgrade);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(680 / 20, 20 / 20); color(15); printf("������");
		gotoxy(720 / 20, 20 / 20); color(15);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf(grade);
		char ka[100] = { 0 };
		sprintf(ka, "%d", speed*2+numblock+1);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(0 / 20, 560 / 20); color(15); printf("�ؿ���");
		gotoxy(40 / 20, 560 / 20); color(15);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY); 
		printf(ka);
	}

	if (Snake.xy_x[0] > 630 || Snake.xy_x[0] < 0 || Snake.xy_y[0] > 480 || Snake.xy_y[0] < 0)
	{
		char grade[100] = { 0 };
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(200 / 20, 200 / 20); color(15); printf("��ķ�����");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		sprintf(grade, "%d", Snake.eatgrade);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(370 / 20, 200 / 20); color(15); printf(grade);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		gotoxy(200 / 20, 590 / 20); color(15); printf("ײǽ�ˣ���Ϸ������");
		Snake.flag = false;
	}

	for (int i = 1; i < Snake.num; i++)
	{
		if (Snake.xy_x[0] == Snake.xy_x[i] && Snake.xy_y[0] == Snake.xy_y[i])
		{
			gotoxy(130 / 20, 590 / 20); color(15);
			SetConsoleTextAttribute(hOut, 0xB);
			printf("��ҧ�����Լ�����Ϸ������");
			Snake.flag = false;
		}
	}

	for (int i = 0; i < numblock; i++) {
		if (Snake.GetXy_x(0) == Block[i].GetBdx() && Snake.GetXy_y(0) == Block[i].GetBdy())
		{
			char grade[100] = { 0 };
			SetConsoleTextAttribute(hOut, 0xB);
			gotoxy(200 / 20, 200 / 20); color(15); printf("��ķ�����");
			sprintf(grade, "%d", Snake.eatgrade);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			gotoxy(370 / 20, 200 / 20); color(15); printf(grade);
			SetConsoleTextAttribute(hOut, 0xB);
			gotoxy(200 / 20, 590 / 20); color(15);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("ײ���ϰ����ˣ���Ϸ������");
			Snake.flag = false;
		}
	}
}
void paint() {
	time_t tt = time(NULL);
	tm t;//ʱ��ṹ��
	localtime_s(&t, &tt);//��ȡʱ��
	int hour, sec, min;
	hour = t.tm_hour;
	min = t.tm_min;
	sec = t.tm_sec;
	int second = hour * 3600 + min * 60 + sec - (hour_begin * 3600 + min_begin * 60 + sec_begin);
	gotoxy(680 / 20, 19); printf("            You already play %d��\n",second);
	gotoxy(680 / 20, 20); printf("            ̰���� V 1.0 made by zhoujunjie\n");
}