#include "Start.h"
#include "BuildEvent.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];

void FortuneCard(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

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
	int n = rand() % 7 + 1;

	/*���¼������� �̺�Ʈ�߻�*/
	switch (n)
	{
	case 1:
		if (isServer)
			HalfAngelCard(turn, playerTurn, socks, true);
		else
			HalfAngelCard(turn, playerTurn, socks, false);
		break;
	case 2:
		if (isServer)
			AngelCard(turn, playerTurn, socks, true);
		else
			AngelCard(turn, playerTurn, socks, false);
		break;
	case 3:
		InviteTravel(turn, playerTurn);
		break;
	case 4:
		if(isServer)
			GoStart(turn, board, playerTurn, socks, true, list);
		else
			GoStart(turn, board, playerTurn, socks, false, list);
		break;
	case 5:
		GoIsland(turn);
		break;
	case 6:
		if (isServer)
			HoldOlympic(turn, playerTurn, socks, true, list);
		else
			HoldOlympic(turn, playerTurn, socks, false, list);
		break;
	case 7:
		if (isServer)
			CompelSale(turn, playerTurn, socks, true);
		else
			CompelSale(turn, playerTurn, socks, false);
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
void HalfAngelCard(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	gotoxytext(37, 27, "�� õ��ī�� �� - ����� �ݰ� ����");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardGet_A01.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 30, "ī�带 �����մϴ�.");
		}
		player[turn].card = 1;		//�÷��̾��� ī����� ����
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 30, "ī�带 �����ϴ�.");
	}
	Sleep(900);
	clrText();
}

/*����� ���� ī��*/
void AngelCard(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	gotoxytext(37, 27, "�� õ��ī�� �� - ����� ����");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardGet_A01.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 30, "ī�带 �����մϴ�.");
		}
		player[turn].card = 2;		//�÷��̾��� ī����� ����
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 30, "ī�带 �����ϴ�.");
	}
	Sleep(900);
	clrText();
}

/*���迩�����ΰ��� ī��*/
void InviteTravel(int turn, int playerTurn) {
	
	gotoxytext(37, 27, "�� ���迩�� �ʴ�� ��");
	gotoxytext(37, 28, "������ ������ ~ ���� ��� ���迩������ �̵�!");
	Sleep(900);

	/*�÷��̾���ġ������ �̵�*/
	int now = player[turn].board;
	if (now < 24) {
		MovePlayer(24 - now, turn);
	}
	else {
		MovePlayer(28, turn);
	}
	player[turn].state = 2;	//�÷��̾��� ���º���
	PlayerState();
}

/*������ΰ��� ī��*/
void GoStart(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

	gotoxytext(37, 27, "�� ����� GO ��");
	gotoxytext(37, 28, "�� ���� �� ��� ~ ���� ��� ������� �̵�!");

	Sleep(900);
	clrText();
	/*�÷��̾���ġ������ �̵�*/
	int now = player[turn].board;
	MovePlayer(32 - now, turn);

	if (isServer)
		StartEvent(turn, board, playerTurn, socks, true, list);
	else
		StartEvent(turn, board, playerTurn, socks, false, list);

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
		MovePlayer(8 - now, turn);
	}
	else {
		MovePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 1;	//�÷��̾���� ����
	clrText();
	PlayerState();
}

/*�ø������ΰ��� ī��*/
void HoldOlympic(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	gotoxytext(37, 27, "�� �ø��� ���� ��");
	gotoxytext(37, 28, "�ø��� ��� ����!!! ���ϴ� ���� �ø��� ����");
	
	Sleep(900);
	clrText();
	OlympicEvent(turn, playerTurn, socks, isServer, list);	//�ø��Ȱ����̺�Ʈ ����
}

/*�����Ű� ī��*/
void CompelSale(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1,select2, count = 0;
	char data[2];
	char name[10];

	gotoxytext(38, 27, "�� ���� �Ű� ��");
	gotoxytext(38, 28, "���ϴ� ����� ���ø� ������ �Ű� (���帶ũ ���ݺҰ�)");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		
		if (turn == playerTurn) {

			gotoxytext(38, 28, "���° �÷��̾��� ������ �Ű��ұ��?");
			gotoxy(70, 29);
			cursor_view(1);

			do {
				select = _getch() - 48;
				gotoxyint(70, 29, select);
				gotoxytext(70, 29, "      ");

			} while (select != 1 && select != 2 && select != 3 && select != 4);
			cursor_view(0);
			gotoxyint(70, 29, select);
			clrText();
			itoa(select, data, 10);

			if (isServer)
			{
				SendMsg(data, sizeof(data), 0);
			}
			else
			{
				send((SOCKET)socks, data, sizeof(data), 0);
			}
			select2 = atoi(data);
		}
		else
		{
			if (isServer)
			{
				SOCKET *sockArr = (SOCKET *)socks;
				while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
				SendMsg(data, sizeof(data), turn);
			}
			else
			{
				while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
			}
			select2 = atoi(data);
		}

		LinkedList *list;
		if (select2 == 0)
			list = list1;
		else if (select2 == 1)
			list = list2;
		else if (select2 == 2)
			list = list3;
		else
			list = list4;

		/*������ ������������ ���帶ũ�� �� ���� 0�̸� �Ű��Ұ�*/
		if (list->size - list->size2 < 1) {
			clrText();
			if(turn==playerTurn)
				gotoxytext(38, 28, "�Ű��� ������ �����ϴ�.");
			Sleep(900);
			return;
		}
		if (turn == playerTurn)
			sndPlaySoundA("..\\sound\\ChanceCardAtt_A01.wav", SND_ASYNC | SND_NODEFAULT);
		/*�����̸��� ����� �Է��Ҷ�����*/
		for (int k = 0; k<1;) {
			clrText();

			if (turn == playerTurn) {
				gotoxytext(38, 27, "�Ű��� ���� �̸��� �Է����ּ���");
				gotoxytext(38, 29, "��  ");
				cursor_view(1);
				gotoxy(44, 29);
				scanf("%s", name);
				cursor_view(0);

				if (isServer)
				{
					SendMsg(name, sizeof(name), 0);
				}
				else
				{
					send((SOCKET)socks, name, sizeof(name), 0);
				}
			}
			else
			{
				if (isServer)
				{
					SOCKET *sockArr = (SOCKET *)socks;
					while (recv(sockArr[turn], name, sizeof(name), 0) <= 0);
					SendMsg(name, sizeof(name), turn);
				}
				else
				{
					while (recv((SOCKET)socks, name, sizeof(name), 0) <= 0);
				}
			}

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
				if (turn == playerTurn) {
					gotoxytext(38, 31, "�ٽ� �Է����ּ���");
					gotoxytext(38, 32, "�������� ���� ���ó� ���帶ũ�� ������ �Ұ��� �մϴ�");
				}
				Sleep(800);
			}
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(40, 28, "ī�带 �����ϴ�");
		Sleep(900);
	}

}

/*õ��ī�� ����*/
int DoAngel(int turn, int price, int playerTurn, void *socks, bool isServer) {
	int select,select1;
	char data[2];
	Sleep(500);

	if (turn == playerTurn) {
		sndPlaySoundA("..\\sound\\ChanceCardUsePop_A01.wav", SND_ASYNC | SND_NODEFAULT);
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
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);

	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardataef_A03.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 32, "ī�带 ����մϴ�.");
		}
		/*ī�� ������ ���� ����� ����*/
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		clrText();
		return price;
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 31, "������� �ʽ��ϴ�.");
	}
	Sleep(900);
	clrText();
}