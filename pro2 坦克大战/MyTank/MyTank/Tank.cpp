#include "Tank.h"
Tank::Tank() {
    int i = 0;
    strcpy(tank_figure[i][0][0], "  ��  ");
    strcpy(tank_figure[i][1][0], "������");
    strcpy(tank_figure[i][2][0], "��  ��");
    strcpy(tank_figure[i][0][1], "��  ��");
    strcpy(tank_figure[i][1][1], "������");
    strcpy(tank_figure[i][2][1], "  ��  ");
    strcpy(tank_figure[i][0][2], "  ����");
    strcpy(tank_figure[i][1][2], "����  ");
    strcpy(tank_figure[i][2][2], "  ����");
    strcpy(tank_figure[i][0][3], "����  ");
    strcpy(tank_figure[i][1][3], "  ����");
    strcpy(tank_figure[i][2][3], "����  ");
    i = 1;
    strcpy(tank_figure[i][0][0], "  ��  ");
    strcpy(tank_figure[i][1][0], "������");
    strcpy(tank_figure[i][2][0], "���١�");
    strcpy(tank_figure[i][0][1], "���١�");
    strcpy(tank_figure[i][1][1], "������");
    strcpy(tank_figure[i][2][1], "  ��  ");
    strcpy(tank_figure[i][0][2], "  ����");
    strcpy(tank_figure[i][1][2], "������");
    strcpy(tank_figure[i][2][2], "  ����");
    strcpy(tank_figure[i][0][3], "����  ");
    strcpy(tank_figure[i][1][3], "�١���");
    strcpy(tank_figure[i][2][3], "����  ");
    i = 2;
    strcpy(tank_figure[i][0][0], "  ��  ");
    strcpy(tank_figure[i][1][0], "������");
    strcpy(tank_figure[i][2][0], "���ڡ�");
    strcpy(tank_figure[i][0][1], "���ڡ�");
    strcpy(tank_figure[i][1][1], "������");
    strcpy(tank_figure[i][2][1], "  ��  ");
    strcpy(tank_figure[i][0][2], "  ����");
    strcpy(tank_figure[i][1][2], "������");
    strcpy(tank_figure[i][2][2], "  ����");
    strcpy(tank_figure[i][0][3], "����  ");
    strcpy(tank_figure[i][1][3], "�ڡ���");
    strcpy(tank_figure[i][2][3], "����  ");
    i = 3;
    strcpy(tank_figure[i][0][0], "  ��  ");
    strcpy(tank_figure[i][1][0], "������");
    strcpy(tank_figure[i][2][0], "���ۡ�");
    strcpy(tank_figure[i][0][1], "���ۡ�");
    strcpy(tank_figure[i][1][1], "������");
    strcpy(tank_figure[i][2][1], "  ��  ");
    strcpy(tank_figure[i][0][2], "  ����");
    strcpy(tank_figure[i][1][2], "������");
    strcpy(tank_figure[i][2][2], "  ����");
    strcpy(tank_figure[i][0][3], "����  ");
    strcpy(tank_figure[i][1][3], "�ۡ���");
    strcpy(tank_figure[i][2][3], "����  ");
    x = 0; y = 0;
    grade = 1;
    overen = false;
    alive = false;
    stop = false;

}
Tank::~Tank() {

}
void Tank::Move(int turn) {
    Reset();
    direct = turn;                  //����������ķ���ֵ�����ҵ�̹�˷���ֵ
    if (Check()) {
        switch (turn)
        {
        case 0: y--; break;  //��ǰ��һ��
        case 1: y++; break;  //��ǰ��һ��
        case 2: x--; break;  //��ǰ��һ��
        case 3: x++; break;  //��ǰ��һ��
        }
    }
    Print();
}

bool Tank::Check() {
    switch (direct)
    {
    case 0:
        if (Map[level][y - 2][x] == 0 && Map[level][y - 2][x - 1] == 0 && Map[level][y - 2][x + 1] == 0)
            return true;
        else
            return false;
    case 1:
        if (Map[level][y + 2][x] == 0 && Map[level][y + 2][x - 1] == 0 && Map[level][y + 2][x + 1] == 0)
            return true;
        else
            return false;
    case 2:
        if (Map[level][y][x - 2] == 0 && Map[level][y - 1][x - 2] == 0 && Map[level][y + 1][x - 2] == 0)
            return true;
        else
            return false;
    case 3:
        if (Map[level][y][x + 2] == 0 && Map[level][y - 1][x + 2] == 0 && Map[level][y + 1][x + 2] == 0)
            return true;
        else
            return false;
    default:
        exit(-1);
    }
}

void Tank::Print() {
    p.color(color);
    for (int i = 0; i < 3; i++)
    {
        p.gotoxy(x - 1, y - 1 + i);
        printf("%s", tank_figure[type][i][direct]); 
        for (int j = 0; j < 3; j++)
            if (!type)       //��Ϊ�ҵ�̹��
                Map[level][y + j - 1][x + i - 1] = 20; 
            else
                Map[level][y + j - 1][x + i - 1] = 10 + type;
    }
}
void Tank::Reset() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            Map[level][y + j - 1][x + i - 1] = 0;
            p.color(2);
            p.gotoxy(x + j - 1, y + i - 1);
            printf("  ");
        }
}