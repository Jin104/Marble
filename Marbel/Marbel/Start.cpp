#include "draw.h"
#include "player.h"
#include "start.h"
#include <time.h>

Local local[32];
Player player[2];

void StartGame() {
	
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].name, localName[i]);
		strcpy(local[i].color, localColor[i]);
		local[i].price = localPrice[i];
		local[i].x = localX[i];
		local[i].y = localY[i];
	}

	playerTurn();

	system("mode con: cols=130 lines=48");

	GameBoard();
	DrawPlayer();
	initPlayerCoord();

	//while (1) {
	//	for (int i = 0; i < 2; i++) {
	//		gotoxy(70, 25);
	//		printf("%s���� �����Դϴ�!", player[i].name);
	//		int n = GameDice();
	//		movePlayer(n, i);
	//	}
	//}

	while (1) {

		for (int i = 0; i < 2; i++) {
			Dice d;
			int doubleCount = 0;
			gotoxy(70, 25);
			printf("%s���� �����Դϴ�!", player[i].name);

			d = GameDice();
			if (d.dice1 != d.dice2) {
				movePlayer(d.sum, i);
			}
			else {
				movePlayer(d.sum, i);
				DoubleDice();

				d = GameDice();
				if (d.dice1 != d.dice2) {
					movePlayer(d.sum, i);
				}
				else {
					movePlayer(d.sum, i);
					DoubleDice();

					d = GameDice();
					if(d.dice1==d.dice2){
						gotoxy(48, 24);
						printf("�ʹ� �ռ����׿�..���ε��� ������");
						player[i].playerBoard = 9;
						Sleep(500);
						//getchar();
						gotoxy(48, 24);
						printf("                                  ");
						break;
					}
					else {
						movePlayer(d.sum, i);
					}
				}
			}
		}
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
	gotoxy(player[1].playerX + 2, player[1].playerY);
	printf("��");
}

int moveCount = 0;
void movePlayer(int i, int turn) {
		
	gotoxy(player[turn].playerX, player[turn].playerY);
	printf("  ");
	if (moveCount > 0) {
		gotoxy(player[turn].playerX + 2, player[turn].playerY);
		printf("  ");
	}
	moveCount++;
	player[turn].playerBoard += i;
	if (player[turn].playerBoard > 31) {
		player[turn].playerBoard -= 32;
	}
	player[turn].playerX = local[player[turn].playerBoard].x;
	player[turn].playerY = local[player[turn].playerBoard].y;
	gotoxy(player[turn].playerX, player[turn].playerY);
	if (turn == 0) {
		printf("��");
		return;
	}
	gotoxy(player[turn].playerX + 2, player[turn].playerY);
	printf("��");

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
	getchar();
}