#include "food.h"
#include <time.h>
food::food() {
	flag = 0;
	fdx = 0;
	fdy = 0;
	kind = 0;
	time_t tt = time(NULL);
	tm t;//时间结构体
	localtime_s(&t, &tt);//获取时间
	int hour, sec, min;
	hour_begin = t.tm_hour;
	min_begin = t.tm_min;
	sec_begin = t.tm_sec;
}

void food::SetFoodFlag(int x) {
	flag = x;
}

void food::inifood()
{
	if (kind == 0) {
		color(8); gotoxy(fdx / 20, fdy / 20);  printf("●");
	}
	else {
		time_t tt = time(NULL);
		tm t;//时间结构体
		localtime_s(&t, &tt);//获取时间
		int hour, sec, min;
		hour = t.tm_hour;
		min = t.tm_min;
		sec = t.tm_sec;
		int second = hour * 3600 + min * 60 + sec - (hour_begin * 3600 + min_begin * 60 + sec_begin);
		if (second % 2 == 0) {
			color(20); gotoxy(fdx / 20, fdy / 20); printf("●");
		}
		else {
			color(100); gotoxy(fdx / 20, fdy / 20); printf("●");
		}
	}
	
}
