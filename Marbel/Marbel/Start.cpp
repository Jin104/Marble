#include "Start.h"
#include "Player.h"
#include "BuildEvent.h"

Local local[32];	//���� 32��
Player player[4];	//�÷��̾� 2��

LinkedList *list1 = NewList();		//�÷��̾ ������ ������ ����Ʈ
LinkedList *list2 = NewList();
LinkedList *list3 = NewList();
LinkedList *list4 = NewList();

void StartGame(int totalNumber) {

	PlayerTurn(totalNumber);	//���� ���ϱ�

	system("mode con: cols=130 lines=48");
	printf("%d\n", totalNumber);
	system("pause");
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
				if (WorldTourEvent(i) == -1) {
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
				d = GameDice(i);	//�ֻ��� ������
				MovePlayer(d.sum, i);	//���¸�ŭ �̵�

										/*3���̻� ������ �����ϰ�*/
				if (doubleCnt < 2) {
					BuildingEvent(i, player[i].board);	//���������������� �̺�Ʈ
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

	PLAYER2
		gotoxytext(73, 37, player[1].name);
	player[1].playerX = player[0].playerX + 2;
	gotoxy(player[1].playerX, player[1].playerY);
	printf("��");

	GRAY
		gotoxy(42, 10); printf("%d", player[0].marble);
	gotoxy(82, 39); printf("%d", player[1].marble);

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

	/*for (int i = 0; i < totalNumber; i++) {


	}*/
	


	char name[50];

	PLAYER1
	gotoxytext(45, 15, "Player 1");
	GRAY
	gotoxytext(54, 15, "�� �̸��� �Է����ּ��� (1~5����,����x)");
	gotoxytext(45, 17, "��  ");

	/*�̸��� ũ�⸦ �Ѿ�� �ٽ��Է¹���*/
	cursor_view(1);
	do {
		gotoxy(49, 17); scanf("%s", name);
		gotoxytext(49, 17, "                                                            ");

	} while (strlen(name) > 10);
	cursor_view(0);
	strcpy(player[0].name, name);
	gotoxytext(49, 17, player[0].name);

	PLAYER2
		gotoxytext(45, 20, "Player 2");
	GRAY
		gotoxytext(54, 20, "�� �̸��� �Է����ּ��� (1~5����,����x)");
	gotoxytext(45, 22, "��  ");

	cursor_view(1);
	do {
		gotoxy(49, 22); scanf("%s", name);
		gotoxytext(49, 22, "                                                            ");

	} while (strlen(name) > 10);
	cursor_view(0);
	strcpy(player[1].name, name);
	gotoxytext(49, 22, player[1].name);
	Sleep(250);

	system("cls");
	sndPlaySoundA("..\\sound\\User_Set_ready_A01.wav", SND_ASYNC | SND_NODEFAULT);
	gotoxytext(53, 17, "������ ���մϴ�. ENTER�� �����ּ���!");
	_getch();
	system("cls");

	/*�������� ������ ������*/
	srand(time(NULL));
	int n = rand() % 2;
	player[0].turn = n;
	player[1].turn = 1 - n;

	/*0�̳��� �÷��̾ ù��° �÷��̾��*/
	if (player[1].turn == 0) {
		Player tmp = player[0];
		player[0] = player[1];
		player[1] = tmp;
	}

	sndPlaySoundA("..\\sound\\User_Set_A01.wav", SND_ASYNC | SND_NODEFAULT);
	gotoxy(53, 17);
	printf("%s ���� ���̿��� !", player[0].name);
	gotoxytext(53, 19, "���� ���� �����ϼ��� ~");

	Sleep(1400);
	gotoxytext(79, 12, "������������������");
	for (int i = 13; i < 23; i++) {
		gotoxytext(79, i, "��");
		gotoxytext(95, i, "��");
	}
	gotoxytext(81, 14, "   ��     ��");
	gotoxytext(81, 15, "  �ܡ�    ��");
	gotoxytext(81, 16, " ��  �� �ܡ�");
	gotoxytext(81, 17, "��    ��  ��");
	gotoxytext(81, 18, "          ��");
	gotoxytext(81, 19, "  ��       ");
	gotoxytext(81, 20, "  ��       ");
	gotoxytext(81, 21, "  �ܡܡܡܡ�");
	gotoxytext(79, 23, "������������������");
	Sleep(800);
}