#include "graphics.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void GameDice() {
	int dice, dice2;
	srand(time(NULL));
	dice = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;

	gotoxy(5, 5);
	printf("주사위의 값 : %d + %d = %d입니다.", dice, dice2, dice + dice2);
	gotoxytext(110, 5, "┏━━━━┓");
	gotoxytext(110, 6, "┃       ┃");
}

void explain() {

}

void GameBoard() {

}
