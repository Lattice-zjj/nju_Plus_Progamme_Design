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
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//全局句柄
void again();//获取上下左右操作键的第一个字符
void foodxy();//产生食物
void eatfood();//判断是否吃掉食物
void update1();//将当前数据存入数组，重新写入txt中
void up1();//将txt中的数据读取到当前的数组中
void start();//开始界面
void snakedie();//判断蛇是否死亡的函数
void blockxy(block& b);//产生障碍物
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
	SetConsoleTitleA("贪吃蛇游戏 V 1.0 made by zhoujunjie");
	while (1) {
		up1();
		COORD dSiz = { 80, 40 };
		SetConsoleScreenBufferSize(hOut, dSiz);//设置窗口缓冲区大小
		CONSOLE_CURSOR_INFO _guan_biao = { 1, FALSE };//设置光标大小，隐藏光标
		SetConsoleCursorInfo(hOut, &_guan_biao);
		start();
		system("cls");
		time_t tt = time(NULL);
		tm t;//时间结构体
		localtime_s(&t, &tt);//获取时间
		hour_begin = t.tm_hour;
		min_begin = t.tm_min;
		sec_begin = t.tm_sec;
		srand((unsigned int)time(NULL));//作为种子生产随机数

		SpeFood.SetKind(1);//设置特殊食物的kind为1

		cout << "请输入游戏中所要的障碍物数量：（最少0个，最多10个）";
		cin >> numblock; cout << endl;
		cout << "请输入游戏中所要的贪吃蛇速度：（最慢为0，最快为10）";
		cin >> speed; cout << endl;
		if (openmusic) {
			mciSendStringW(L"open love.mp3", 0, 0, 0);
			mciSendStringW(L"play love.mp3", 0, 0, 0);
		}
		system("cls");
		for (int i = 0; i <= 500 / 20 - 1; i++) {
			gotoxy(640 / 20, i); color(100); printf("■");
		}
		for (int i = 0; i <= 640 / 20; i++) {
			gotoxy(i, 500 / 20); color(100); printf("■");
		}

		while (1)//不断的循环
		{
			SetConsoleScreenBufferSize(hOut, dSiz);//设置窗口缓冲区大小
			CONSOLE_CURSOR_INFO _guan_biao = { 1, FALSE };//设置光标大小，隐藏光标
			SetConsoleCursorInfo(hOut, &_guan_biao);
			paint();
			if (Food.GetFoodFlag() == 0)
			{
				foodxy();//如果没有食物了，就产生一个新的食物
			}
			for (int i = 0; i < numblock; i++) {//产生障碍物
				if (Block[i].GetBlockFlag() == 0)
				{
					blockxy(Block[i]);
				}
			}
			if (Food.GetFoodFlag()) Food.inifood();
			if (SpeFood.GetFoodFlag()) SpeFood.inifood();//绘画食物
			for (int i = 0; i < numblock; i++) {
				if (Block[i].GetBlockFlag()) Block[i].iniblock();
			}//绘画障碍物
			Snake.inisnake();//绘画蛇

			snakedie();//判断蛇是否死亡
			eatfood();//判断蛇是否能吃掉食物
			Snake.moveway();//移动蛇
			Sleep(100 - speed * 5);//根据速度参数来改变sleep的时间来达到改变蛇运动快慢的目的

			while (_kbhit()) //接受上下左右的按键
			{
				again();
				Snake.snakemove();
			}

			if (num == 5) { //达到5个普通食物就产生特殊食物
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
				if (step == 80) { //计数达到80步就会消失
					SpeFood.SetFoodFlag(0); f = 0; step = 0;
				}
			}

			if (Snake.die()) { //如果蛇死亡
				mciSendStringW(L"close love.mp3", 0, 0, 0);
				numscore++; scorexi[numscore] = Snake.GetEatgrade();
				update1();//更新成绩
				break;//退出
			}
		}
		break;
	}
	while (1);
	return 0;
}

void foodxy()
{
	//蛇坐标 0 10 20 30 n*10
	//食物 如果 rand() % 650 那么坐标0 1 2 3 4 蛇将吃不到食物 坐标重合低

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
	outfile1 << "分数" << endl;
	for (int i = 1; i <= numscore; i++) {
		outfile1 << scorexi[i] << endl;
	}
	int p = 0;
	if (numscore > 10) p = 10; else p = numscore;
	int hang = 40;
	gotoxy(1000 / 20, hang / 20); color(15); printf("排行榜");
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
	/*初始化界面选项*/
	gotoxy(6, 6);
	color(4);
	printf("贪   吃   蛇   游   戏");
	gotoxy(6, 8);
	printf("  	  V 1.0");
	gotoxy(6, 10);
	printf("Made    by   Zhoujunjie");
	color(15);
	gotoxy(6, 21);
	printf("请选择：");
	gotoxy(6, 22);
	printf("(上下键选择,回车确认)");
	gotoxy(6, 23);
	printf("(+ 键选择开声音 - 键选择关声音)");
	gotoxy(27, 22);
	color(25);
	printf("开始游戏");
	gotoxy(27, 24);
	color(15);
	printf("退出游戏");
	gotoxy(27, 26);
	color(100);
	printf("声音：开");
	color(15);
	/*上下方向键选择模块*/
	int ch;//记录键入值
	int key = 1;//记录选中项，初始选择第一个
	bool flag = false;//记录是否键入Enter键标记，初始置为否
	while ((ch = _getch()))
	{
		switch (ch)//检测输入键
		{
		case '+':
			if (!openmusic) {
				openmusic = true;
				gotoxy(27, 26);
				color(100);
				printf("声音：开");
			}
			break;
		case '-':
			if (openmusic) {
				openmusic = false;
				gotoxy(27, 26);
				color(100);
				printf("声音：关");
			}
			break;
		case 72://UP上方向键
			if (key > 1)//当此时选中项为第一项时，UP上方向键无效
			{
				gotoxy(27, 22);//给待选中项设置背景色
				color(25);
				printf("开始游戏");

				gotoxy(27, 24);//将已选中项取消我背景色
				color(15);
				printf("退出游戏");

				--key;
			}
			break;

		case 80://DOWN下方向键
			if (key < 2)
			{
				gotoxy(27, 22);
				color(15);
				printf("开始游戏");

				gotoxy(27, 24);
				color(25);
				printf("退出游戏");

				++key;
			}
			break;

		case 13://Enter回车键
			flag = true;
			break;
		default://无效按键
			break;
		}
		if (flag) break;//输入Enter回车键确认，退出检查输入循环
	}
	if (key == 1) { color(15); system("cls"); return; }
	else {
		color(15); exit(-1);
	}
}

//判断蛇是否死亡
void snakedie()
{
	{ //分数
		char grade[100] = { 0 };
		sprintf(grade, "%d", Snake.eatgrade);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(680 / 20, 20 / 20); color(15); printf("分数：");
		gotoxy(720 / 20, 20 / 20); color(15);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf(grade);
		char ka[100] = { 0 };
		sprintf(ka, "%d", speed*2+numblock+1);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(0 / 20, 560 / 20); color(15); printf("关卡：");
		gotoxy(40 / 20, 560 / 20); color(15);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY); 
		printf(ka);
	}

	if (Snake.xy_x[0] > 630 || Snake.xy_x[0] < 0 || Snake.xy_y[0] > 480 || Snake.xy_y[0] < 0)
	{
		char grade[100] = { 0 };
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(200 / 20, 200 / 20); color(15); printf("你的分数是");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		sprintf(grade, "%d", Snake.eatgrade);
		SetConsoleTextAttribute(hOut, 0xB);
		gotoxy(370 / 20, 200 / 20); color(15); printf(grade);
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		gotoxy(200 / 20, 590 / 20); color(15); printf("撞墙了，游戏结束！");
		Snake.flag = false;
	}

	for (int i = 1; i < Snake.num; i++)
	{
		if (Snake.xy_x[0] == Snake.xy_x[i] && Snake.xy_y[0] == Snake.xy_y[i])
		{
			gotoxy(130 / 20, 590 / 20); color(15);
			SetConsoleTextAttribute(hOut, 0xB);
			printf("你咬死了自己，游戏结束！");
			Snake.flag = false;
		}
	}

	for (int i = 0; i < numblock; i++) {
		if (Snake.GetXy_x(0) == Block[i].GetBdx() && Snake.GetXy_y(0) == Block[i].GetBdy())
		{
			char grade[100] = { 0 };
			SetConsoleTextAttribute(hOut, 0xB);
			gotoxy(200 / 20, 200 / 20); color(15); printf("你的分数是");
			sprintf(grade, "%d", Snake.eatgrade);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			gotoxy(370 / 20, 200 / 20); color(15); printf(grade);
			SetConsoleTextAttribute(hOut, 0xB);
			gotoxy(200 / 20, 590 / 20); color(15);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("撞到障碍物了，游戏结束！");
			Snake.flag = false;
		}
	}
}
void paint() {
	time_t tt = time(NULL);
	tm t;//时间结构体
	localtime_s(&t, &tt);//获取时间
	int hour, sec, min;
	hour = t.tm_hour;
	min = t.tm_min;
	sec = t.tm_sec;
	int second = hour * 3600 + min * 60 + sec - (hour_begin * 3600 + min_begin * 60 + sec_begin);
	gotoxy(680 / 20, 19); printf("            You already play %d秒\n",second);
	gotoxy(680 / 20, 20); printf("            贪吃蛇 V 1.0 made by zhoujunjie\n");
}