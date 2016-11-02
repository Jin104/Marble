#include "graphics.h"
#include "draw.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "player.h"
#include "start.h"
#include "local.h"

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
	gotoxy(player[0].playerX, player[0].playerY);
	printf("◇");
	gotoxy(player[1].playerX+2, player[1].playerY);
	printf("◆");

	while (1) {
		int i = GameDice();
		movePlayer(i);
		gotoxy(48, 22);
		printf("주사위의 값은 = %d 입니다", i);
		getchar();
		gotoxy(48, 22);
		printf("                                 ");
		if (i == -1) {
			gotoxy(48, 24);
			printf("더블입니다 한번 더 돌려주세요!");
			getchar();
			gotoxy(48, 24);
			printf("                                  ");
			int j =GameDice();
			gotoxy(48, 22);
			printf("주사위의 값은 = %d 입니다", j);
			movePlayer(j);
		}
	}
}


void movePlayer(int i) {
	gotoxy(player[0].playerX, player[0].playerY);
	printf("  ");
	player[0].playerBoard += i;
	if (player[0].playerBoard > 31) {
		player[0].playerBoard -= 32;
	}
	player[0].playerX = local[player[0].playerBoard].x;
	player[0].playerY = local[player[0].playerBoard].y;
	gotoxy(player[0].playerX, player[0].playerY);
	printf("◇");
}
