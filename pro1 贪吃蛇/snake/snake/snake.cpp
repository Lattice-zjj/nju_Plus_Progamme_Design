#include "snake.h"
snake::snake() { //构造函数

	xy_x[2] = 0;
	xy_y[2] = 0;
	xy_x[1] = 20;
	xy_y[1] = 0;
	xy_x[0] = 40;
	xy_y[0] = 0;
	num = 3;
	way = right;
	eatgrade = 0;
	flag = true;
}
void snake::inisnake() {
	for (int i = 0; i < num; i++)
	{
		if (xy_x[i] < 0 || xy_y[i] < 0) continue;
		gotoxy(xy_x[i] / 20, xy_y[i] / 20); color(15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
		if (i == 0)printf("●"); else printf("■");
	}
	gotoxy(lastx / 20, lasty / 20); printf(" ");
}

void snake::snakemove()
{
	char ch = 0;
	ch = _getch();
	switch (ch)
	{
	case 72:
		if (!(xy_x[0] == xy_x[1] && xy_y[0] == xy_y[1] + 20))
			way = up;
		break;
	case 75:
		if (!(xy_x[0] == xy_x[1] + 20 && xy_y[0] == xy_y[1]))
			way = left;
		break;
	case 77:
		if (!(xy_x[0] == xy_x[1] - 20 && xy_y[0] == xy_y[1]))
			way = right;
		break;
	case 80:
		if (!(xy_x[0] == xy_x[1] && xy_y[0] == xy_y[1] - 20))
			way = down;
		break;
	default:
		break;
	}
}

//蛇的移动
void snake::moveway()
{
	//除了第一节蛇，后面每节都是前面一节蛇的前一次坐标
	lastx = xy_x[num - 1];
	lasty = xy_y[num - 1];
	for (int i = num - 1; i > 0; i--)
	{
		xy_x[i] = xy_x[i - 1];
		xy_y[i] = xy_y[i - 1];
	}
	
	switch (way)
	{
	case right:
		xy_x[0] += 20;
		break;
	case left:
		xy_x[0] -= 20;
		break;
	case down:
		xy_y[0] += 20;
		break;
	case up:
		xy_y[0] -= 20;
		break;
	default:
		break;
	}
}
