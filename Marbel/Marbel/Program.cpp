#include "Start.h"

void main() {

	cursor_view(0);

	//Loading();
	Menu();

	int select, cnt = 0;
	int num = 1, truth = 1;

	while (1) {
		select = _getch();

		switch (select) {
		case 80: //아래쪽 커서키
			cnt++;
			num = 2;
			settextcolor(0x0007, 000000);
			gotoxytext(50, 28, " ");
			gotoxytext(50, 30, "☞");

			settextcolor(0, 3);
			gotoxytext(55, 30, "[2] 게임 설명");

			settextcolor(0x0007, 000000);
			gotoxytext(55, 28, "[1] 게임 시작");
			break;
		case 72: //위쪽 화살표
			cnt--;
			num = 1;
			settextcolor(0x0007, 000000);
			gotoxytext(50, 30, " ");
			gotoxytext(50, 28, "☞");

			settextcolor(0, 3);
			gotoxytext(55, 28, "[1] 게임 시작");

			settextcolor(0x0007, 000000);
			gotoxytext(55, 30, "[2] 게임 설명");
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
