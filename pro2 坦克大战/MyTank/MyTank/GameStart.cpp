#include "GameStart.h"
#include <Mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
enum { UP, DOWN, LEFT, RIGHT };
bool havetools;
GameStart::GameStart() {
    over.first = false;
    running = true;
    Bullet h;
    EnemyTank w;
    for (int i = 0; i < 100; i++) bullet.push_back(h);
    ZhuangTank* w1 = new ZhuangTank; LightTank* w2 = new LightTank; HeavyTank* w3 = new HeavyTank;
    root.push_back(w1); root.push_back(w2); root.push_back(w3);
    userTank = new MyTank;
    num_of_enemy = 0;
    display = true;
    Stop = false;
}

int GameStart::start(MyTank* user1) {
    userTank = user1;
    srand(time(NULL));
    PrintSideInfor();
    DrawMap();
    Init();
    food.SetXy();
    food.SetType(rand() % 5);
    while (1) {
        if (GetTickCount() - clock_return > 20) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                running = !running;
            }
            clock_return = GetTickCount();
        }
        if (!running) continue;
        if (over.first) return over.second;
        if (!userTank->alive) {
            userTank->BuildUser(); if (openmusic) PlaySound(TEXT("add.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        if (userTank->alive) userTank->Print();
        DWORD clockfood_1 = GetTickCount();
        if (clockfood_1 - clock_food > 10000) {
            if (food.alive) {
                food.Reset();
            }
            else {
                food.SetXy();
                food.SetType(rand() % 5);
                food.alive = false;
            }
            food.alive = !food.alive;
            clock_display = GetTickCount();
            clock_food = clockfood_1;
        }
        if (food.alive) {
            DWORD clock_display_1 = GetTickCount();
            if (clock_display_1 - clock_display > 70) {
                if (display) {
                    food.Print(); display = false;
                }
                else {
                    food.Reset(); display = true;
                }
                clock_display = clock_display_1;
            }
        }
        if (Stop) {
            if (GetTickCount() - clock_stop > 10000) {
                userTank->stop = false;
                Stop = false;
            }
        }
        DWORD clock2_1 = GetTickCount();
        if (clock2_1 - clock_bullet > 20) {
            for (int i = 0; i < 100; i++)
                if (bullet[i].f) {
                    if (!bullet[i].Move()) CrashJudge(bullet[i]);
                    BulletsCrash();
                }
            clock_bullet = clock2_1;
        }
        DWORD clock3_1 = GetTickCount();
        if (clock3_1 - clock_key > 100) {
            if (userTank->alive && !userTank->stop) DoKey();
            clock_key = clock3_1;
        }
        if (userTank->twobullet && userTank->twice) {
            if (GetTickCount() - middle_bullet > 40) {
                BuildBullet(*userTank);
                userTank->twice = false;
            }
        }
        for (int i = 0; i < root.size(); i++) {
            if (!root[i]->alive && root[i]->num>0) {
                DWORD now = GetTickCount();
                if (now - clock_enemy[i] > 1000) {
                    if (openmusic) PlaySound(TEXT("add.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    root[i]->alive = true;
                    root[i]->reset();
                    p.gotoxy(41, 10 + i); p.color(root[i]->color); printf("%-5d%d", root[i]->blood, root[i]->num);
                }
            }
        }
        for (int i = 0; i < root.size(); i++) {
            DWORD clockt = GetTickCount();
            if (clockt - clock_enemy_move[i] > 200 - root[i]->speed) {
                if (root[i]->alive && !root[i]->stop) if (!root[i]->AutoMove()) root[i]->RandMove();
                clock_enemy_move[i] = clockt;
            }
        }
        for (int i = 0; i < 3; i++) {
            DWORD clock5_1 = GetTickCount();
            if (clock5_1 - clock_en_bullet[i] > 1000-root[i]->ShootSpeed) {
                if (root[i]->alive&& !root[i]->stop) BuildBullet(*root[i]);
                clock_en_bullet[i] = clock5_1;
            }
        }
        if (food.alive) FoodEaten();
        ToolCheck();
        GameJudge();
    }
}
void GameStart::PrintSideInfor() {
    p.gotoxy(39, 2);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
    printf("第  %d  关", level + 1);
    p.gotoxy(39, 5);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    printf("生  命：");
    p.gotoxy(43, 5); p.color(6); printf("%d", userTank->ming);
    p.gotoxy(39, 7);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("血  量：");
    p.gotoxy(43, 7); p.color(7); printf("%-5d", userTank->blood);
    p.gotoxy(39, 9);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf("敌方血量、数量");
    p.gotoxy(39, 24);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
    printf("帮  助");
    p.gotoxy(39, 27);
    p.color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("awsd 移动");
    p.gotoxy(39, 29);
    printf("j 键 射击");
    p.gotoxy(39, 31);
    printf("回车键暂停");
}

void GameStart::DrawMap() {
    for (int i = 0; i < 38; i++) {
        for (int j = 0; j < 38; j++) {
            p.MapDraw(Map[level][i][j], j, i);
        }
    }
    p.color(6); p.gotoxy(18, 36); printf("◢◣");
    p.gotoxy(18, 35); printf("██");
}
void GameStart::GameOver(int f) {
    system("cls");
    if (f == 0) {
        p.gotoxy(19, 10); p.color(3); printf("你的生命已尽！");
        over.first = true; over.second = false;
    }
    else {
        p.gotoxy(19, 10); p.color(3); printf("你老家被抄了！");
        over.first = true; over.second = false;
    }
    int sum = 0;
    for (int i = 0; i < root.size(); i++) {
        root[i]->direct = 0; root[i]->x = 18; root[i]->y = 14 + 4 * i;
        if (i == 2) root[i]->color = 6;
        root[i]->Print();
        p.gotoxy(20, 14 + 4 * i); p.color(9); printf("*  %d  =  %d", 4 - root[i]->num, root[i]->score * (4 - root[i]->num));
        sum += root[i]->score * (4 - root[i]->num);
    }
    p.gotoxy(18, 14 + 4 * 4); p.color(5); printf("您的分数为：%d", sum);
    Sleep(2000);
}
void GameStart::GameJudge() {
    if (num_of_enemy == 12) {
        system("cls");
        p.gotoxy(19, 10); p.color(3); printf("恭喜你打败了所有敌人！");
        over.first = true; over.second = true;
        int sum = 0;
        for (int i = 0; i < root.size(); i++) {
            root[i]->direct = 0; root[i]->x = 18; root[i]->y = 14 + 4 * i;
            if (i == 2) root[i]->color = 6;
            root[i]->Print();
            p.gotoxy(20, 14 + 4 * i); p.color(9); printf("*  %d  =  %d", 4 - root[i]->num, root[i]->score * (4 - root[i]->num));
            sum += root[i]->score * (4 - root[i]->num);
        }
        p.gotoxy(18, 14 + 4 * 4); p.color(5); printf("您的分数为：%d", sum);
        Sleep(2000);
    }
    if (userTank->ming <= 0) GameOver(0);
}

void GameStart::DoKey() {
    if (GetAsyncKeyState(0x57) & 0x8000)
        userTank->Move(0);
    else if (GetAsyncKeyState(0x53) & 0x8000)
        userTank->Move(1);
    else if (GetAsyncKeyState(0x41) & 0x8000)
        userTank->Move(2);
    else if (GetAsyncKeyState(0x44) & 0x8000)
        userTank->Move(3);
    else if (GetAsyncKeyState(0x1B) & 0x8000)  // Esc键
        exit(0);  //退出程序函数
    if (GetAsyncKeyState(0x4A) & 0x8000) {
        DWORD t = GetTickCount();
        if (t - clock_my_bullet > 500-userTank->ShootSpeed) {
            BuildBullet(*userTank);
            if (userTank->twobullet) {
                userTank->twice = true;
            }
            middle_bullet = GetTickCount();
            clock_my_bullet = t;
        }
    }
}

void GameStart::CrashJudge(Bullet& bullet) {
    int x = bullet.x;
    int y = bullet.y;
    if (Map[level][y][x] == 1 || Map[level][y][x] == 2) {
        if (bullet.direct == 0 || bullet.direct == 1)   //如果子弹是纵向的
            for (int i = -1; i <= 1; i++) {
                if (Map[level][y][x + i] == 1 || Map[level][y][x + i] == 2){
                    Map[level][y][x + i] = 0;    //砖块碎
                    p.gotoxy(x + i, y);
                    p.color(4);
                    printf("  ");
                }
            }
        if (bullet.direct == 2 || bullet.direct == 3)     //若子弹是横向的 
            for (int i = -1; i <= 1; i++) {
                if (Map[level][y + i][x] == 1 || Map[level][y + i][x] == 2) {
                    Map[level][y + i][x] = 0;
                    p.gotoxy(x, y + i);
                    p.color(4);
                    printf("  ");
                }
            }
        bullet.f = false;           //这颗子弹已经不存在了
        if (openmusic) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (Map[level][y][x] == 4 || Map[level][y][x] == 3) { //子弹碰到边框或者不可摧毁方块
        if (bullet.If_Through) { //看子弹发出者是否能够打穿铁块
            if (bullet.direct == 0 || bullet.direct == 1)   //如果子弹是纵向的
                for (int i = -1; i <= 1; i++) {
                    if (Map[level][y][x + i] == 1 || Map[level][y][x + i] == 2 || Map[level][y][x + i] == 3) {
                        Map[level][y][x + i] = 0;
                        p.gotoxy(x + i, y);
                        p.color(4);
                        printf("  ");
                    }
                }
            if (bullet.direct == 2 || bullet.direct == 3)   //若子弹是横向的 
                for (int i = -1; i <= 1; i++) {
                    if (Map[level][y + i][x] == 1 || Map[level][y + i][x] == 2 || Map[level][y][x + i] == 3) {
                        Map[level][y + i][x] = 0;
                        p.gotoxy(x, y + i);
                        p.color(4);
                        printf("  ");
                    }
                }
        }
        bullet.f = false;
        if (openmusic) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (bullet.type == 0 && Map[level][y][x] > 10 && Map[level][y][x] < 14) {
        int num = Map[level][y][x] % 10 - 1;
        root[num]->blood -= bullet.atk * 1000;
        if (root[num]->type == 3) {
            root[num]->color++;
        }
        if (root[num]->blood < 0) {
            root[num]->blood = 3000;
            root[num]->alive = false;
            root[num]->Reset();
            root[num]->num--;
            clock_enemy[num] = GetTickCount();
            num_of_enemy++;
            p.gotoxy(41, 10 + num); p.color(root[num]->color); printf("%-5d%d", 0, root[num]->num);
            if (openmusic) PlaySound(TEXT("bang.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        else {
            p.gotoxy(41, 10 + num); p.color(root[num]->color); printf("%-5d", root[num]->blood);
        }
        bullet.f = false;
        if (openmusic) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (Map[level][y][x] == 20 && bullet.type != 0) 
    {
        userTank->blood -= bullet.atk * 1000;
        if (userTank->blood <= 0) {
            userTank->alive = false;
            userTank->Reset();
            p.gotoxy(43, 7); p.color(6); printf("%-5d", 0);
            userTank->ming--;
            p.gotoxy(43, 5); p.color(6); printf("%d", userTank->ming);
            if (openmusic) PlaySound(TEXT("bang.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        else {
            p.gotoxy(43, 7); p.color(6); printf("%-5d", userTank->blood);
        }
        bullet.f = false;
        if (openmusic) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }

    else if (Map[level][y][x] == 9)
    {
        bullet.f = false; p.color(7);
        if (openmusic) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
        p.gotoxy(18, 35); printf("◣◢");
        p.gotoxy(18, 36); printf("◢◣");
        GameOver(1);           //游戏结束,传入1代表老家被毁
    }
}

void GameStart::FoodEaten() {
    if (Map[level][food.y][food.x] > 10 && Map[level][food.y][food.x] <=13) {
        food.run(root[Map[level][food.y][food.x] - 11],root, userTank);
        food.alive = false;
        clock_food = GetTickCount();
        if (food.type == 2) {
            Stop = true;
            clock_stop = GetTickCount();
        }
    }
    else if (Map[level][food.y][food.x] == 20) {
        food.run(userTank, root, userTank);
        food.alive = false;
        clock_food = GetTickCount();
    }
}
void GameStart::BuildBullet(Tank& tank,int x) {
    switch (tank.direct)
    {
    case 0:
        bullet[bul_num].x = tank.x;
        bullet[bul_num].y = tank.y - x;
        bullet[bul_num].direct = 0;
        break;
    case 1:
        bullet[bul_num].x = tank.x;
        bullet[bul_num].y = tank.y + x;
        bullet[bul_num].direct = 1;
        break;
    case 2:
        bullet[bul_num].x = tank.x - x;
        bullet[bul_num].y = tank.y;
        bullet[bul_num].direct = 2;
        break;
    case 3:
        bullet[bul_num].x = tank.x + x;
        bullet[bul_num].y = tank.y;
        bullet[bul_num].direct = 3;
        break;
    }
    if (openmusic) PlaySound(TEXT("fire.wav"), NULL, SND_FILENAME | SND_ASYNC);
    bullet[bul_num].f = true;    //子弹被建立,此值为1则此子弹存在
    bullet[bul_num].Is_First = true;  //子弹处于初建立状态
    bullet[bul_num].type = tank.type;   //如果是我的坦克发射的子弹bullet.my=1，否则为0
    bullet[bul_num].atk = tank.atk;
    if (tank.grade > 2) bullet[bul_num].If_Through = true; else bullet[bul_num].If_Through = false;
    bul_num++;
    if (bul_num == 100)        //如果子弹编号增长到100号，那么重头开始编号
        bul_num = 0;                 //考虑到地图上不可能同时存在20颗子弹，所以数组元素设置20个
}

void GameStart::Init()
{
    for (int i = 0; i < 3; i++) {
        clock_enemy[i] = GetTickCount();
        clock_enemy_move[i] = GetTickCount();
        clock_en_bullet[i] = GetTickCount();
    }
    clock_key = GetTickCount();
    clock_my_bullet = GetTickCount();
    clock_bullet = GetTickCount();
    clock_food = GetTickCount();
    clock_display = GetTickCount();
    clock_return = GetTickCount();
}
void GameStart::BulletsCrash() {
    for (int i = 0; i < 100; i++) {
        if (bullet[i].f) {
            for (int j = 0; j < 100; j++)
                if (bullet[j].f && j != i && (bullet[i].type || bullet[j].type) && bullet[i].x == bullet[j].x && bullet[i].y == bullet[j].y)
                {
                    bullet[j].f = false;
                    bullet[i].f = false;
                    bullet[j].Reset();
                    break;
                }
        }
    }
}

void GameStart::ToolCheck()
{
    if (userTank->overen) {
        for (int i = 0; i < 3; i++) {
            if (root[i]->num > 0) {
                root[i]->blood = 3000;
                root[i]->alive = false;
                root[i]->Reset();
                root[i]->num--;
                clock_enemy[i] = GetTickCount();
                num_of_enemy++;
                p.gotoxy(41, 10 + i); p.color(root[i]->color); printf("%-5d%d", 0, root[i]->num);
            }
        }
        userTank->overen = false;
    }
    for (int i = 0; i < 3; i++) {
        if (root[i]->overen) {
            userTank->alive = false;
            userTank->Reset();
            p.gotoxy(43, 7); p.color(6); printf("%-5d", 0);
            userTank->ming--;
            p.gotoxy(43, 5); p.color(6); printf("%d", userTank->ming);
            root[i]->overen = false;
        }
    }
}
