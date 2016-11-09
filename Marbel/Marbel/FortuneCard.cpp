#include "Start.h"
#include "BuildEvent.h"
#include "Player.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void FortuneCard(int turn) {
	
	clrText();

	/*ī���� ȸ��*/
	for (int i = 0; i < 6; i++) {
		Sleep(30);
		DrawFortuneCard();
		Sleep(30);
		DrawFortuneCard2();
		Sleep(30);
		DrawFortuneCard();
	}

	/*1���� 7���� ������ �� ����*/
	srand(time(NULL));
	int n = 1;// rand() % 7 + 1;

	/*���¼������� �̺�Ʈ�߻�*/
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
	clrText();
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

/*����� �ݰ� ī��*/
void HalfAngelCard(int turn) {
	int select;
	gotoxytext(37, 27, "�� õ��ī�� �� - ����� �ݰ� ����");
	gotoxytext(37, 28, "1) ����  2) ������ (����) ��");
	gotoxy(70, 28);
	cursor_view(1);

	/*1�Ǵ� 2�� �Է��Ҷ�����*/
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	if (select == 1) {
		gotoxytext(37, 30, "ī�带 �����մϴ�.");
		player[turn].card = 1;		//�÷��̾��� ī����� ����
	}
	else {
		gotoxytext(37, 30, "ī�带 �����ϴ�.");
	}
	Sleep(900);
	clrText();
}

/*����� ���� ī��*/
void AngelCard(int turn) {
	int select;
	gotoxytext(37, 27, "�� õ��ī�� �� - ����� ����");
	gotoxytext(37, 28, "1) ����  2) ������ (����) ��");
	gotoxy(70, 28);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	if (select == 1) {
		gotoxytext(37, 30, "ī�带 �����մϴ�.");
		player[turn].card = 2;
	}
	else {
		gotoxytext(37, 30, "ī�带 �����ϴ�.");
	}
	Sleep(900);
	clrText();
}

/*���迩�����ΰ��� ī��*/
void InviteTravel(int turn) {
	gotoxytext(37, 27, "�� ���迩�� �ʴ�� ��");
	gotoxytext(37, 28, "������ ������ ~ ���� ��� ���迩������ �̵�!");
	Sleep(900);

	/*�÷��̾���ġ������ �̵�*/
	int now = player[turn].board;
	if (now < 24) {
		movePlayer(24 - now, turn);
	}
	else {
		movePlayer(28, turn);
	}
	player[turn].state = 2;	//�÷��̾��� ���º���
	PlayerState();
}

/*������ΰ��� ī��*/
void GoStart(int turn) {
	gotoxytext(37, 27, "�� ����� GO ��");
	gotoxytext(37, 28, "�� ���� �� ��� ~ ���� ��� ������� �̵�!");
	Sleep(900);
	clrText();
	/*�÷��̾���ġ������ �̵�*/
	int now = player[turn].board;
	movePlayer(32 - now, turn);

	StartEvent(turn);	//������̺�Ʈ ����
	PlayerState();

}

/*���ε��ΰ��� ī��*/
void GoIsland(int turn) {
	clrText();
	gotoxytext(37, 27, "�� ���ε� Ž�� ��");
	gotoxytext(37, 28, "�ʹ� �ռ����׿�.. ���� ��� ���ε��� �̵�!");
	Sleep(900);
	
	/*�÷��̾���ġ������ �̵�*/
	int now = player[turn].board;
	if (now < 8) {
		movePlayer(8 - now, turn);
	}
	else {
		movePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 1;	//�÷��̾���� ����
	clrText();
	PlayerState();
}

/*�ø������ΰ��� ī��*/
void HoldOlympic(int turn) {
	gotoxytext(37, 27, "�� �ø��� ���� ��");
	gotoxytext(37, 28, "�ø��� ��� ����!!! ���ϴ� ���� �ø��� ����");
	Sleep(900);
	clrText();
	OlympicEvent(turn);	//�ø��Ȱ����̺�Ʈ ����
}

/*�����Ű� ī��*/
void CompelSale(int turn) {
	int select, count = 0;
	char name[10];
	gotoxytext(38, 27, "�� ���� �Ű� ��");
	gotoxytext(38, 28, "���ϴ� ����� ���ø� ������ �Ű� (���帶ũ ���ݺҰ�)");
	gotoxytext(38, 29, "1) �Ű�  2) ������ (����) ��"); 

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
		if (turn == 0)
			list = list2;
		else
			list = list1;

		/*������ ������������ ���帶ũ�� �� ���� 0�̸� �Ű��Ұ�*/
		if (list->size - list->size2 < 1) {
			clrText();
			gotoxytext(40, 28, "�Ű��� ������ �����ϴ�.");
			Sleep(900);
			return;
		}

		/*�����̸��� ����� �Է��Ҷ�����*/
		for(int k=0;k<1;){
			clrText();
			gotoxytext(38, 27, "�Ű��� ���� �̸��� �Է����ּ���");
			gotoxytext(38, 29, "��  ");
			cursor_view(1);
			gotoxy(44, 29);
			scanf("%s", name);
			cursor_view(0);
			Node *node = FindNode(list, name);

			/*�Է��� ���ð� ���ų�, ���帶ũ�� ���� �Ű� �Ұ�*/
			if (node != NULL && local[node->num].state != 2 && local[node->num].state != 3) {
				count++;
				k++;
				local[node->num].state = -1;	//������ ���¸� �⺻���� ����
				player[1 - turn].marble += node->price / 2;	//���濡�� �Ű��� ���� ��
				gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");	//�ǹ��׸� ����
				deletNode(list, name);	//������ ����Ʈ���� ������� ����
			}
			else {
				gotoxytext(38, 31, "�ٽ� �Է����ּ���");
				gotoxytext(38, 32, "�������� ���� ���ó� ���帶ũ�� ������ �Ұ��� �մϴ�");
				Sleep(800);
			}
		}
	}
	else {
		clrText();
		gotoxytext(40, 28, "ī�带 �����ϴ�");
		Sleep(900);
	}

}


/*õ��ī�� ����*/
int DoAngel(int turn, int price) {
	int select;
	Sleep(500);
	if (player[turn].card == 1) {
		gotoxytext(37, 27, "����� �ݰ� ���� ī�尡 �����Ǿ��ֽ��ϴ�.");
	}
	else {
		gotoxytext(37, 27, "����� ���� ī�尡 �����Ǿ��ֽ��ϴ�.");
	}
	gotoxytext(37, 28, "������ ī�带 ����Ͻðڽ��ϱ�?");
	gotoxytext(37, 29, "1) ���  2) �̻�� (����) �� ");

	gotoxy(70, 29);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);
	clrText();
	if (select == 1) {
		gotoxytext(37, 32, "ī�带 ����մϴ�.");
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		clrText();
		return price;
	}
	else {
		gotoxytext(37, 31, "������� �ʽ��ϴ�.");
	}
	Sleep(900);
	clrText();
}