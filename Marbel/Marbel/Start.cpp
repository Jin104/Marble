#include "draw.h"
#include "player.h"
#include "start.h"
#include "buildEvent.h"

Local local[32];
Player player[2];

LinkedList *list1 = NewList();		//�÷��̾ ������ ������ ����Ʈ
LinkedList *list2 = NewList();

void StartGame() {

	playerTurn();

	system("mode con: cols=130 lines=48");
	
	GameBoard();
	DrawPlayer();
	initLocal();
	initPlayerCoord();

	int doubleCnt = 0;
	while (1) {
		
		for (int i = 0; i < 2; i++) {		//�÷��̾� 1,2 �����Ƽ� �ϴ°�
			Dice d;
			gotoxy(73, 8);
			printf("%d: %s���� �����Դϴ�!",i, player[i].name);

			switch (player[i].state)		//�÷��̾ ���¸� �޾Ƽ� �װ������� �̺�Ʈ�� �߻�
			{
			case 1:

				break;
			case 3:
				if (WorldTourEvent(i) == -1) {
					player[i].state = 0;
					goto A;
				}
				else {
					goto C;
				}
				
			case 2:
				doubleCnt = 0;
				if (IslandEvent(i) == -1) {
					player[i].state = 0;
					goto B;
				}
			default:
				if (doubleCnt > 2) {
					GoIsland(i);
					player[i].marble -= 75;
					doubleCnt = 0;
					goto B;
				}
				A:
				d = GameDice(i);
				movePlayer(d.sum, i);
				C:
				if (doubleCnt < 2) {
					buildBuilding(i, player[i].board);
				}
				if (d.dice1 == d.dice2 && player[i].state != 2) {
					i--;
					doubleCnt++;
					gotoxy(73, 9);
					printf("���� %d��°", doubleCnt);
				}
				else {
					gotoxy(73, 9);
					printf("             ");
					doubleCnt = 0;
				}		
			B:
				break;
			
			}
			
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


	//1�� ��
	settextcolor(444444, 000000);
	gotoxytext(33, 8, player[0].name);
	
	gotoxy(player[0].playerX, player[0].playerY);
	printf("��");
	settextcolor(777777, 000000);
	//2�� ��
	gotoxytext(73, 37, player[1].name);
	
	player[1].playerX = player[0].playerX + 2;
	gotoxy(player[1].playerX, player[1].playerY);
	printf("��");
	settextcolor(0x0007, 000000);
	gotoxy(42, 10); printf("%d", player[0].marble);
	gotoxy(82, 39); printf("%d", player[1].marble);
	//���� ��
}

void movePlayer(int i, int turn) {
	
	for (int j = 0; j < i; j++) {
		gotoxytext(player[turn].playerX, player[turn].playerY, "  ");
		player[turn].board++;

		if (player[turn].board > 31) {
			player[turn].board -= 32;
			player[turn].marble += 75;
		}

		player[turn].playerX = local[player[turn].board].x + (turn * 2);
		player[turn].playerY = local[player[turn].board].y;
		gotoxy(player[turn].playerX, player[turn].playerY);

		if (turn == 0) {
			settextcolor(888888, 000000);
		}
		else {
			settextcolor(555555, 000000);
		}
		printf("��");
		settextcolor(0x0007, 000000);
		Sleep(0);
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