#include "draw.h"
#include "player.h"
#include "start.h"
#include <time.h>

Local local[32];
Player player[2];

void StartGame() {

	playerTurn();

	system("mode con: cols=130 lines=48");
	GameBoard();
	DrawPlayer();
	initLocal();
	initPlayerCoord();

	while (1) {
		int doubleCnt = 0;
		for (int i = 0; i < 2; i++) {
			Dice d;
			gotoxy(70, 25);
			printf("%s님의 차례입니다!", player[i].name);
			d = GameDice(i);
			movePlayer(d.sum, i);

			/*switch (player[i].board)
			{
			default:
				break;
			}*/

			if (d.dice1 == d.dice2) {

				if (doubleCnt > 1) {
					gotoxy(48, 24);
					printf("너무 앞서갔네요..무인도로 가세요");
					player[i].board = 9;
					Sleep(500);
					//getchar();
					gotoxy(48, 24);
					printf("                                  ");
					doubleCnt = 0;
				}
				else {
					DoubleDice();
					doubleCnt++;
					i--;
				}

			}
			else {
				doubleCnt = 0;
			}
		}
	}
}
void initLocal() {
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].name, localName[i]);
		strcpy(local[i].color, localColor[i]);
		local[i].price = localPrice[i];
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
	printf("◇");
	gotoxy(player[1].playerX + 2, player[1].playerY);
	printf("◆");
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
	player[turn].board += i;
	if (player[turn].board > 31) {
		player[turn].board -= 32;
	}
	player[turn].playerX = local[player[turn].board].x;
	player[turn].playerY = local[player[turn].board].y;
	gotoxy(player[turn].playerX, player[turn].playerY);
	if (turn == 0) {
		printf("◇");
		return;
	}
	gotoxy(player[turn].playerX + 2, player[turn].playerY);
	printf("◆");

}

void playerTurn() {

	printf("플레이어1의 이름을 입력해주세요 : ");
	scanf("%s", player[0].name);
	printf("플레이어2의 이름을 입력해주세요 : ");
	scanf("%s", player[1].name);

	printf("순서를 정합니다.\n");
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
	printf("%s님이 첫번째 차례네요.\n제일 먼저 시작하세요\n", player[0].name);
	getchar();
}