#include "player.h"
#include "Start.h"
#include "BuildEvent.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void BonusEvent(int i) {

	int select, correct;
	gotoxytext(37, 27, "�� ���� ���� ���߱� ��");
	gotoxytext(37, 28, "1) �ո�  2) �޸�  (����) ��");
	
	gotoxy(70, 28);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

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

/*����� �Ǽ� �̺�Ʈ*/
void StartEvent(int i) {

	int select;
	char name[10];
	gotoxytext(37, 27, "�� ����� ���� ��");
	gotoxytext(37, 28, "�ڽ��� ������ ���帶ũ �Ǽ� ����!");
	gotoxytext(37, 29, "1) �Ǽ� 2)���  (����) �� ");
	
	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);

	if (select == 1) {

		LinkedList *list;
		if (i == 0) 
			list = list1;
		else
			list = list2;

		PrintList(list);

		int cnt = 0;
		/*������ ȣ�ڰ� ���帶ũ�� ��*/
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == i + 4 || local[j].state == i + 2) {
				cnt++;
			}
		}

		/*������ �ǹ��� ���� ������*/
		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				gotoxytext(37, 28, "���帶ũ�� ���� �ǹ��� �Է��ϼ���. (������ �Ұ�)");
				gotoxy(38, 28); 
				scanf("%s", name);
				Node *node = FindNode(list, name);
				
				/*�����ϳ� ������ �Է��Ҷ�*/
				if (node != NULL) {

					/*������ ���°� ���帶ũ�� �ƴҶ�*/
					if (local[node->num].state != i + 4 && local[node->num].state != i + 2) {
						k++;
						local[node->num].state = i + 2;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][i + 2]);
						if (i == 0)
							PLAYER1
						else
							PLAYER2
						
						gotoxytext(local[node->num].x, local[node->num].y - 2, "������");
						gotoxytext(37, 33, "���帶ũ�� �������ϴ�!");
						Sleep(500);
						clrText();
					}
					else {
						gotoxy(37, 33); printf("�������� ���帶ũ�� �Ұ����մϴ�.");
						Sleep(700);
						clrText();
					}
				}
				else {
					gotoxy(37, 33); printf("���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
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

	Sleep(900);
	clrText();
	clrList();
}

/*���ε�*/
int IslandEvent(int i) {
	int select;
	gotoxytext(37, 27, "�� ���ε� ��");
	gotoxytext(37, 28, "���ε��� �������ϴ�! Ż���� (����) �� ");
	gotoxytext(37, 29, "1) ���� ����   2) 50�� ���� ����");

	gotoxy(80, 28);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);


	if (select == 1) {
		gotoxy(37, 31); 
		printf("���� ���ϴ�");
		Sleep(900);
		clrText();
		return -1;
	}
	else {
		player[i].marble -= 50;
		gotoxytext(37, 31, "50�� ������ ���� �Ǿ����ϴ�");
		player[i].state = 0;
		player[i].count = 0;
		Sleep(900);
		clrText();
		return 0;
	}


}

/*�ø���*/
void OlympicEvent(int i) {
	int select;
	char name[10];
	gotoxytext(37, 27, "�� �ø��� ���� ��");
	gotoxytext(37, 28, "���ϴ� ������ �̸��� �Է��ϸ� ����ᰡ 2�� ~");
	gotoxytext(37, 29, "1) ���� 2)���  �� ");
	
	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);


	if (select == 1) {

		LinkedList *list;
		if (i == 0)
			list = list1;
		else
			list = list2;

		PrintList(list);
		/*���������� ������*/
		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				gotoxytext(37, 27, "������ �̸��� �Է��ϼ��� �� ");
				gotoxy(70, 27); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {
					k++;
					/*�ٸ������� �ø��Ȼ��¸� ����*/
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}
					/*�Է��������� �ø��Ȱ���*/
					local[node->num].olystate = 1;

					gotoxytext(37, 32, "����� 2�谡 ��µǾ����ϴ�!");
					Sleep(900);
					clrText();

				}
				else {
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

	Sleep(900);
	clrText();

}

/*���迩��*/
int WorldTourEvent(int i) {
	char name[10];
	int select;
	gotoxytext(37, 27, "�� ���� ���� ��");
	gotoxytext(37, 28, "���ϴ� ������ �̸��� �Է��ϸ� ���迩�� ~");
	gotoxytext(37, 29, "1) ���� 2)��� ��");

	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);

	if (select == 1) {
		clrText();
		if (player[i].marble < 10) {
			gotoxytext(37, 33, "������ �����մϴ�.");
			return -1;
		}

		int cnt = 0;
		for (int k = 0; k < 1;) {
			int n;
			clrText();
			gotoxytext(37, 29, "������ ���� �Է��ϼ���  ��");
			gotoxy(70, 29); 
			cursor_view(1); 
			scanf("%s", name);
			cursor_view(0);
			
			/*�Է��Ѱ� ����ʿ� �ִ���*/
			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					/*����ī�� �Է½�*/
					if (j == 12) {
						for (int m = 0; m < 1;) {
							gotoxytext(37, 32, "���° ����ī��� �����? ��");
							int k;
							gotoxy(70, 32); scanf("%d", &k);
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
				gotoxytext(37, 33, "�̵��մϴ�");
				k++;
				player[i].marble -= 10;
				player[i].state = 0;
				int move;
				
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

	Sleep(900);
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
	Sleep(900);
	clrText();
}
