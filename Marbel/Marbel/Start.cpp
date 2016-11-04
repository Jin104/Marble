#include "draw.h"
#include "player.h"
#include "start.h"
#include "buildEvent.h"

Local local[32];
Player player[2];

LinkedList *list1 = NewList();
LinkedList *list2 = NewList();

void StartGame() {

	playerTurn();

	system("mode con: cols=130 lines=48");
	
	GameBoard();
	DrawPlayer();
	initLocal();
	initPlayerCoord();


	while (1) {
		int doubleCnt = 0;
		for (int i = 0; i < 2; i++) {		//�÷��̾� 1,2 �����Ƽ� �ϴ°�
			Dice d;
			gotoxy(73, 8);
			printf("%s���� �����Դϴ�!", player[i].name);

			switch (player[i].state)		//�÷��̾ ���¸� �޾Ƽ� �װ������� �̺�Ʈ�� �߻�
			{
			case 1:
				break;
			case 2:
				//IslandEvent(i);
				break;
			case 3:
				WorldTourEvent(i);
			default:
				d = GameDice(i);				//�ֻ��� ó�� ������
				movePlayer(d.sum, i);		//�̵�
				buildBuilding(i, player[i].board);

				break;
			}

			/*if (d.dice1 == d.dice2) {
				doubleCnt++;
				if (doubleCnt > 1) {
					gotoxy(48, 24);
					printf("%d �ʹ� �ռ����׿�..���ε��� ������",doubleCnt);
					player[i].board = 9;
					Sleep(500);
					gotoxy(48, 24);
					printf("                                  ");
					doubleCnt = 0;
				}
				else {
					DoubleDice();
					i--;
				}

			}
			else {
				doubleCnt = 0;
			}*/
		}
	}
}

void initLocal() {
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].name, localName[i]);
		strcpy(local[i].color, localColor[i]);
		local[i].price = localPrice[i][0];
		local[i].x = localX[i];
		local[i].y = localY[i];
	}
}

void initPlayerCoord() {
	gotoxytext(33, 8, player[0].name);
	gotoxytext(73, 37, player[1].name);
	gotoxytext(33, 8, player[0].name);
	gotoxytext(73, 37, player[1].name);
	gotoxy(42, 10); printf("%d", player[0].marble);
	gotoxy(82, 39); printf("%d", player[1].marble);
	gotoxy(player[0].playerX, player[0].playerY);
	printf("��");
	player[1].playerX = player[0].playerX + 2;
	gotoxy(player[1].playerX, player[1].playerY);
	printf("��");
}

void movePlayer(int i, int turn) {
		
	for (int j = 0; j < i; j++) {
		gotoxytext(player[turn].playerX, player[turn].playerY, "  ");
		player[turn].board++;

		if (player[turn].board > 31) {
			player[turn].board -= 32;
			player[turn].turn++;
		}

		player[turn].playerX = local[player[turn].board].x + (turn * 2);
		player[turn].playerY = local[player[turn].board].y;
		gotoxy(player[turn].playerX, player[turn].playerY);
		if (turn == 0) {
			printf("��");
		}
		else {
			printf("��");
		}
		Sleep(150);
	}

}

void playerTurn() {

	printf("�÷��̾�1�� �̸��� �Է����ּ��� : ");
	scanf("%s", player[0].name);
	printf("�÷��̾�2�� �̸��� �Է����ּ��� : ");
	scanf("%s", player[1].name);

	printf("������ ���մϴ�.\n");
	getchar();
	system("cls");

	srand(time(NULL));
	int n = rand() % 2;

	player[0].turn = n;
	player[1].turn = 1 - n;

	if (player[1].turn == 0) {
		Player tmp = player[0];
		player[0] = player[1];
		player[1] = tmp;
	}
	printf("%s���� ù��° ���ʳ׿�.\n���� ���� �����ϼ���\n", player[0].name);
	Sleep(300);
}