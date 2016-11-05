#include "player.h"
#include "buildEvent.h"
#include "start.h"
#include "draw.h"

extern LinkedList *list1, *list2;   //�÷��̾�1,2�� �������� ���Ḯ��Ʈ
extern Player player[2];
extern Local local[32];

int SellBuilding(int turn, int price) {

	LinkedList *list;
	if (turn == 0) { list = list1;}
	else { 	list = list2; }

	char name[10];
	
	while (price > player[turn].marble) {

		clrText();
		clrList();
		gotoxytext(34, 29, "�Ű����� �����Դϴ�.");
		PrintList(list);
		gotoxy(34, 30);
		printf("������ ����: %d  �Ű��� �����̸��� �Է����ּ���.", price- player[turn].marble);
		gotoxy(34, 31);
		scanf("%s", name);
		int cnt = 0;
		Node *node = FindNode(list, name);

		if (node != NULL) {

			int money = node->price / 2;

			gotoxy(34, 37); printf("list->size : %d", list->size);	//�ӽ�
			local[node->num].state = -1;
			gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");
			deletNode(list, name);	//������
			gotoxy(34, 38); printf("list->size : %d", list->size);	//�ӽ�
			player[turn].marble += money;
			PlayerState();
			if (list->size < 1) {
				gotoxytext(34, 31, "���̻� �Ű��Ұǹ��� �����ϴ�.");
				Sleep(700);
				return -1;
			};
		}
		else {
			gotoxy(34, 31);
			printf("�ٽ� �Է����ּ���.");
			Sleep(500);
			gotoxy(34, 31);
			printf("                  ");
			gotoxy(34, 31);
		}
	}
	player[turn].marble -= price;
	player[1 - turn].marble += price;
	PlayerState();
	return 0;

}

void Bankrupt(int turn, int price) {
	LinkedList *list;
	if (turn == 0) {
		list = list1;
	}
	else {
		list = list2;
	}

	int answer;
	gotoxytext(34, 31, "����ᰡ �����մϴ�.\n");
	gotoxy(48, 31);
	printf("1) �Ű�  2) �Ļ�  (����) �� ");
	answer = _getch() - 48;
	gotoxy(80, 31); printf("%d", answer);

	if (answer == 1) {
		if (SellBuilding(turn, price) == -1) {
			clrText();
			gotoxytext(34, 30, "��� �ǹ��� �Ű��ص� �����մϴ�.");
			gotoxytext(34, 31, "�Ļ�!!!!");
			getchar();
			exit(1);
		}
		else {
			gotoxytext(34, 32, "�Ű��� �Ϸ��߽��ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(34, 31, "�Ļ�!!!!");
		exit(1);
	}
}

void TouristMonop(int turn) {
	int cnt = 0;
	for (int i = 0; i < boardNum; i++) {
		if (local[i].state == 4) {
			cnt++;
		}
	}
	if (cnt == 5) {
		clrText();
		
		gotoxy(35, 30); printf("%s���� ���������� �¸�!", player[turn].name);
			
		exit(1);
	}
}

void ColorMonop(int turn) {
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
	int color = 0;
	
	//local[1].state
}

void LineMonop(int turn) {

	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	for (int i = 1; i < 8; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt1++;
		}
	}

	for (int i = 9; i < 16; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt2++;
		}
	}

	for (int i = 17; i < 24; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt3++;
		}
	}

	for (int i = 25; i < 32; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt4++;
		}
	}
	if (cnt1 == 6 || cnt2 == 6 || cnt3 == 6 || cnt4 == 5) {
		clrText();
		gotoxy(35, 30); printf("%s���� ���ε��� �¸�!", player[turn].name);
		exit(1);
	}


}

void CheckGameOver(int turn) {
	TouristMonop(turn);
	ColorMonop(turn);
	LineMonop(turn);
}