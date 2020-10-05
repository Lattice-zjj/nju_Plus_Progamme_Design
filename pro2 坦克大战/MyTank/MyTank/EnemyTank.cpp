#include "EnemyTank.h"
EnemyTank::EnemyTank() {
    direct = 1;
    type = 0;
    color = 2;
    blood = 3000;
    atk = 1;
    num = 4;
    speed = -200;
    ShootSpeed = 0;
}
EnemyTank::~EnemyTank() {

}
bool EnemyTank::AutoMove() {
    Astar astar;
    BsetDir = 0;
    astar.GetStartAndDesPoint(x, y);
    if (astar.AstarWork()) {
        BsetDir = astar.GetBestRoad();
        step = 0;
        for (step; *(BsetDir + step) != -1; step++) //获取路径长度
        {
            //break;
        }
        step -= 1;//多读了结束标志-1
    }
    else step = -1;
    astar.ReleaseRoad();
    if (step >= 0) { Move(*(BsetDir + step)); step--; }
    if (step == -1) return false; else return true;
}
void EnemyTank::RandMove() {
    srand(time(NULL));
    if (!(rand() % 23))     
    {
        direct = rand() % 4;
        if (rand() % 3)   
        {
            return;
        }
    }
    Reset();
    if (Check())
        Move(direct);
    else                   
    {
        if (!(rand() % 4))     
        {
            direct = rand() % 4;
            Print();
            return;          
        }
        else              
        {
            int j;
            for (j = 1; j <= 4; j++)
                if (Check()) 
                    break;
            if (j == 5)         
            {
                Print();
                return;      
            }
            while (Check() == false) 
                direct = (rand() % 4);
            Move(direct);
        }
    }
    Print();
}