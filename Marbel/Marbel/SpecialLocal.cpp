#include "player.h"
#include "Start.h"
#include "BuildEvent.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];
extern int tNum;

//����
//���ʽ� ���� �̺�Ʈ
void BonusEvent(int turn, int board, int playerTurn, void *socks, bool isServer) {

	int select, select1, correct;
	char data[2];

	if (turn == playerTurn) {
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

	srand(time(NULL));
	correct = rand() % 2 + 1;

	if (correct == 1) {
		if (correct == select1) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\Maccau_Success_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			}
			if (turn == playerTurn)
				player[turn].marble += 50;
		}
		else
			gotoxytext(37, 30, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}
	else {
		if (correct == select1) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\Maccau_Success_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "¦¦¦ ~ ���߼̽��ϴ�! 50�� ���� ����!");
			}
			player[turn].marble += 50;
		}
		else
			if (turn == playerTurn)
				gotoxytext(37, 30, "������ ���߽��ϴ�...������ �ٽ� �����ϼ���!");
	}

	Sleep(800);
	clrText();
}

/*����� �Ǽ� �̺�Ʈ*/
void StartEvent(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

	int select;
	int select1;
	char data[2];

	char name[10];
	if (turn == playerTurn) {
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
	else {
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

		if(turn==playerTurn)
			PrintList(list);

		int cnt = 0;
		/*������ ȣ�ڰ� ���帶ũ�� ��*/
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == turn + 4 || local[j].state == turn + 2) {
				cnt++;
			}
		}

		/*������ �ǹ��� ���� ������*/
		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				if (turn == playerTurn) {
					clrText();
					gotoxytext(37, 28, "���帶ũ�� ���� �ǹ��� �Է��ϼ���. (������ �Ұ�)");
					gotoxy(37, 29);
					scanf("%s", name);

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
				
				/*������ ������ �Է��Ҷ�*/
				if (node != NULL) {

					/*������ ���°� ���帶ũ�� �ƴҶ�*/
					if (local[node->num].state != turn + 4 && local[node->num].state != turn + 8) {
						k++;
						local[node->num].state = turn + 4;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][3]);
						
						SetDrawColor(turn);
						gotoxytext(local[node->num].x, local[node->num].y - 2, "������");
						GRAY
						sndPlaySoundA("..\\sound\\LandMark_A01.wav", SND_ASYNC | SND_NODEFAULT);
						if(turn==playerTurn)
							gotoxytext(37, 33, "���帶ũ�� �Ǽ��߽��ϴ�!");
						Sleep(500);
						clrText();
					}
					else {
						if (turn == playerTurn)
							gotoxytext(37, 33, "�������� ���帶ũ�� �Ұ����մϴ�.");
						Sleep(700);
						clrText();
					}
				}
				else {
					if (turn == playerTurn)
						gotoxytext(37, 33, "���� ���� �Դϴ�. �ٽ� �Է����ּ���.");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			if (turn == playerTurn)
				gotoxytext(37, 28, "�Ǽ��� ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 28, "�Ǽ����� �ʽ��ϴ�.");
	}

	Sleep(900);
	clrText();
	clrList();
}

/*���ε�*/
int IslandEvent(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	if (turn == playerTurn) {
		gotoxytext(37, 27, "�� ���ε� ��");
		gotoxytext(37, 28, "���ε��� �������ϴ�! Ż���� (����) �� ");
		gotoxytext(37, 29, "1) ���� ����   2) 50�� ���� ����");

		gotoxy(80, 28);
		cursor_view(1);
		do {
			select = _getch() - 48;
			gotoxyint(80, 28, select);
			gotoxytext(80, 28, "      ");

		} while (select != 1 && select != 2);
		cursor_view(0);
		gotoxyint(80, 28, select);
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
		if(turn==playerTurn)
			gotoxytext(37, 31, "���� ���ϴ�");
		Sleep(900);
		clrText();
		return -1;
	}
	else {
		player[turn].marble -= 50;
		if (turn == playerTurn)
			gotoxytext(37, 31, "50�� ������ ���� �Ǿ����ϴ�");
		player[turn].state = 0;	//�÷��̾� ���� ����
		Sleep(900);
		clrText();
		return 0;
	}
}

/*�ø���*/
void OlympicEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select, select1;
	char name[10];
	char data[2];

	if (turn == playerTurn) {
		sndPlaySoundA("..\\sound\\Olympic_A01.wav", SND_ASYNC | SND_NODEFAULT);
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
		
		if(turn==playerTurn)
			PrintList(list);

		/*���������� ������*/
		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				if (turn == playerTurn) {
					gotoxytext(37, 27, "������ �̸��� �Է��ϼ��� �� ");
					gotoxy(70, 27); scanf("%s", name);

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

				if (node != NULL) {
					k++;
					/*�ٸ������� �ø��Ȼ��¸� ����*/
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}
					/*�Է��������� �ø��Ȱ���*/
					local[node->num].olystate = 1;

					if(turn==playerTurn)
						gotoxytext(37, 32, "����� 2�谡 ��µǾ����ϴ�!");
					Sleep(900);
					clrText();

				}
				else {
					if (turn == playerTurn)
						gotoxytext(37, 31, "���� ���� �Դϴ�. �ٽ� �Է����ּ���. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			if (turn == playerTurn)
				gotoxytext(37, 28, "������ ������ �����ϴ�.");
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 28, "�������� �ʽ��ϴ�.");
	}

	Sleep(900);
	clrText();

}

/*���迩��*/
int WorldTourEvent(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	int k, k1;
	char name[10];
	char data[2];
	
	if (turn == playerTurn) {
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
		clrText();
		if (player[turn].marble < 10) {
			if(turn==playerTurn)
				gotoxytext(37, 33, "������ �����մϴ�.");
			return -1;
		}

		if (turn == playerTurn)
			sndPlaySoundA("..\\sound\\WorldTour_A01.wav", SND_ASYNC | SND_NODEFAULT);
		
		int cnt = 0;
		for (int k = 0; k < 1;) {
			int n;

			if (turn == playerTurn) {
				clrText();
				gotoxytext(37, 29, "������ ���� �Է��ϼ���  ��");
				gotoxy(70, 29);
				cursor_view(1);
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

			/*�Է��Ѱ� ����ʿ� �ִ���*/
			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					/*����ī�� �Է½�*/
					if (j == 12) {
						for (int m = 0; m < 1;) {

							if (turn == playerTurn) {
								gotoxytext(37, 32, "���° ����ī��� �����? ��");
								gotoxy(70, 32);
								k = getch() - 48;
								gotoxyint(70, 32, k);
								clrText();
								itoa(k, data, 10);

								if (isServer)
								{
									SendMsg(data, sizeof(data), 0);
								}
								else
								{
									send((SOCKET)socks, data, sizeof(data), 0);
								}
								k1 = atoi(data);
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
								k1 = atoi(data);
							}

							switch (k1)
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
								if (turn == playerTurn)
									gotoxytext(37, 33, "�߸��Է��ϼ̽��ϴ�.");
								Sleep(500);
								clrText();
								break;
							}
						}
					}
					else {
						n = j;
					}
					cnt++;
					break;
				}
			}
			if (cnt > 0) {
				clrText();
				if (turn == playerTurn)
					gotoxytext(37, 33, "�̵��մϴ�");
				k++;
				player[turn].marble -= 10;
				player[turn].state = 0;
				int move;

				if (n > 24) {
					move = n - 24;
				}
				else {
					move = n + 8;
				}
				MovePlayer(move, turn);
				BuildingEvent(turn, player[turn].board, playerTurn,socks, isServer);
			}
			else {
				clrText();
				if (turn == playerTurn)
					gotoxytext(37, 33, "���� ���� �Դϴ�. �ٽ� �Է����ּ���.");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 33, "�������� �ʽ��ϴ�.");
		return -1;
	}

	Sleep(900);
	clrText();
}

//����
//����û �̺�Ʈ
void TaxEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	int tax = 0;

	if (turn == playerTurn) {
		gotoxytext(37, 27, "�� ����û ��");
		gotoxytext(37, 28, "����û �Դϴ� ������ �������ּ���");
		gotoxytext(37, 29, "[�ڽ��� ����/�ǹ� 10% ¡��]");
	}
	for (int k = 0; k < 32; k++) {
		if (local[k].state == turn || local[k].state == turn + 4 || local[k].state == turn + 8) {
			tax += local[k].price;
		}
	}

	tax = (0.1)*tax;
	if (turn == playerTurn)
		gotoxy(70, 30); printf("������ %d ���� �Դϴ�", tax);

	if (player[turn].marble >= tax) {
		player[turn].marble -= tax;
		Sleep(1000);
		if (turn == playerTurn)
			gotoxytext(37, 32, "���� ������ �Ϸ� �Ǿ����ϴ�");
	}
	else {
		Bankrupt(turn, tax, playerTurn, socks, isServer, list);
	}

	PlayerState(tNum);
	Sleep(900);
	clrText();
}
