#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
class PainterHelper {
public:
	void color(int color);
	void gotoxy(int x, int y);
	void printfxywithcolor(int x, int y, int color, std::string st);
	void MapDraw(int type, int x, int y);
};
