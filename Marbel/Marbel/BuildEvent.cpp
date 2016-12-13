#include "Player.h"
#include "BuildEvent.h"
#include "Start.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];
extern int tNum;
char data[2];
void BuildingEvent(int turn, int board, int playerTurn, void *socks, bool isServer) {

	/*
	turn=> ���� �÷��̾� ��ȣ		0:player1  1:player2  2:player3  3:player4
	borad=> �÷��̾�ִ� ������ȣ
	state=> ������ ���Ż���
	-1: �������    0~3�� �÷��̾��� ȣ��     4~7�� �÷��̾��� ���帶ũ     8~11�� �÷��̾��� ������
	board=> ������ Ư����   0���� 2���ʽ����� 4,9,14,18,25������ 8���ε� 12,20,28����ī�� 16�ø��� 24���迩�� 30����û
	*/

	int select;
	int select1;
	int state = local[board].state;

	LinkedList *list;
	if (turn == 0)
		list = list1;
	else if(turn == 1)
		list = list2;
	else if (turn == 2)
		list = list3;
	else
		list = list4;

	switch (board)
	{
	case 0:	//�����
		StartEvent(turn, board, playerTurn, socks, isServer, list);
		break;
	case 2:	//���ʽ�����
		BonusEvent(turn, board, playerTurn, socks, isServer);
		PlayerState(tNum);
		break;
	case 8:	//���ε�
		if(turn==playerTurn)
			gotoxytext(37, 28, "���ε� ��÷ ���� �Ͽ� Ż�� ���� !");
		Sleep(800);
		clrText();
		player[turn].state = 1;
		break;
	case 12: case 20: case 28:
		FortuneCard(turn, board, playerTurn, socks, isServer, list);
		break;
	case 16:
		OlympicEvent(turn, playerTurn, socks, isServer, list);
		PlayerState(tNum);
		break;
	case 24:
		gotoxytext(37, 28, "���迩�� ~~ �����Ͽ� ���ϴ°����� �̵� !");
		Sleep(800);
		clrText();
		player[turn].state = 2;
		break;
	case 30:
		TaxEvent(turn, playerTurn, socks, isServer, list);
		break;
	default:

		switch (state)
		{
		case -1:   //������ ���������
			if (player[turn].marble >= local[board].price) {	//�����ҵ��� ������
				
				if (turn == playerTurn) {

					gotoxytext(37, 27, "����ִ� �����Դϴ�. �����Ͻðڽ��ϱ�?");
					gotoxytext(37, 28, "1) YES  2) NO  (����) �� ");

					gotoxy(70, 28);
					cursor_view(1);
					do {
						select = _getch() - 48;
						gotoxyint(70, 28, select);
						gotoxytext(70, 28, "      ");
					} while (select != 1 && select != 2);
					cursor_view(0);
					gotoxyint(70, 28, select);
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
							
				Sleep(500);

				if (select1 == 1) {
					if (board != 4 && board != 9 && board != 14 && board != 18 && board != 25) {   //�������� ����
						gotoxytext(37, 30, "ȣ���� �Ǽ��߽��ϴ�.");
						local[board].state = turn;   //������ ���¸� �ٲ���
					}
					else {
						gotoxytext(37, 30, "�������� �����߽��ϴ�.");
						local[board].state = turn + 8;   //������ ���¸� �ٲ���
					}

					player[turn].marble -= localPrice[board][0];   //���� ���� ����

					Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //���ο� ����������
					HangNode(list, node);   //�÷��̾��� ����Ʈ�� ������带 ��������
					if (turn == playerTurn) {
						PrintList(list);
					}
					SetDrawColor(turn);
					gotoxytext(local[board].x, local[board].y - 2, "����");
					GRAY
				}
			}
			else {
				gotoxy(37, 27);
				printf("������ ���� �����մϴ�.\n");
			}
			break;

		case 0:   //player1�� ȣ���� �������ִ°��
			if (turn == 0){
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else 
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*������ �ø��� ���¸� ����� 2�� ����*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn) {
					printf("������ %d���� �Դϴ�.", toll);
				}

				int price = toll;
				/*������ ī�尡 ������*/
				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn) {
						printf("������ %d���� �Դϴ�.", price);
					}
				}

				/*���������� ����Ẹ�� ������ �Ļ����(�ǹ��Ű�)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*�μ��� ������*/

				Takeover(turn, board, playerTurn, socks, isServer, list1, list);
				
				Sleep(500);

			}
			break;

		case 1:	//player2�� ȣ���� �������ִ°��
			if (turn == 1)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*������ �ø��� ���¸� ����� 2�� ����*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				/*������ ī�尡 ������*/
				if (player[turn].card == 1 || player[turn].card == 2) {

					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("������ %d���� �Դϴ�.", price);
				}

				/*���������� ����Ẹ�� ������ �Ļ����(�ǹ��Ű�)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*�μ��� ������*/
				Takeover(turn, board, playerTurn, socks, isServer, list2, list);

				Sleep(500);

			}
			break;

		case 2:	//player3�� ȣ���� �������ִ°��
			if (turn == 2)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*������ �ø��� ���¸� ����� 2�� ����*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				/*������ ī�尡 ������*/
				if (player[turn].card == 1 || player[turn].card == 2) {

					price -= DoAngel(turn, toll, playerTurn, socks, isServer);

					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("������ %d���� �Դϴ�.", price);
				}

				/*���������� ����Ẹ�� ������ �Ļ����(�ǹ��Ű�)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*�μ��� ������*/
				Takeover(turn, board, playerTurn, socks, isServer, list2, list);
				Sleep(500);

			}
			break;
		case 3:	//player4�� ȣ���� �������ִ°��
			if (turn == 3)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*������ �ø��� ���¸� ����� 2�� ����*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				/*������ ī�尡 ������*/
				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("������ %d���� �Դϴ�.", price);
				}

				/*���������� ����Ẹ�� ������ �Ļ����(�ǹ��Ű�)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*�μ��� ������*/
				Takeover(turn, board, playerTurn, socks, isServer, list3, list);
				Sleep(500);

			}
			break;

		case 4:	//player1�� ���帶ũ�� �������ִ°��
			if (turn != 0) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if(turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 5:	//player2�� ���帶ũ�� �������ִ°��
			if (turn != 1) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 6:	//player3�� ���帶ũ�� �������ִ°��
			if (turn != 2) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 7:	//player4�� ���帶ũ�� �������ִ°��
			if (turn != 3) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;

		case 8:	//player1�� �������� ���
			if (turn != 0) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 9:
			if (turn != 1) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 10:
			if (turn != 2) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 11:
			if (turn != 3) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		default:
			break;
		}

		PlayerState(tNum);
		Sleep(700);
		clrList();
		clrText();
		
		CheckGameOver(turn, playerTurn);
		break;
	}
}

void BuildRandmark(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select;
	int select1;
	
	if(turn == playerTurn){
		gotoxytext(37, 27, "���帶ũ�� �Ǽ��Ͻðڽ��ϱ�?");
		gotoxy(37, 28);
		printf("1) YES  2) NO  (����) �� ");

		gotoxy(70, 28);
		cursor_view(1);
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
		if (player[turn].marble >= localPrice[board][1]) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\LandMark_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "���帶ũ�� �Ǽ��߽��ϴ�.");
			}
			local[board].state = turn + 4;      //������ ���º���
			local[board].price = localPrice[board][3];   //������ ���ݺ���

			player[turn].marble -= localPrice[board][1];
			modifiNode(list, local[board].name, localPrice[board][3]);	//��������� ���ݼ���

			SetDrawColor(turn);
			gotoxytext(local[board].x, local[board].y - 2, "������");	//���帶ũ ������� ����
			GRAY
		}
		else
		{
			if (turn == playerTurn)
			{
				gotoxytext(37, 30, "�Ǽ��� ���� �����ϴ�.");
			}
		}
	}
}

void Takeover(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list, LinkedList *myList) {

	int select, select1;
	Sleep(500);
	if (player[turn].marble > localPrice[board][0]) {   //�μ��� ���� ������
		if (turn == playerTurn) {
			gotoxy(37, 27);
			printf("�μ��Ͻðڽ��ϱ�? �μ���� %d�Դϴ�.\n", localPrice[board][0]);
			gotoxy(37, 28);
			printf("1) YES  2) NO  (����) �� ");

			gotoxy(70, 28);
			cursor_view(1);
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
			Sleep(500);
			gotoxytext(37, 30, "�μ��� �Ϸ��߽��ϴ�.\n");
			clrText();
			player[turn].marble -= localPrice[board][0];   //�������� ����
			player[1 - turn].marble += localPrice[board][0];
			local[board].state = turn;   //������ ���� ����
			Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //������� ����
			
			deletNode(list, local[board].name);   //������ ���Ḯ��Ʈ���� ������� ����
			
			HangNode(myList, node);   //�ڽ��� ���Ḯ��Ʈ�� ������� ����
			SetDrawColor(turn);
			gotoxytext(local[board].x, local[board].y - 2, "����");
			GRAY
			return;
		}
	}
	else {
		gotoxy(37, 30);
		printf("�μ��� ���� �����մϴ�.\n");
		clrText();
	}
}
