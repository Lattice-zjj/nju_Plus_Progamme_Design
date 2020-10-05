#include "PainterHelper.h"

void PainterHelper::color(int color) {
	HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, color);
}

void PainterHelper::gotoxy(int x, int y) {
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void PainterHelper::printfxywithcolor(int x, int y, int color,std::string st) {
	HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, color);
	//光标属性光标不可见
	HANDLE  hstdOut = GetStdHandle(STD_OUTPUT_HANDLE);	//获得游戏句柄
	CONSOLE_CURSOR_INFO  cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", st.c_str());
}
void PainterHelper::MapDraw(int type, int x, int y) {
	if (type == 3) {
		color(127); gotoxy(x, y); printf("■");
	}
	else if (type == 0) {
		color(7); gotoxy(x, y); printf("  ");
	}
	else if (type == 2) {
		color(110); gotoxy(x, y); printf("▓");
	}
	else if (type == 1) {
		color(108); gotoxy(x, y); printf("▓");
	}
	else if (type == 5) {
		color(27); gotoxy(x, y); printf("～");
	}
	else if (type == 4) {
		color(7); gotoxy(x, y); printf("〓");
	}
	else if (type == 6) {
		color(108); gotoxy(x, y); printf("★");
	}
}