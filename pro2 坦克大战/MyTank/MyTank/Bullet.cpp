#include "Bullet.h"

Bullet::Bullet() {
    x = 0; y = 0; place = 0;
    f = false;
    Is_First = true;
    atk = 0;
    If_Through = false;
}
Bullet::~Bullet() {

}
void Bullet::Print() {
    if (place == 1) p.color(15);
    else if (place == 2) p.color(31);
    p.gotoxy(x, y);
    printf("●");
}
void Bullet::Reset() {
    p.gotoxy(x, y);
    if (place == 1) {
        p.color(1);
        printf("  ");
    }
    if (place == 2) {
        p.color(27);
        printf("～");
    }
}
bool Bullet::Move() {
    if (!Is_First) {   
        if (Map[level][y][x] == 0 || Map[level][y][x] == 5)   //如果子弹坐标当前位置无障碍
            Reset();     //抹除子弹图形
        switch (direct) //然后子弹坐标变化（子弹变到下一个坐标）
        {
        case 0:y--; break;
        case 1:y++; break;
        case 2:x--; break;
        case 3:x++; break;
        }
    }
    if (Map[level][y][x] == 0) place = 1;
    else if (Map[level][y][x] == 5) place = 2;
    else place = 0;//不可通过
    if (place)  
        Print();    
    else
        return false;    //若有碰撞则执行子弹碰撞函数                  

    if (Is_First) Is_First = false;
    return true;
}