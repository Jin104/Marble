#include "graphics.h"
#include "draw.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void GameDice() {
	int dice, dice2;

	//gotoxytext(20, 5, "�ֻ����� �����ּ���  �� Enter ��r");
	//getchar();

	srand(time(NULL));
	dice = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;

	gotoxy(20, 8);
	//printf("�ֻ����� �� : %d + %d = %d �Դϴ�.", dice, dice2, dice + dice2);

	gotoxy(0, 3);
	DiceShape(dice);
	gotoxy(0, 10);
	DiceShape(dice2);

}
void DiceShape(int dice) {

	if (dice == 1) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  ��          ��");
		puts("  ��    ��    ��");
		puts("  ��          ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
	if (dice == 2) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  ��    ��    ��");
		puts("  ��          ��");
		puts("  ��    ��    ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
	if (dice == 3) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  ��    ��    ��");
		puts("  ��          ��");
		puts("  �� ��    �� ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
	if (dice == 4) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  �� ��    �� ��");
		puts("  ��          ��");
		puts("  �� ��    �� ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
	if (dice == 5) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  �� ��    �� ��");
		puts("  ��    ��    ��");
		puts("  �� ��    �� ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
	if (dice == 6) {
		puts("  ��������������");
		puts("  ��          ��");
		puts("  �� ��    �� ��");
		puts("  �� ��    �� ��");
		puts("  �� ��    �� ��");
		puts("  ��          ��");
		puts("  ��������������");
	}
}

void Explain() {

}

//World Map
void GameBoard() {
	
	//�ܺ� �׵θ�
	gotoxytext(17, 1, "��������������������������������������������������������������������������������������������");
	for (int i = 2; i < 46; i++) {
		if (i % 5 == 1) {
			gotoxytext(17, i, "��");
			gotoxytext(107, i, "��");
		}
		else {
			gotoxytext(17, i, "��");
			gotoxytext(107, i, "��");
		}
	}
	gotoxytext(17, 46, "��������������������������������������������������������������������������������������������");

	//���� �׵θ�
	gotoxytext(27, 6, "������������������������������������������������������������������������");
	for (int i = 7; i < 41; i++) {
		if (i % 5 == 1) {
			gotoxytext(27, i, "��");
			gotoxytext(97, i, "��");
		}
		else {
			gotoxytext(27, i, "��");
			gotoxytext(97, i, "��");
		}
	}
	gotoxytext(27, 41, "������������������������������������������������������������������������");

	//���� ���μ�
	for (int i = 27; i < 107; i += 10) {
		for (int j = 2; j < 6; j++) {
			gotoxytext(i, j, "��");
		}
	}

	//�Ʒ��� ���μ�
	for (int i = 27; i < 107; i += 10) {
		for (int j = 42; j < 46; j++) {
			gotoxytext(i, j, "��");
		}
	}
	
	//���� ���μ�
	for (int j = 6; j < 46; j+=5) {
		for (int i = 19; i < 26; i+=2) {
			gotoxytext(i, j, "��");
		}
	}

	//������ ���μ�
	for (int j = 6; j < 46; j += 5) {
		for (int i = 99; i < 106; i+=2) {
			gotoxytext(i, j, "��");
		}
	}
}

//Player
void DrawPlayer() {

	gotoxytext(1, 30, "����������������");

}


void DrawMap() {
	GameBoard();
	GameDice();
	DrawPlayer();
	system("pause>null");
}