#include "graphics.h"
#include "draw.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void StartGame() {

	system("mode con: cols=100 lines=100");
	int select;
	int num = 1, truth = 1;

	gotoxytext(25, 21, "☞");
	while (1) {
		gotoxytext(28, 8, "┏━━━━━━━┓");
		gotoxytext(28, 11, "┃모 두 의 마 블┃ ");
		gotoxytext(28, 12, "┗━━━━━━━┛");
		gotoxytext(30, 21, "[1] 게임 시작");
		gotoxytext(30, 26, "[2] 게임 설명");
		select = _getch();

		switch (select) {
		case 80:
			num = 2;
			gotoxytext(26, 21, " ");
			gotoxytext(26, 26, "☞");
			break;
		case 72:
			num = 1;
			gotoxytext(26, 26, " ");
			gotoxytext(26
				, 21, "☞");
			break;
		case 13:
			system("cls");
			if (num == 1) {
				truth = 0;
				//startGame();
				break;
			}
			else if (num == 2) {
				//Explanation();
			}
		}
		if (truth == 0)
			break;
	}

}
