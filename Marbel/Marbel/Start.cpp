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

int tNum;
//extern SOCKET sock;
void StartGame(int totalNumber, int playerTurn, char *name,void *socks, bool isServer) {
	
	tNum = totalNumber;

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

		for (int turn = 0; turn < totalNumber; turn++) {		//�÷��̾� ���� 0:player1  1:player2  2:player3  3:player4

			SetDrawColor(turn);
			gotoxytext(1, 20, player[turn].name);

			GRAY
			gotoxytext(1, 21, "���� �����Դϴ�!");

			switch (player[turn].state)		//�÷��̾ ���¸� �޾Ƽ� �װͿ����� �̺�Ʈ�� �߻�
			{
			case 2:	//���迩�࿡�ִ� ����
				if (WorldTourEvent(turn, playerTurn, socks, isServer) == -1) {
					player[turn].state = 0;	//�÷��̾���¸� �⺻����
					goto A;	//�ֻ����� ������ ������
				}
				else {
					goto B;	//����������
				}

			case 1:	//���ε����ִ� ����
				doubleCnt = 0;
				if (IslandEvent(turn, playerTurn, socks, isServer) == -1) {
					player[turn].state = 0;
					goto B;	//����������
				}
			default:	//�⺻�����϶�
				/*������ 3���̻��϶� ���ε���*/
				if (doubleCnt > 2) {
					GoIsland(turn);	//���ε��� �̵�
					player[turn].marble -= 75;	//���ε��ΰ����� ������ �������� ����
					doubleCnt = 0;
					goto B;	//����������
				}
			A:

				Dice d;
				char sumData[2];
				char equalData[2];
				int select;



				/*������ ó��    �ٸ� ���� ������ ó���� ����ؼ� ���⿡�� �ּ� �޾ҽ��ϴ�*/
				//�ڱ��� �����϶�
				if (turn == playerTurn) {
					d = GameDice(turn);	//�ֻ��� ������
					itoa(d.sum, sumData, 10);
					itoa(d.equal, equalData, 10);
					if (isServer)	//�ڽ��� ������
					{
						SendMsg(sumData, sizeof(sumData), 0);	//�ٸ� Ŭ���̾�Ʈ���� ����� ����
						SendMsg(equalData, sizeof(equalData), 0);
					}
					else  //������ �ƴϸ�
					{
						send((SOCKET)socks, sumData, sizeof(sumData), 0);	//�������� ����� ����
						send((SOCKET)socks, equalData, sizeof(equalData), 0);
					}
					select = atoi(sumData);
					MovePlayer(select, turn);	//���¸�ŭ �̵�
				}
				else  //�ڱ��� ���ʰ� �ƴϸ�
				{
					if (isServer)	//�ڽ��� ������
					{
						SOCKET *sockArr = (SOCKET *)socks;
						while (recv(sockArr[turn], sumData, sizeof(sumData), 0) <= 0);	//������� ����
						while (recv(sockArr[turn], equalData, sizeof(equalData), 0) <= 0);
						SendMsg(sumData, sizeof(sumData), turn);	//���� ������� �ٸ� Ŭ���̾�Ʈ���� ����
						SendMsg(equalData, sizeof(equalData), turn);
					}
					else  //������ �ƴϸ�
					{
						while (recv((SOCKET)socks, sumData, sizeof(sumData), 0) <= 0);	//������� ����
						while (recv((SOCKET)socks, equalData, sizeof(equalData), 0) <= 0);
					}
					select = atoi(sumData);
					MovePlayer(select, turn);	//���¸�ŭ �̵�
				}
			
				/*3���̻� ������ �����ϰ�*/
				if (doubleCnt < 2) {
					BuildingEvent(turn, player[turn].board, playerTurn, socks, isServer);	//���������������� �̺�Ʈ
				}
				
				/*�����̳�������*/
				if (atoi(equalData)==1 && player[turn].state == 0) {
					turn--;	//���� �ٲ����ʱ�����
					doubleCnt++;
				}
				else {
					gotoxy(73, 10);
					printf("             ");
					doubleCnt = 0;
				}
			B:
				gotoxytext(1, 20, "              ");
				gotoxy(48, 20);
				printf("                                     ");
				clrDice();
				clrCard();
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

		SetDrawColor(turn);
		printf("��");
		GRAY
			Sleep(200);
	}

}
