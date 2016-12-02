#include "Start.h"
#include "Player.h"
#include "BuildEvent.h"
#include "Client.h"

Local local[32];	//���� 32��
Player player[4];	//�÷��̾� 2��

LinkedList *list1 = NewList();		//�÷��̾ ������ ������ ����Ʈ
LinkedList *list2 = NewList();
LinkedList *list3 = NewList();
LinkedList *list4 = NewList();

extern int serverNumber;
extern SOCKET sock;
void StartGame(int totalNumber, int playerTurn, char *name) {

	//PlayerTurn(totalNumber);	//����

	system("mode con: cols=130 lines=48");
	printf("%d\n", playerTurn);
	Sleep(1000);
	system("cls");
	GameBoard();	//������ ���
	DrawPlayer(totalNumber);	//�÷��̾��� ���
	initLocal();	//���� �ʱ�ȭ
	initPlayerCoord(totalNumber);	//�÷��̾� �������

	PlaySound(NULL, 0, 0);
	int doubleCnt = 0;
	while (1) {

		for (int i = 0; i < totalNumber; i++) {		//�÷��̾� ���� 0:player1  1:player2

			if (i == 0)
				PLAYER1
			else if(i==1)
				PLAYER2
			else if(i==2)
				PLAYER3
			else
				PLAYER4

			gotoxytext(1, 20, player[i].name);

			GRAY
				gotoxytext(1, 21, "���� �����Դϴ�!");

			switch (player[i].state)		//�÷��̾ ���¸� �޾Ƽ� �װͿ����� �̺�Ʈ�� �߻�
			{
			case 2:	//���迩�࿡�ִ� ����
				if (WorldTourEvent(i, playerTurn) == -1) {
					player[i].state = 0;	//�÷��̾���¸� �⺻����
					goto A;	//�ֻ����� ������ ������
				}
				else {
					goto B;	//����������
				}

			case 1:	//���ε����ִ� ����
				doubleCnt = 0;
				if (IslandEvent(i) == -1) {
					player[i].state = 0;
					goto B;	//����������
				}
			default:	//�⺻�����϶�
				/*������ 3���̻��϶� ���ε���*/
				if (doubleCnt > 2) {
					GoIsland(i);	//���ε��� �̵�
					player[i].marble -= 75;	//���ε��ΰ����� ������ �������� ����
					doubleCnt = 0;
					goto B;	//����������
				}
			A:
				Dice d;
				char dd[2];
				d = GameDice(i);	//�ֻ��� ������
				itoa(d.sum, dd, 10);
				
				if (i == serverNumber) {
					SendMsg(dd, sizeof(dd));
				}
				else {
					if (i == playerTurn) {
						send(sock, dd, 2, 0);
					}
					recv(sock, dd, 2, 0);
				}
				MovePlayer(atoi(dd), i);	//���¸�ŭ �̵�

										/*3���̻� ������ �����ϰ�*/
				if (doubleCnt < 2) {
					BuildingEvent(i, player[i].board, playerTurn);	//���������������� �̺�Ʈ
				}

				/*�����̳�������*/
				if (d.dice1 == d.dice2 && player[i].state == 0) {
					i--;	//���� �ٲ����ʱ�����
					doubleCnt++;
					gotoxy(73, 10);
					printf("���� %d��°", doubleCnt);
				}
				else {
					gotoxy(73, 10);
					printf("             ");
					doubleCnt = 0;
				}
			B:
				break;

			}
		}
	}
}

/*�������� �ʱ�ȭ*/
void initLocal() {
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].name, localName[i]);
		local[i].price = localPrice[i][0];
		local[i].x = localX[i];
		local[i].y = localY[i];
	}
}

/*�ʱ� �÷��̾����� ���*/
void initPlayerCoord(int totalNumber) {

	PLAYER1
		gotoxytext(33, 8, player[0].name);
	gotoxy(player[0].playerX, player[0].playerY);
	printf("��");
	GRAY
		gotoxy(42, 10); printf("%d", player[0].marble);

	PLAYER2
		gotoxytext(73, 37, player[1].name);
	player[1].playerX = player[0].playerX + 2;
	gotoxy(player[1].playerX, player[1].playerY);
	printf("��");
	GRAY
		gotoxy(42, 10); printf("%d", player[1].marble);

	if (totalNumber >= 3) {
		PLAYER3
			gotoxytext(33, 37, player[2].name);
		player[2].playerX = player[1].playerX + 2;
		gotoxy(player[2].playerX, player[2].playerY);
		printf("��");
		GRAY
			gotoxy(42, 10); printf("%d", player[2].marble);

		if (totalNumber > 3) {
			PLAYER4
				gotoxytext(73, 8, player[3].name);
			player[3].playerX = player[2].playerX + 2;
			gotoxy(player[3].playerX, player[3].playerY);
			printf("��");
			GRAY
				gotoxy(42, 10); printf("%d", player[3].marble);
		}
	}

}

/*�÷��̾ �̵�������   i:�̵���ų����  turn:�÷��̾����*/
void MovePlayer(int i, int turn) {

	for (int j = 0; j < i; j++) {
		sndPlaySoundA("..\\sound\\DiceItem00000_0.wav", SND_ASYNC | SND_NODEFAULT);
		gotoxytext(player[turn].playerX, player[turn].playerY, "  ");	//������ġ�� ���� ������
		player[turn].board++;

		/*������� �����ԵǸ� ������ �ٽ� 0����*/
		if (player[turn].board > 31) {
			player[turn].board -= 32;
			player[turn].marble += 75;	//������� ������ ��������
		}

		/*�÷��̾��� ��ġ�� ������ ��ġ�� �ٲٰ� �� ���*/
		player[turn].playerX = local[player[turn].board].x + (turn * 2);
		player[turn].playerY = local[player[turn].board].y;
		gotoxy(player[turn].playerX, player[turn].playerY);

		if (turn == 0)
			PLAYER1
		else if(turn == 1)
			PLAYER2
		else if(turn == 2)
			PLAYER3
		else
			PLAYER4

		printf("��");
		GRAY
			Sleep(200);
	}

}

/*�÷��̾� ������ ������*/
void PlayerTurn(int totalNumber) {

	//for (int i = 0; i < totalNumber; i++) {
	//	//player[i].myTurn=

	//}

	Sleep(800);
}