#include "MyTank.h"
MyTank::MyTank() {
    x = 14; y = 35;
    direct = 0;
    color = 1;
    blood = 9000;
    atk = 2;
    alive = false;
    type = 0;
    ming = 3;
    grade = 0;
    twice = false;
    twobullet = false;
    ShootSpeed = 100;
}
MyTank::~MyTank() {

}

void MyTank::BuildUser()
{
    this->x = 14; this->y = 35;
    this->direct = 0;
    this->color = 1;
    this->blood = 9000;
    this->atk = 2;
    this->alive = true;
    this->type = 0;
    this->grade = 0;
    this->twobullet = false;
    this->twice = false;
    this->ShootSpeed = 100;
    p.gotoxy(43, 7); p.color(7); printf("%-5d", this->blood);
}

void MyTank::resetxy()
{
    this->x = 14; this->y = 35;
    this->direct = 0;
}
