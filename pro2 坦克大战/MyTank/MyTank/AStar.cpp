#include "AStar.h"
Astar::Astar() :Start{ 0 }, Des{ 0 }, Cur{ 0 }, Next{ 0 }
{
}
Astar::~Astar()
{
	v_open.clear();//回收内存
	close.clear();
}
void Astar::GetStartAndDesPoint(int x ,int y) //获取目标和起始点
{
	Start.x = Start.px = x;
	Start.y = Start.py = y;
	Des.x = 14 + rand() % 3;
	Des.y = 32 + rand() % 4;
}
bool Astar::FindEdge(NODE* cur) { //判断是否是边界
	if (cur->x == 0 || cur->y == 0 || cur->x == 37 || cur->y == 37) return true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (Map[level][cur->y + i][cur->x + j] == 4) return true;
		}
	}
	return false;
}
bool Astar::FindSteel(NODE* cur) { //判断是否是障碍
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (Map[level][cur->y + i][cur->x + j] == 3 || (Map[level][cur->y + i][cur->x + j] == 5)) return true;
		}
	}
	return false;
}
bool Astar::FindDes(NODE* cur) {
	return (cur->x == Des.x && cur->y == Des.y);
}
bool Astar::FindOpen(NODE* cur, NODE** old) {
	for (UINT i = 0; i < v_open.size(); i++) {
		if (v_open[i].x == cur->x && v_open[i].y == cur->y)	{
			*old = &(v_open[i]);
			return true;
		}
	}
	return false;
}
bool  Astar::FindClose(NODE* cur) {
	for (UINT i = 0; i < close.size(); i++){
		if (close[i].x == cur->x && close[i].y == cur->y)return true;
	}
	return false;
}

int Astar::CalcG(NODE* cur, NODE* pcur)
{
	if (cur->x == pcur->x || cur->y == pcur->y) return 10;
	return 20;
}
int Astar::CalcH(NODE* cur)
{
	return ((abs(cur->x - Des.x) ) + abs(cur->y - Des.y)) * 10;
}

bool Astar::FindPoint(NODE* cur, NODE* pcur)
{
	NODE* old = nullptr;
	if (!FindDes(cur)) {
		if (!FindClose(cur)) {
			if (!FindOpen(cur, &old)) {
				if (!FindEdge(cur) && !FindSteel(cur)) {
					cur->px = pcur->x;
					cur->py = pcur->y;
					cur->g = CalcG(cur, pcur) + pcur->g;
					cur->h = CalcH(cur);
					cur->f = cur->g + cur->h;
					v_open.insert(v_open.begin(), *cur);
				}
			}
			else{
				if (old){
					if (CalcG(cur, pcur) + pcur->g < old->g) {
						old->px = pcur->x;
						old->py = pcur->y;
						old->g = CalcG(cur, pcur) + pcur->g;				
						old->f = old->g + old->h;
						old->dir = cur->dir;
					}
				}
			}
		}
	}
	else{
		cur->px = pcur->x;
		cur->py = pcur->y;
		close.push_back(*cur);
		return 1;
	}
	return 0;
}
bool Astar::AstarWork() {
	NODE* CUR = new NODE();
	Cur = Start;
	memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
	close.push_back(Start);
	while (1){
		if (abs(Cur.x - Des.x) - abs(Cur.y - Des.y) <= 0){ //先上下
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->y -= 1;
			CUR->dir = 0;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->y += 1;
			CUR->dir = 1;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->x += 2;
			CUR->dir = 3;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->x -= 2;
			CUR->dir = 2;
			if (FindPoint(CUR, &Cur)) break;
		}
		else //左右
		{
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->x += 2;
			CUR->dir = 3;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->x -= 2;
			CUR->dir = 2;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->y -= 1;  //上
			CUR->dir = 0;
			if (FindPoint(CUR, &Cur)) break;
			memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
			CUR->y += 1;
			CUR->dir = 1;
			if (FindPoint(CUR, &Cur)) break;
		}
		//排序v_open表
		if (v_open.size() > 0) {
			NODE t = { 0 };
			for (int i = v_open.size(); i > 0; i--) {
				for (int j = v_open.size() - 1; j > v_open.size() - i; j--) {
					if (v_open[j].f < v_open[j - 1].f) {
						t = v_open[j - 1]; v_open[j - 1] = v_open[j];v_open[j] = t;
					}
				}
			}
		}
		else {
			delete[] CUR;
			CUR = nullptr;
			return 0;
		}
		Cur = *v_open.begin();
		memcpy_s(CUR, sizeof(NODE), &Cur, sizeof(NODE));
		close.push_back(*v_open.begin());
		v_open.erase(v_open.begin());
	}
	NODE* Step = new NODE[close.size()]();//存放回溯节点
	int* r_dir = new int[close.size()]();//存放回溯的反向信息
	int p_x = CUR->x;
	int p_y = CUR->y;
	delete[] CUR;
	CUR = nullptr;
	for (int i = 0; ; i++) {
		*(Step + i) = GetCloseData(p_x, p_y);
		if ((*(Step + i)).x == Start.x && (*(Step + i)).y == Start.y) {
			*(r_dir + i) = -1;
			break;
		}
		*(r_dir + i) = (*(Step + i)).dir;
		p_x = (*(Step + i)).px;
		p_y = (*(Step + i)).py;
	}
	BestRoad = Step;
	BestDir = r_dir;
	return 1;
}

NODE Astar::GetCloseData(int x, int y) {
	for (unsigned int i = 0; i < close.size(); i++) {
		if (close[i].x == x && close[i].y == y) return close[i];
	}
	return { 0 };
}

int* Astar::GetBestRoad()
{
	if (BestDir) return BestDir; else return 0;
}

bool Astar::ReleaseRoad() //释放空间
{
	if (!BestRoad) {
		delete[] BestRoad;
		BestRoad = nullptr;
	}
	if (!BestDir) {
		delete[] BestDir;
		BestDir = nullptr;
	}
	return true;
}