#include "player.h"
#include "buildEvent.h"
#include "start.h"
#include "draw.h"

extern LinkedList *list1, *list2;   //�÷��̾�1,2�� �������� ���Ḯ��Ʈ
extern Player player[2];
extern Local local[32];

//price = localPrice[board][2];
//marble = player[turn].marble;

int SellBuilding(int turn, int price) {
	//player 2�϶� (turn:1)
	LinkedList *list;
	if (turn == 0) { list = list1;}
	else { 	list = list2; }

	int marble = player[turn].marble;
	int cost = price - marble;
	char name[10];
	
	while (price > cost) {
		clrText();
		clrList();
		//gotoxytext(34, 30, "������ �����Դϴ�.");
		PrintList(list2);
		gotoxy(34, 30);
		printf("������ ����: %d  �Ű��� �����̸��� �Է����ּ���.", cost);
		gotoxy(34, 31);
		scanf("%s", name);
		int cnt = 0;
		Node *node = FindNode(list, name);
		/*while (node != NULL) {
			cnt++;
			if (cnt > 0) {
				gotoxy(34, 31);
				printf("�ٽ� �Է����ּ���.");
				Sleep(500);
				gotoxy(34, 31);
				printf("                  ");
			}
			gotoxy(34, 31);
			scanf("%s", name);
		}*/

		int money = node->price / 2;
		deletNode(list, name);	//������
		local[node->num].state = -1;
		free(node);
		player[turn].marble += money;
		if (list->size == 0) { return -1; };
	}
	player[turn].marble -= marble - price;
	player[1 - turn].marble += price;
	//gotoxytext(34, 32, "�Ű��� �Ϸ��߽��ϴ�.");
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
		if (list->size <= 0) {
			clrText();
			gotoxytext(34, 30, "�Ű��� ������ �����ϴ�.");
			gotoxytext(34, 31, "�Ļ�!!!!");
			exit(1);
		}
		else if (SellBuilding(turn, price) == -1) {
			clrText();
			gotoxytext(34, 30, "��� �ǹ��� �Ű��ص� �����մϴ�.");
			gotoxytext(34, 31, "�Ļ�!!!!");
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