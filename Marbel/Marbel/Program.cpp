#include "Start.h"
#include "Graphics.h"
//����
//���� �޴� ����Ű
void main() {

	//Ŀ�� ����
	cursor_view(0);
	sndPlaySoundA("..\\sound\\Modoo Marble Zion-T AR new_44k_16b.wav", SND_ASYNC | SND_NODEFAULT);
	Loading();
	Menu();

	int select, num = 1;

	while (1) {
		select = _getch();

		switch (select) {
		case 80: //�Ʒ��� Ŀ��Ű
			num = 2;
			settextcolor(0x0007, 000000);
			gotoxytext(50, 28, " ");
			gotoxytext(50, 30, "��");

			settextcolor(0, 3);
			gotoxytext(55, 30, "[2] ���� ����");

			settextcolor(0x0007, 000000);
			gotoxytext(55, 28, "[1] ���� ����");
			break;
		case 72: //���� Ŀ��Ű
			num = 1;
			settextcolor(0x0007, 000000);
			gotoxytext(50, 30, " ");
			gotoxytext(50, 28, "��");

			settextcolor(0, 3);
			gotoxytext(55, 28, "[1] ���� ����");

			settextcolor(0x0007, 000000);
			gotoxytext(55, 30, "[2] ���� ����");
			break;
		case 13:
			system("cls");
			if (num == 1) {
				StartGame();
			}
			else if (num == 2) {
				Explain();
			}
		}
	}
}
