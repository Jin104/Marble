#include "draw.h"
#include "fortuneCard.h"
#include "specialLocal.h"
#include "player.h"
#include "start.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void FortuneCard(int turn) {
	
	clrText();

	for (int i = 0; i < 6; i++) {
		Sleep(50);
		DrawFortuneCard();
		Sleep(50);
		DrawFortuneCard2();
	}

	srand(time(NULL));
	int n = 1;// rand() % 7 + 1;

	switch (n)
	{
	case 1:
		HalfAngelCard(turn);
		break;
	case 2:
		AngelCard(turn);
		break;
	case 3:
		InviteTravel(turn);
		break;
	case 4:
		GoStart(turn);
		break;
	case 5:
		GoIsland(turn);
		break;
	case 6:
		HoldOlympic(turn);
		break;
	case 7:
		CompelSale(turn);
		break;
	default:
		break;
	}

	//Sleep(700);
	clrText();
	//getchar();
	clrCard();
}

void DrawFortuneCard() {
	gotoxy(112, 16); printf("��������������");
	gotoxy(112, 17); printf("��          ��");
	gotoxy(112, 18); printf("��  �ڡڡ�  ��");
	gotoxy(112, 19); printf("�� ��    �� ��");
	gotoxy(112, 20); printf("��     ��   ��");
	gotoxy(112, 21); printf("��    ��    ��");
	gotoxy(112, 22); printf("��          ��");
	gotoxy(112, 23); printf("��    ��    ��");
	gotoxy(112, 24); printf("��          ��");
	gotoxy(112, 25); printf("��������������");
}

void DrawFortuneCard2() {
	gotoxy(112, 16); printf("��������������");
	gotoxy(112, 17); printf("��          ��");
	gotoxy(112, 18); printf("��  �١١�  ��");
	gotoxy(112, 19); printf("�� ��    �� ��");
	gotoxy(112, 20); printf("��   ��     ��");
	gotoxy(112, 21); printf("��    ��    ��");
	gotoxy(112, 22); printf("��          ��");
	gotoxy(112, 23); printf("��    ��    ��");
	gotoxy(112, 24); printf("��          ��");
	gotoxy(112, 25); printf("��������������");
}

void HalfAngelCard(int turn) {
	int select;
	gotoxytext(48, 30, "�� õ��ī�� ��");
	gotoxytext(48, 31, "����� �ݰ� ����");
	gotoxytext(48, 32, "1) ����  2) ������ (����) ��");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {
		gotoxytext(48, 33, "ī�带 �����մϴ�.");
		player[turn].card = 1;		
	}
	else {
		gotoxytext(48, 33, "ī�带 �����ϴ�.");
	}
	Sleep(700);
	clrText();
}

void AngelCard(int turn) {
	int select;
	gotoxytext(48, 30, "�� õ��ī�� ��");
	gotoxytext(48, 31, "����� ����");
	gotoxytext(48, 32, "1) ����  2) ������ (����) ��");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {
		gotoxytext(48, 33, "ī�带 �����մϴ�.");
		player[turn].card = 2;
	}
	else {
		gotoxytext(48, 33, "ī�带 �����ϴ�.");
	}
}

void InviteTravel(int turn) {
	gotoxytext(48, 30, "�� ���迩�� �ʴ�� ��");
	gotoxytext(35, 31, "������ ������ ~ ���� ��� ���迩������ �̵�!");
	Sleep(700);
	int now = player[turn].board;
	
	if (now < 24) {
		movePlayer(24 - now, turn);
	}
	else {
		movePlayer(28, turn);
	}
	player[turn].state = 3;	//�����Ͽ� �̵��ϴ°Ŵϱ�
	PlayerState();
}

void GoStart(int turn) {
	gotoxytext(48, 30, "�� ����� GO ��");
	gotoxytext(35, 31, "�� ���� �� ��� ~ ���� ��� ������� �̵�!");
	Sleep(700);

	int now = player[turn].board;
	movePlayer(32 - now, turn);

	StartEvent(turn);
	PlayerState();

}

void GoIsland(int turn) {
	clrText();
	gotoxytext(48, 30, "�� ���ε� Ž�� ��");
	gotoxytext(35, 31, "�ʹ� �ռ����׿�.. ���� ��� ���ε��� �̵�!");
	Sleep(700);
	
	int now = player[turn].board;

	if (now < 8) {
		movePlayer(8 - now, turn);
	}
	else {
		movePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 2;
	clrText();
	PlayerState();
}

void HoldOlympic(int turn) {
	gotoxytext(48, 30, "�� �ø��� ���� ��");
	gotoxytext(35, 31, "�ø��� ��� ����!!! ���ϴ� ���� �ø��� ����");
	Sleep(500);
	clrText();
	OlympicEvent(turn);
}

//void ChangeLocal(int turn) {
//
//	gotoxytext(48, 43, "�� ���� ü���� ��");
//	gotoxytext(48, 44, "���ϴ� ����� ���ÿ� �� ���ø� �±�ȯ (���帶ũ �Ǽ��� ���� ���ݺҰ�)");
//
//}

void CompelSale(int turn) {
	int select, count = 0;
	char name[10];
	gotoxytext(48, 30, "�� ���� �Ű� ��");
	gotoxytext(35, 31, "���ϴ� ����� ���ø� ������ �Ű� (���帶ũ ���ݺҰ�)");
	gotoxytext(48, 32, "1) �Ű�  2) ������ (����) ��");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {

		LinkedList *list;
		if (turn == 0) { list = list2; }
		else { list = list1; }

		if (list->size - list->size2 < 1) {
			clrText();
			gotoxy(48, 30); printf("list->size : %d", list->size);
			gotoxy(48, 31); printf("list->size : %d", list->size2);
			gotoxytext(35, 32, "�Ű��� ������ �����ϴ�.");
			Sleep(500);
			return;
		}
		for(int k=0;k<1;){
			clrText();
			gotoxytext(35, 32, "�Ű��� ���� �̸��� �Է����ּ���");
			gotoxy(35, 33);
			scanf("%s", name);
			Node *node = FindNode(list, name);

			if (node != NULL && local[node->num].state != 2 && local[node->num].state != 3) {
				count++;
				k++;
				local[node->num].state = -1;
				player[1 - turn].marble += node->price / 2;
				gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");
				deletNode(list, name);
			}
			else {
				gotoxytext(35, 34, "�ٽ� �Է����ּ���.");
				gotoxytext(35, 35, "�������� ���� ���ó� ���帶ũ�� ������ �Ұ��� �մϴ�.");
				Sleep(500);
			}
		}
	}
	else {
		gotoxytext(48, 33, "ī�带 �����ϴ�.");
	}

}



int DoAngel(int turn, int price) {
	int select;
	if (player[turn].card == 1) {
		gotoxy(34, 30); printf("����� �ݰ� ���� ī�尡 �����Ǿ��ֽ��ϴ�.");
	}
	else {
		gotoxy(34, 30); printf("����� ���� ī�尡 �����Ǿ��ֽ��ϴ�.");
	}
	gotoxytext(34, 31, "������ ī�带 ����Ͻðڽ��ϱ�?");
	gotoxytext(34, 32, "1) ���  2) �̻�� (����) ��");
	select = _getch() - 48;
	gotoxy(70, 32); printf("%d", select);
	if (select == 1) {
		gotoxytext(34, 33, "ī�带 ����մϴ�.");
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		return price;
	}
	else {
		gotoxytext(34, 34, "������� �ʽ��ϴ�.");
	}
	Sleep(500);
	clrText();
}