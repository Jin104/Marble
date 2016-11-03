#include "draw.h"
#include "local.h"
#include "start.h"
#include <time.h>
#include <stdlib.h>


extern Player player[2];

int doubleCount = 0;
int turnCount = 0;

Dice GameDice(int i) {
	
	Dice d;
	gotoxy(48, 22);
	printf("                                     ");
	gotoxytext(48, 20, "주사위를 돌려주세요  ☞ Enter ☜");
	turnCount++;
	srand(time(NULL));
	while (1) {
		Sleep(50);
		d.dice1 = rand() % 2 + 1;
		d.dice2 = rand() % 2 + 1;
		d.sum = d.dice1 + d.dice2;
		DiceShape(d.dice1);
		DiceShape2(d.dice2);
		if (kbhit()) {
			getchar();
			break;
		}
	}
	gotoxy(48, 22);
	printf("주사위의 값 : %d + %d = %d 입니다", d.dice1, d.dice2, d.sum);
	Sleep(500);
	//getchar();
	return d;
}

//int GameDice() {
//	int dice, dice2;
//	gotoxy(48, 22);
//	printf("                                     ");
//	gotoxytext(48, 20, "주사위를 돌려주세요  ☞ Enter ☜");
//	turnCount++;
//	srand(time(NULL));
//	while (1) {
//		Sleep(50);
//		dice = rand() % 6 + 1;
//		dice2 = rand() % 6 + 1;
//		DiceShape(dice);
//		DiceShape2(dice2);
//		if (kbhit()) {
//			getchar();
//			break;
//		}
//	}
//	gotoxy(48, 22);
//	printf("주사위의 값 : %d + %d = %d 입니다", dice, dice2, dice + dice2);
//	Sleep(500);
//	//getchar();
//	if (dice == dice2) {
//		if (doubleCount == 2) {
//			gotoxy(48, 24);
//			printf("너무 앞서갔네요..무인도로 가세요");
//			Sleep(500);
//			//getchar();
//			gotoxy(48, 24);
//			printf("                                  ");
//			doubleCount = 0;
//			return 0;
//		}else{
//			doubleCount = 1;
//		}
//		turnCount--;
//		gotoxy(48, 24);
//		printf("더블입니다 한번 더 돌려주세요!");
//		Sleep(500);
//		//getchar();
//		gotoxy(48, 24);
//		printf("                                  ");
//		movePlayer(dice + dice2, turnCount%2);
//		return GameDice();
//	}
//
//	return dice + dice2;
//}

void DoubleDice() {
	gotoxy(48, 24);
	printf("더블입니다 한번 더 돌려주세요!");
	Sleep(500);
	//getchar();
	gotoxy(48, 24);
	printf("                                  ");


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

void Loading() {

	system("mode con:cols=130 lines=48");
	gotoxy(25, 10); BLUE_GREEN printf("┏━━━━━┓");
	gotoxy(25, 11); printf("┃ ┏━━┓ ┃");
	gotoxy(25, 12); printf("┃ ┃    ┃ ┃");
	gotoxy(25, 13); printf("┃ ┗━━┛ ┃");
	gotoxy(25, 14); printf("┗━┓  ┏━┛");
	gotoxy(25, 15); printf("    ┃  ┃  ");
	gotoxy(25, 16); printf("    ┃  ┃  ");
	gotoxy(25, 17); printf("┏━┛  ┗━┓");
	gotoxy(25, 18); printf("┃          ┃");
	gotoxy(25, 19); printf("┗━━━━━┛");

	gotoxy(39, 11); printf("┏━━━━━┓");
	gotoxy(39, 12); printf("┃  ┏━━━┛");
	gotoxy(39, 13); printf("┃  ┃      ");
	gotoxy(39, 14); printf("┃  ┗━━━┓");
	gotoxy(39, 15); printf("┗━━━━━┛");
	gotoxy(39, 16); printf("┏━━━━━┓");
	gotoxy(39, 17); printf("┃          ┃");
	gotoxy(39, 18); printf("┗━┓  ┏━┛");
	gotoxy(39, 19); printf("    ┃  ┃  ");
	gotoxy(39, 20); printf("    ┃  ┃  ");
	gotoxy(39, 21); printf("    ┗━┛");

	gotoxy(53, 12); printf("  ━━━  ┏┓");
	gotoxy(53, 13); printf("┃┏━┓┃┃┃");
	gotoxy(53, 14); printf("┃┗━┛┃┃┃");
	gotoxy(53, 15); printf("  ━━━  ┃┃");
	gotoxy(53, 16); printf("┏━━━┓┃┃");
	gotoxy(53, 17); printf("┗━━━┛┗┛");

	gotoxy(67, 10); printf("            ┏┓");
	gotoxy(67, 11); printf("┏━━━━┓┃┃");
	gotoxy(67, 12); printf("┃        ┃┃┃");
	gotoxy(67, 13); printf("┃┏━━┓┃┃┃");
	gotoxy(67, 14); printf("┃┃    ┃┃┃┗┓");
	gotoxy(67, 15); printf("┃┃    ┃┃┃┏┛");
	gotoxy(67, 16); printf("┃┃    ┃┃┃┃");
	gotoxy(67, 17); printf("┃┗━━┛┃┃┃");
	gotoxy(67, 18); printf("┃        ┃┃┃");
	gotoxy(67, 19); printf("┗━━━━┛┃┃");
	gotoxy(67, 20); printf("            ┗┛");

	gotoxy(85, 10); printf("┏━┓    ┏━┓");;
	gotoxy(85, 11); printf("┃  ┗━━┛  ┃");
	gotoxy(85, 12); printf("┃  ┏━━┓  ┃");
	gotoxy(85, 13); printf("┃  ┗━━┛  ┃");
	gotoxy(85, 14); printf("┗━━━━━━┛");
	gotoxy(85, 15); printf("┏━━━━━━┓");
	gotoxy(85, 16); printf("┗━━━━━━┛");
	gotoxy(85, 17); printf("┏━━━━━━┓");
	gotoxy(85, 18); printf("┗━━━━━┓┃");
	gotoxy(85, 19); printf("┏━━━━━┛┃");
	gotoxy(85, 20); printf("┃┏━━━━━┛");
	gotoxy(85, 21); printf("┃┗━━━━━┓");
	gotoxy(85, 22); printf("┗━━━━━━┛");;


	gotoxy(45, 30); printf("L");
	Sleep(200);
	gotoxy(50, 30); printf("O");
	Sleep(200);
	gotoxy(55, 30); printf("A");
	Sleep(200);
	gotoxy(60, 30); printf("D");
	Sleep(200);
	gotoxy(65, 30); printf("I");
	Sleep(200);
	gotoxy(70, 30); printf("N");
	Sleep(200);
	gotoxy(75, 30); printf("G");
	Sleep(200);
	gotoxy(45, 32); printf("▶");
	Sleep(200);
	gotoxy(50, 32); printf("▶");
	Sleep(200);
	gotoxy(55, 32); printf("▶");
	Sleep(200);
	gotoxy(60, 32); printf("▶");
	Sleep(200);
	gotoxy(65, 32); printf("▶");
	Sleep(200);
	gotoxy(70, 32); printf("▶");
	Sleep(200);
	gotoxy(75, 32); printf("▶");
	Sleep(200);
	ORIGINAL
	system("cls");


}

void Explain() {


}

