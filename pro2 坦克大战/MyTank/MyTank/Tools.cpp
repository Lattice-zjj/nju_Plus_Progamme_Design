#include "Tools.h"
void Tools::run(Tank* tank, vector<EnemyTank*> enemy, MyTank* user) {
	if (type == 4) {
		tank->overen = true;
	}
	else if (type == 3) {
		if (tank->ifmy()) {
			setBorder(3);
		}
		else setBorder(0);
	}
	else if (type == 2) {
		if (tank->ifmy()) {
			for (int i = 0; i < enemy.size(); i++) {
				enemy[i]->stop = true;
			}
		}
		else {
			user->stop = true;
		}
	}
	else if (type == 1) {
		if (tank->ifmy()) {
			if (user->grade == 0) {
				user->grade = 1; user->ShootSpeed = 400;
				user->color++;
			}
			else if (user->grade == 1) {
				user->grade = 2; user->twobullet = true;
				user->color++;
			}
			else {
				user->grade = 3;
				user->color++;
			}
		}
		else {
			tank->grade = 3;
		}
	}
	else {
		if (tank->ifmy()) {
			user->ming++;
			p.gotoxy(43, 5); p.color(6); printf("%d", user->ming);
		}
		else {
			tank->blood += 4000;
			int num = tank->type - 1;
			p.gotoxy(41, 10 + num); p.color(enemy[num]->color); printf("%-5d", enemy[num]->blood);
		}
	}
};