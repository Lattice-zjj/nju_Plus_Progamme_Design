#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include <windows.h>
#include "Normal.h"
#include "PainterHelper.h"
typedef struct _Node
{
	int x, y;//此点的坐标
	int px, py;//父节点的坐标
	int dir;//当前的方向
	int f, g, h;//对应的F、G、H值
}NODE, * PNODE;
class Astar{
public:
	Astar();
	~Astar();
	bool AstarWork();
	int* GetBestRoad();
	bool ReleaseRoad();
	PainterHelper p;
	friend class EnemyTank;

private:
	NODE  Start, Des, Cur, Next;
	std::vector<NODE> v_open;//v_open表
	std::vector<NODE> close;//close表
	NODE* BestRoad;
	int* BestDir;
	void GetStartAndDesPoint(int x,int y);
	NODE GetCloseData(int x, int y);
	bool FindEdge(NODE* cur);
	bool FindSteel(NODE* cur);
	bool FindDes(NODE* cur);
	bool FindOpen(NODE* cur, NODE** old);
	bool FindClose(NODE* cur);
	int CalcG(NODE* cur, NODE* pcur);
	int CalcH(NODE* cur);
	bool FindPoint(NODE* cur, NODE* pcur);

};
