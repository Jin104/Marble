#include "graphics.h"
#include "draw.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "player.h"
#include "start.h"
#include "local.h"

int turn = 0;

Local local[32];
Player player[2];
void StartGame() {
	
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].localName, localName[i]);
		strcpy(local[i].localColor, localColor[i]);
		local[i].localPrice = localPrice[i];
		local[i].x = localX[i];
		local[i].y = localY[i];
	}

	printf("플레이어1의 이름을 입력해주세요 : ");
	scanf("%s", player[0].name);
	printf("플레이어2의 이름을 입력해주세요 : ");
	scanf("%s", player[1].name);

	system("mode con: cols=130 lines=48");

	GameBoard();
	DrawPlayer();
	
	initPlayerCoord();

	while (1) {
		int i = GameDice();
		movePlayer(i,turn);
		system("pause>null");
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

void movePlayer(int i, int turn) {
	gotoxy(player[turn].playerX, player[turn].playerY);
	printf("  ");
	player[turn].playerBoard += i;
	if (player[turn].playerBoard > 31) {
		player[turn].playerBoard -= 32;
	}
	player[turn].playerX = local[player[turn].playerBoard].x;
	player[turn].playerY = local[player[turn].playerBoard].y;
	gotoxy(player[turn].playerX, player[turn].playerY);
	if (turn == 0) {
		printf("◇");
		turn = 1;
		return;
	}
	printf("◆");
}

