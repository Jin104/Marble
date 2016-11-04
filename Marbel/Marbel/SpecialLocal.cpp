#include "player.h"
#include "start.h"
#include "draw.h"

extern Player player[2];
extern Local local[32];

void bonusEvent(int i) {
	int select, select2;
	int correct;
	gotoxytext(48, 29, "�� ���� ���� ���߱� ��");
	gotoxytext(48, 30, "1) �ո�  2) �޸�  (����) ��");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	srand(time(NULL));
	correct = rand() % 2 + 1;
	if (correct == 1) {
		if (correct == select) {
			gotoxytext(48, 32, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			player[i].marble += 50;
		}
		else
			gotoxytext(48, 32, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}
	else {
		if (correct == select) {
			gotoxytext(48, 32, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			player[i].marble += 50;
		}
		else
			gotoxytext(48, 33, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}

	Sleep(1000);
	clrText();
}

void StartEvent(int i) {
	if (player[i].board >= boardNum) { //?
		gotoxytext(48, 29, "�ѹ����� ���Ƽ� ������ ���޵Ǿ����ϴ�!");
		player[i].marble += 750000;
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                           ");
}

void IslandEvent(int i) {
	int select;
	if (player[i].board == 8) {
		gotoxytext(48, 29, "�ڹ��ε� Ż�� �����");
		gotoxytext(48, 30, "���ε��� �������ϴ�! Ż���� (����) �� ");
		gotoxytext(48, 31, "1) �ֻ��� ���� 3��   2) 50�� ���� ����");
		select = _getch() - 48;
		gotoxy(80, 31); printf("%d", select);
		if (select == 1) {
			Dice GameDice();
			//���ε� Ż��
		}
		else {
			player[i].marble -= 50;
			gotoxytext(48, 33, "50�� ������ ���� �Ǿ����ϴ�");
		}
		Sleep(500);
		clrText();
	}
}

void OlympicEvent(int i) {
	char name[10];
	if (player[i].board == 16) {
		gotoxytext(48, 29, "�ڿø��� ���֡�");
		gotoxytext(48, 30, "���ϴ� ������ �̸��� �Է��ϸ� ����� 2�� ~");
		gotoxytext(48, 31, "(��, �ڽ��� ������ ����): ");
		scanf("%s", name[10]);
		local[i].price *= 2;
		gotoxytext(48, 33, "����� 2�谡 ��µǾ����ϴ�!");
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                                ");
	gotoxy(48, 30);
	printf("                                                ");
	gotoxy(48, 31);
	printf("                                                ");
	gotoxy(48, 33);
	printf("                                                ");
}

void WorldTourEvent(int i) {
	char name[10];
	if (player[i].board == 24) {
		gotoxytext(48, 29, "�ڼ��� �����");
		gotoxytext(48, 30, "���ϴ� ������ �̸��� �Է��ϸ� ���迩�� ~");
		scanf("%s", name);
		while (player[i].board != 0) {
			player[i].turn = 1;
		}
		//gotoxytext(48, 32, "���� �϶� ���迩�� ����!");
		for (i = 0; i<boardNum; i++) {
			if (!strcmp(local[i].name, local->name)) { //?
			}
		}


		Sleep(1000);
		gotoxy(48, 29);
		printf("                                              ");
		gotoxy(48, 30);
		printf("                                              ");
		gotoxy(48, 32);
		printf("                                              ");
	}
}
void TaxEvent(int i) {
	int tax;
	if (player[i].board == 31) {
		gotoxytext(48, 29, "�ڱ���û��");
		gotoxytext(48, 30, "����û �Դϴ� ������ �������ּ���");
		gotoxytext(48, 31, "(�ڽ��� ����/�ǹ� 10% ¡��)");
		tax = (local[i].price) * (0.1);
		player[i].marble -= tax;
		Sleep(1000);
		gotoxytext(48, 33, "���� ������ �Ϸ� �Ǿ����ϴ�");
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                              ");
	gotoxy(48, 30);
	printf("                                              ");
	gotoxy(48, 31);
	printf("                                              ");
	gotoxy(48, 33);
	printf("                                              ");
}