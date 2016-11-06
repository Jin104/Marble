#include "player.h"
#include "Start.h"
#include "BuildEvent.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void BonusEvent(int i) {
	int select, select2;
	int correct;
	gotoxytext(37, 27, "�� ���� ���� ���߱� ��");
	gotoxytext(37, 28, "1) �ո�  2) �޸�  (����) ��");
	select = _getch() - 48;
	gotoxy(73, 28); printf("%d", select);
	srand(time(NULL));
	correct = rand() % 2 + 1;
	if (correct == 1) {
		if (correct == select) {
			gotoxytext(37, 30, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			player[i].marble += 50;
		}
		else
			gotoxytext(37, 30, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}
	else {
		if (correct == select) {
			gotoxytext(37, 30, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			player[i].marble += 50;
		}
		else
			gotoxytext(37, 30, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}

	Sleep(800);
	clrText();
}

void StartEvent(int i) {

	int select;
	char name[10];
	gotoxytext(37, 27, "�� ����� ���� ��");
	gotoxytext(37, 28, "�ڽ��� ������ ���帶ũ �Ǽ� ����!");
	gotoxytext(37, 29, "1) �Ǽ� 2)���  (����) �� ");
	select = _getch() - 48;
	gotoxy(73, 29); printf("%d", select);

	if (select == 1) {

		LinkedList *list;
		if (i == 0) 
			list = list1;
		else
			list = list2;

		PrintList(list);

		int cnt = 0;
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == i + 4 || local[j].state == i + 2) {
				cnt++;
			}
		}

		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				gotoxy(73, 27); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {

					if (local[node->num].state != i + 4 && local[node->num].state != i + 2) {
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
						gotoxy(37, 31); printf("�������� ���帶ũ�� �Ұ����մϴ�.");
						Sleep(700);
						clrText();
					}
				}
				else {
					clrText();
					gotoxy(37, 31); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			gotoxy(37, 28); printf("�Ǽ��� ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 28, "�Ǽ����� �ʽ��ϴ�.");
	}

	Sleep(500);
	clrText();
	clrList();
}

int IslandEvent(int i) {
	int select;
	gotoxytext(37, 27, "�� ���ε� ��");
	gotoxytext(37, 28, "���ε��� �������ϴ�! Ż���� (����) �� ");
	gotoxytext(37, 29, "1) ���� ����   2) 50�� ���� ����");
	select = _getch() - 48;
	gotoxy(78, 28); printf("%d", select);
	if (select == 1) {
		gotoxy(37, 31); printf("���� ���ϴ�");
		Sleep(500);
		clrText();
		return -1;
	}
	else {
		player[i].marble -= 50;
		gotoxytext(37, 31, "50�� ������ ���� �Ǿ����ϴ�");
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
	gotoxytext(37, 27, "�� �ø��� ���� ��");
	gotoxytext(37, 28, "���ϴ� ������ �̸��� �Է��ϸ� ����ᰡ 2�� ~");
	gotoxytext(37, 29, "1) ���� 2)���  �� ");
	select = _getch() - 48;
	gotoxy(73, 29); printf("%d", select);

	if (select == 1) {

		LinkedList *list;
		if (i == 0)
			list = list1;
		else
			list = list2;

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

					gotoxytext(37, 32, "����� 2�谡 ��µǾ����ϴ�!");
					Sleep(500);
					clrText();

				}
				else {
					clrText();
					gotoxy(37, 31); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			gotoxy(37, 28); printf("������ ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 28, "�������� �ʽ��ϴ�.");
	}

	Sleep(500);
	clrText();

}

int WorldTourEvent(int i) {
	char name[10];
	int select;
	gotoxytext(37, 27, "�� ���� ���� ��");
	gotoxytext(37, 28, "���ϴ� ������ �̸��� �Է��ϸ� ���迩�� ~");
	gotoxytext(37, 29, "1) ���� 2)��� ��");
	select = _getch() - 48;
	gotoxy(73, 31); printf("%d", select);
	if (select == 1) {
		clrText();
		if (player[i].marble < 10) {
			gotoxytext(37, 33, "������ �����մϴ�.");
			return -1;
		}

		int cnt = 0;
		for (int k = 0; k < 1;) {
			int n;
			gotoxytext(37, 29, "������ ���� �Է��ϼ���  ��");
			cursor_view(1);
			gotoxy(37, 29); scanf("%s", name);
			cursor_view(0);

			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					if (j == 12) {
						for (int m = 0; m < 1;) {
							gotoxytext(37, 32, "���° ����ī��� �����? ��");
							int k;
							gotoxy(80, 32); scanf("%d", &k);
							switch (k)
							{
							case 1:
								m++;
								n = 12;
								break;
							case 2:
								m++;
								n = 20;
								break;
							case 3:
								m++;
								n = 28;
								break;
							default:
								gotoxytext(37, 33, "�߸��Է��ϼ̽��ϴ�.");
								Sleep(500);
								clrText();
								break;
							}
						}

					}else{
						n = j;
					}
					cnt++;
					break;
				}
			}
			if (cnt > 0) {
				clrText();
				gotoxy(37, 33); printf("�̵��մϴ�");
				k++;
				player[i].marble -= 10;
				player[i].state = 0;
				int move;
				if (n == 12 || n == 20 || n == 28) {
					
				}
				if (n > 24) {
					move = n - 24;
				}else{
					move = n + 8;
				}
				movePlayer(move, i);
				BuildingEvent(i, player[i].board);
			}
			else {
				clrText();
				gotoxy(37, 33); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		gotoxytext(37, 33, "�������� �ʽ��ϴ�.");
		return -1;
	}

	Sleep(1000);
	clrText();

}

void TaxEvent(int i) {
	int tax = 0;

	gotoxytext(37, 27, "�� ����û ��");
	gotoxytext(37, 28, "����û �Դϴ� ������ �������ּ���");
	gotoxytext(37, 29, "[�ڽ��� ����/�ǹ� 10% ¡��]");
	for (int k = 0; k < 32; k++) {
		if (local[k].state == i || local[k].state == i + 2 || local[k].state == i + 4) {
			tax += local[k].price;
		}
	}

	tax = (0.1)*tax;
	gotoxy(70, 30); printf("������ %d ���� �Դϴ�", tax);

	if (player[i].marble >= tax) {
		player[i].marble -= tax;
		Sleep(1000);
		gotoxytext(37, 32, "���� ������ �Ϸ� �Ǿ����ϴ�");
	}
	else {
		Bankrupt(i, tax);
	}

	PlayerState();
	Sleep(500);
	clrText();
}
