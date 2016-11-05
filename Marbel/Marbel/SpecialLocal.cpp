#include "player.h"
#include "start.h"
#include "draw.h"
#include "gameOver.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void BonusEvent(int i) {
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

	int select;
	char name[10];
	gotoxytext(48, 29, "������� ���á�");
	gotoxytext(48, 30, "�ڽ��� ������ ���帶ũ �Ǽ� ����! (������/���帶ũ�ΰ��� �Ұ�)");
	gotoxytext(35, 31, "1) �Ǽ� 2)���  �� ");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {

		LinkedList *list;
		if (i == 0) {
			list = list1;
		}
		else {
			list = list2;
		}

		PrintList(list);

		int cnt = 0;
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == i + 4 || local[j].state == i + 2) {
				cnt++;
			}
		}

		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				gotoxy(75, 31); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {

					if (local[node->num].state != i + 4 || local[node->num].state != i + 2) {
						k++;
						local[node->num].state = i + 2;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][i + 2]);
						if (i == 0) {
							gotoxytext(local[node->num].x, local[node->num].y - 2, "������");
						}
						else {
							gotoxytext(local[node->num].x, local[node->num].y - 2, "������");
						}

						gotoxytext(48, 33, "���帶ũ�� �������ϴ�!");
						Sleep(500);
						clrText();
					}
					else {
						clrText();
						gotoxy(48, 34); printf("�������� ���帶ũ�� �Ұ����մϴ�.");
						Sleep(700);
						clrText();
					}
				}
				else {
					clrText();
					gotoxy(48, 34); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			gotoxy(48, 34); printf("�Ǽ��� ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "�Ǽ����� �ʽ��ϴ�.");
	}

	Sleep(500);
	clrText();
}

int IslandEvent(int i) {
	int select;
	gotoxytext(48, 29, "�� ���ε� ��");
	gotoxytext(48, 30, "���ε��� �������ϴ�! Ż���� (����) �� ");
	gotoxytext(48, 31, "1) ���� ����   2) 50�� ���� ����");
	select = _getch() - 48;
	gotoxy(80, 31); printf("%d", select);
	if (select == 1) {
		gotoxy(48, 33); printf("���� ���ϴ�");
		Sleep(500);
		clrText();
		return -1;
	}
	else {
		player[i].marble -= 50;
		gotoxytext(48, 33, "50�� ������ ���� �Ǿ����ϴ�");
		player[i].state = 0;
		player[i].count = 0;
		Sleep(500);
		clrText();
		return 0;
	}
	

}

void OlympicEvent(int i) {
	int select;
	char name[10] = " ";
	gotoxytext(48, 29, "�ڿø��� ���֡�");
	gotoxytext(48, 30, "���ϴ� ������ �̸��� �Է��ϸ� ����ᰡ 2�� ~");
	gotoxytext(35, 31, "1) ���� 2)���  �� ");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {
		LinkedList *list;
		if (i == 0) {
			list = list1;
		}
		else {
			list = list2;
		}

		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				gotoxy(75, 31); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {
					k++;
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}

					local[node->num].olystate = 1;

					gotoxytext(48, 33, "����� 2�谡 ��µǾ����ϴ�!");
					Sleep(500);
					clrText();

				}
				else {
					clrText();
					gotoxy(48, 34); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			gotoxy(48, 34); printf("������ ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "�������� �ʽ��ϴ�.");
	}

	Sleep(500);
	clrText();

}

int WorldTourEvent(int i) {
	char name[10];
	int select;
	gotoxytext(48, 29, "�ڼ��� �����");
	gotoxytext(48, 30, "���ϴ� ������ �̸��� �Է��ϸ� ���迩�� ~");
	gotoxytext(48, 31, "1) ���� 2)���");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {
		if (player[i].marble <= 10) {
			gotoxytext(48, 31, "������ �����մϴ�.");
			return -1;
		}

		int cnt = 0;
		while (cnt != 0) {
			gotoxy(48, 31); scanf("%s", name);

			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					cnt++;
				}
			}

			if (cnt == 0) {
				//local[]
				gotoxy(48, 34); printf("�̵��մϴ�");
				player[i].marble -= 10;
				player[i].state = 0;
			}
			else {
				clrText();
				gotoxy(48, 34); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "�������� �ʽ��ϴ�.");
	}

	Sleep(1000);
	clrText();

}

void TaxEvent(int i) {
	int tax = 0;

	gotoxytext(48, 29, "�ڱ���û��");
	gotoxytext(48, 30, "����û �Դϴ� ������ �������ּ���");
	gotoxytext(48, 31, "(�ڽ��� ����/�ǹ� 10% ¡��)");
	for (int k = 0; k < 32; k++) {
		if (local[k].state == i || local[k].state == i + 2 || local[k].state == i + 4) {
			tax += local[k].price;
		}
	}
	tax = (0.1)*tax;
	gotoxy(70, 30); printf("����: %d ", tax);

	if (player[i].marble >= tax) {
		player[i].marble -= tax;
		Sleep(2000);
		gotoxytext(48, 33, "���� ������ �Ϸ� �Ǿ����ϴ�");
	}else{
		Bankrupt(i, tax);
	}

	PlayerState();
	Sleep(1000);
	clrText();
}
