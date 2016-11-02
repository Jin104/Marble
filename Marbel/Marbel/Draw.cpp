#include "graphics.h"
#include "draw.h"
#include "local.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "start.h"

int doubleCount = 0;
int GameDice() {
	int dice, dice2;

	gotoxytext(48, 20, "주사위를 돌려주세요  ☞ Enter ☜");
	srand(time(NULL));
	while (1) {
		Sleep(50);
		dice = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
		DiceShape(dice);
		DiceShape2(dice2);
		if (kbhit()) {
			getchar();
			break;
		}
	}
	gotoxy(48, 22);
	printf("주사위의 값 : %d + %d = %d 입니다", dice, dice2, dice + dice2);

	if (dice == dice2) {
		gotoxy(48, 24);
		printf("더블입니다 한번 더 돌려주세요!");
		getchar();
		gotoxy(48, 24);
		printf("                                  ");
		movePlayer(dice + dice2, 0);
		return GameDice();
	}

	return dice + dice2;
}

int Double(int dice, int dice2) {
	int count = 0;

	gotoxy(48, 24);
	printf("더블입니다 한번 더 돌려주세요!");
	getchar();
	gotoxy(48, 24);
	printf("                                  ");

	count++;
	if (count == 3) {
		gotoxy(48, 24);
		printf("너무 앞서갔네요..무인도로 가세요");
		getchar();
		gotoxy(48, 24);
		printf("                                  ");
	}
	return 0;
}

void DiceShape(int dice) {

	if (dice == 1) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃          ┃");
		gotoxy(45, 15); printf("  ┃    ●    ┃");
		gotoxy(45, 16); printf("  ┃          ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
	if (dice == 2) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃    ●    ┃");
		gotoxy(45, 15); printf("  ┃          ┃");
		gotoxy(45, 16); printf("  ┃    ●    ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
	if (dice == 3) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃    ●    ┃");
		gotoxy(45, 15); printf("  ┃          ┃");
		gotoxy(45, 16); printf("  ┃ ●    ● ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
	if (dice == 4) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃ ●    ● ┃");
		gotoxy(45, 15); printf("  ┃          ┃");
		gotoxy(45, 16); printf("  ┃ ●    ● ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
	if (dice == 5) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃ ●    ● ┃");
		gotoxy(45, 15); printf("  ┃    ●    ┃");
		gotoxy(45, 16); printf("  ┃ ●    ● ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
	if (dice == 6) {
		gotoxy(45, 12); printf("  ┏━━━━━┓");
		gotoxy(45, 13); printf("  ┃          ┃");
		gotoxy(45, 14); printf("  ┃ ●    ● ┃");
		gotoxy(45, 15); printf("  ┃ ●    ● ┃");
		gotoxy(45, 16); printf("  ┃ ●    ● ┃");
		gotoxy(45, 17); printf("  ┃          ┃");
		gotoxy(45, 18); printf("  ┗━━━━━┛");
	}
}

void DiceShape2(int dice2) {

	if (dice2 == 1) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃          ┃");
		gotoxy(65, 15); printf("  ┃    ●    ┃");
		gotoxy(65, 16); printf("  ┃          ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
	if (dice2 == 2) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃    ●    ┃");
		gotoxy(65, 15); printf("  ┃          ┃");
		gotoxy(65, 16); printf("  ┃    ●    ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
	if (dice2 == 3) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃    ●    ┃");
		gotoxy(65, 15); printf("  ┃          ┃");
		gotoxy(65, 16); printf("  ┃ ●    ● ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
	if (dice2 == 4) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃ ●    ● ┃");
		gotoxy(65, 15); printf("  ┃          ┃");
		gotoxy(65, 16); printf("  ┃ ●    ● ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
	if (dice2 == 5) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃ ●    ● ┃");
		gotoxy(65, 15); printf("  ┃    ●    ┃");
		gotoxy(65, 16); printf("  ┃ ●    ● ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
	if (dice2 == 6) {
		gotoxy(65, 12); printf("  ┏━━━━━┓");
		gotoxy(65, 13); printf("  ┃          ┃");
		gotoxy(65, 14); printf("  ┃ ●    ● ┃");
		gotoxy(65, 15); printf("  ┃ ●    ● ┃");
		gotoxy(65, 16); printf("  ┃ ●    ● ┃");
		gotoxy(65, 17); printf("  ┃          ┃");
		gotoxy(65, 18); printf("  ┗━━━━━┛");
	}
}


//World Map
void GameBoard() {
	
	//외부 테두리
	gotoxytext(17, 1, "┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┓");
	for (int i = 2; i < 46; i++) {
		if (i % 5 == 1) {
			gotoxytext(17, i, "┣");
			gotoxytext(107, i, "┫");
		}
		else {
			gotoxytext(17, i, "┃");
			gotoxytext(107, i, "┃");
		}
	}
	gotoxytext(17, 46, "┗━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┛");

	//내부 테두리
	gotoxytext(27, 6, "╋━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━╋");
	for (int i = 7; i < 41; i++) {
		if (i % 5 == 1) {
			gotoxytext(27, i, "┫");
			gotoxytext(97, i, "┣");
		}
		else {
			gotoxytext(27, i, "┃");
			gotoxytext(97, i, "┃");
		}
	}
	gotoxytext(27, 41, "╋━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━╋");

	//윗쪽 세로선
	for (int i = 27; i < 107; i += 10) {
		for (int j = 2; j < 6; j++) {
			gotoxytext(i, j, "┃");
		}
	}

	//아랫쪽 세로선
	for (int i = 27; i < 107; i += 10) {
		for (int j = 42; j < 46; j++) {
			gotoxytext(i, j, "┃");
		}
	}
	
	//왼쪽 가로선
	for (int j = 6; j < 46; j+=5) {
		for (int i = 19; i < 26; i+=2) {
			gotoxytext(i, j, "━");
		}
	}

	//오른쪽 가로선
	for (int j = 6; j < 46; j += 5) {
		for (int i = 99; i < 106; i+=2) {
			gotoxytext(i, j, "━");
		}
	}

	int i = 0;
	for (int j = 42; j > 5; j -= 5) {
		gotoxy(19, j); printf("%s", localName[i]);
		i++;
	}
	for (int j = 19; j < 105; j += 10) {
		gotoxy(j, 2); printf("%s", localName[i]);
		i++;
	}
	for (int j = 7; j < 47; j += 5) {
		gotoxy(99, j); printf("%s", localName[i]);
		i++;
	}
	for (int j = 89; j > 22; j -= 10) {
		gotoxy(j, 42); printf("%s", localName[i]);
		i++;
	}
}

//Player
void DrawPlayer() {

	gotoxytext(29, 7, "┏━━━━━━━━━━━━┓");
	gotoxytext(29, 8, "┃                        ┃");
	gotoxytext(29, 9, "┃                        ┃");
	gotoxytext(29, 10, "┃                        ┃");
	gotoxytext(29, 11, "┗━━━━━━━━━━━━┛");

	gotoxytext(40, 8, "님");
	gotoxytext(31, 10, "보유마블: ");

	gotoxytext(69, 36, "┏━━━━━━━━━━━━┓");
	gotoxytext(69, 37, "┃                        ┃");
	gotoxytext(69, 38, "┃                        ┃");
	gotoxytext(69, 39, "┃                        ┃");
	gotoxytext(69, 40, "┗━━━━━━━━━━━━┛");

	gotoxytext(80, 37, "님");
	gotoxytext(71, 39, "보유마블: ");
}

//
//void DrawMap() {
//	GameBoard();
//	DrawPlayer();
//	GameDice();
//	system("pause>null");
//}

void Loading() {


}

void Explain() {


}

