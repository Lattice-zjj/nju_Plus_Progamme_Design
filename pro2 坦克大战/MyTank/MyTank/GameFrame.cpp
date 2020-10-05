#include "GameFrame.h"
#include "MapInit.h"
#include <Mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
bool openmusic;
int level = 0;
GameFrame::GameFrame() {
	openmusic = true;
	string st;
	vector<string> help1,help2;
	st = "      ■"; help1.push_back(st); st = "  ■■■■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "      ■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "    ■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "  ■■■■"; help2.push_back(st);
	num.push_back(help1); num.push_back(help2);
	help1.clear(); help2.clear();
	st = "      ■";   help1.push_back(st); st = "  ■■■■"; help2.push_back(st);
	st = "    ■■";   help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "  ■  ■";   help1.push_back(st); st = "      ■"; help2.push_back(st);
	st = "■■■■■"; help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "      ■";   help1.push_back(st); st = "  ■■■■"; help2.push_back(st);
	num.push_back(help2); num.push_back(help1);
	help1.clear(); help2.clear();
	st = "■■■■"; help1.push_back(st); st = "■■■■■"; help2.push_back(st);
	st = "■     "; help1.push_back(st);  st = "■      "; help2.push_back(st);
	st = "■■■■"; help1.push_back(st); st = "■■■■■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "■■■■"; help1.push_back(st); st = "■■■■■"; help2.push_back(st);
	num.push_back(help1); num.push_back(help2);
	help1.clear(); help2.clear();
	st = "■■■■"; help1.push_back(st); st = "  ■■■"; help2.push_back(st);
	st = "      ■"; help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "    ■";   help1.push_back(st); st = "  ■■■"; help2.push_back(st);
	st = "  ■    "; help1.push_back(st); st = "■      ■"; help2.push_back(st);
	st = "■      "; help1.push_back(st); st = "  ■■■"; help2.push_back(st);
	num.push_back(help1); num.push_back(help2);
	help1.clear(); help2.clear();
	st = "■■■■"; help1.push_back(st);
	st = "■    ■"; help1.push_back(st);
	st = "■■■■"; help1.push_back(st);
	st = "      ■"; help1.push_back(st);
	st = "■■■■"; help1.push_back(st);
	num.push_back(help1);
	help1.clear(); help2.clear();
	for (int i = 4; i < 9; i++) {
		for (int j = 0; j < 38; j++) {
			for (int k = 0; k < 38; k++) {
				Map[i][j][k] = Map[i - 4][j][k];
			}
		}
	}
	userTank = new MyTank;
}
GameFrame::~GameFrame() {
	num.clear();
}
void GameFrame::show() {
	SetConsoleTitleA("坦克大战游戏 V 1.0 made by zhoujunjie");//设置标题
	system("mode con cols=92 lines=38");//改变窗体大小
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //设置光标大小，隐藏光标
	initGame();
	chooseLevel();
	system("cls");
	while (1) {
		if (openmusic) PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
		GameStart NewGame;
		if (NewGame.start(userTank) == 1) level = (level + 1) % 9; else break;
		userTank->resetxy();
		system("cls");
		p.printfxywithcolor(15, 13, 5, "进入下一关......");
		Sleep(1000);
		system("cls");
	}
	system("cls");
	p.printfxywithcolor(15, 13, 5, "您失败啦（按任意键结束）......");
	Sleep(3000);
	_getch();
}
void GameFrame::initGame() {
	/*初始化界面选项*/
	p.gotoxy(15, 9);
	p.color(5);
	p.gotoxy(1, 3); printf("■■■■■     ■      ■      ■ ■    ■ ■        ■        ■     ■      ■■■■ \n");
	p.gotoxy(1, 4); printf("    ■       ■  ■    ■■    ■ ■  ■    ■      ■ ■     ■    ■  ■    ■    ■\n");
	p.gotoxy(1, 5); printf("    ■      ■■■■   ■  ■  ■ ■■       ■    ■   ■   ■    ■■■■   ■■■■\n");
	p.gotoxy(1, 6); printf("    ■     ■      ■  ■    ■■ ■  ■      ■  ■     ■ ■    ■      ■  ■  ■\n");
	p.gotoxy(1, 7); printf("    ■    ■        ■ ■      ■ ■    ■      ■        ■     ■        ■ ■    ■\n");
	//printf("坦    克    大    战    游    戏");
	p.gotoxy(21, 11);
	printf("V 1.0");
	p.gotoxy(15, 13);
	printf("Made         by        Zhoujunjie");
	p.color(15);
	p.gotoxy(10, 22);
	printf("请选择：");
	p.gotoxy(10, 24);
	printf("(上下键选择,回车确认)");
	p.gotoxy(10, 26);
	printf("(+ 键选择开声音 - 键选择关声音)");
	p.gotoxy(35, 22);
	p.color(25);
	printf("开始游戏");
	p.gotoxy(35, 24);
	p.color(15);
	printf("退出游戏");
	p.gotoxy(35, 26);
	p.color(100);
	printf("声音：开");
	p.color(15);
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
				p.gotoxy(35, 26);
				p.color(100);
				printf("声音：开");
			}
			break;
		case '-':
			if (openmusic) {
				openmusic = false;
				p.gotoxy(35, 26);
				p.color(100);
				printf("声音：关");
			}
			break;
		case 72://UP上方向键
			if (key > 1)//当此时选中项为第一项时，UP上方向键无效
			{
				p.gotoxy(35, 22);//给待选中项设置背景色
				p.color(25);
				printf("开始游戏");

				p.gotoxy(35, 24);//将已选中项取消我背景色
				p.color(15);
				printf("退出游戏");

				--key;
			}
			break;

		case 80://DOWN下方向键
			if (key < 2)
			{
				p.gotoxy(35, 22);
				p.color(15);
				printf("开始游戏");

				p.gotoxy(35, 24);
				p.color(25);
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
	if (key == 1) { p.color(15); system("cls"); return; }
	else {
		p.color(15); exit(-1);
	}
}

void GameFrame::chooseLevel()
{ 
	for (int i = 0; i <= 8; i++) {
		p.color(5);
		p.gotoxy(i, 14); printf("■      ■■■   ■        ■   ■■■   ■\n");
		p.gotoxy(i, 15); printf("■      ■        ■      ■    ■       ■\n");
		p.gotoxy(i, 16); printf("■      ■■■     ■    ■     ■■■   ■\n");
		p.gotoxy(i, 17); printf("■      ■          ■  ■      ■       ■\n");
		p.gotoxy(i, 18); printf("■■■  ■■■        ■        ■■■   ■■■\n");
		Sleep(50);
		if (i != 8) {
			for (int j = 14; j <= 18; j++) {
				p.gotoxy(i, j); printf("  ");
			}
		}
	}
	p.printfxywithcolor(10, 23, 2, string("按上（右）下（左）键进行等级的增减,回车键确认"));
	char ch;
	bool flag = false;
	for (int i = 14; i <= 18; i++) {
		p.gotoxy(33, i); printf("            ");
	}
	for (int i = 14; i <= 18; i++) {
		p.gotoxy(33, i); p.color(1); printf("%s", num[level][i - 14].c_str());
	}
	while ((ch = _getch()))
	{
		switch (ch)//检测输入键
		{
		case 72://UP上方向键
			level++; if (level >= 9) level = 0;
			break;

		case 80://DOWN下方向键
			level--; if (level < 0) level = 8;
			break;
		case 75:
			level--; if (level < 0) level = 8;
			break;
		case 77:
			level++; if (level >= 9) level = 0;
			break;
		case 13://Enter回车键
			flag = true;
			break;
		default://无效按键
			break;
		}
		if (flag) break;//输入Enter回车键确认，退出检查输入循环
		for (int i = 14; i <= 18; i++) {
			p.gotoxy(33, i); printf("            ");
		}
		for (int i = 14; i <= 18; i++) {
			p.gotoxy(33, i); p.color(1); printf("%s", num[level][i - 14].c_str());
		}
	}
}
