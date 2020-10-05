#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "PainterHelper.h"
#include "GameStart.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <cstring>
using namespace std;
class GameFrame
{
public:
	GameFrame();
	~GameFrame();
	void show();
private:
	PainterHelper p;
	void initGame();
	void chooseLevel();
	vector<vector<string>> num;
	MyTank* userTank;
};

