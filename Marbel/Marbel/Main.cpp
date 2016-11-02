#include "start.h"
#include "draw.h"

void main() {

	cursor_view(0);

	//Loading();

	int select;
	int num = 1, truth = 1;

	gotoxytext(68, 18, "☞");
	while (1) {
		gotoxytext(70, 10, "┏━━━━━━━┓");
		gotoxytext(70, 11, "┃모 두 의 마 블┃ ");
		gotoxytext(70, 12, "┗━━━━━━━┛");
		gotoxytext(73, 18, "[1] 게임 시작");
		gotoxytext(73, 21, "[2] 게임 설명");
		select = _getch();

		switch (select) {
		case 80:
			num = 2;
			gotoxytext(68, 18, " ");
			gotoxytext(68, 21, "☞");
			break;
		case 72:
			num = 1;
			gotoxytext(68, 21, " ");
			gotoxytext(68, 18, "☞");
			break;
		case 13:
			system("cls");
			if (num == 1) {
				truth = 0;
				StartGame();
				break;
			}
			else if (num == 2) {
				Explain();
			}
		}
		if (truth == 0)
			break;
	}
}
