#include "block.h"

block::block() {
	flag = 0;
	fdx = 0;
	fdy = 0;
	kind = 0;
}

void block::SetblockFlag(int x) {
	flag = x;
}

void block::iniblock()
{
	gotoxy(fdx / 20, fdy / 20); color(12); printf("¡ô");

}
