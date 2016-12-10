#include "Start.h"
#include "Player.h"
#include <stdlib.h>

extern Player player[4];

//À¯³ª ÁÖ»çÀ§
Dice GameDice(int i) {
	Sleep(500);
	Dice d;
	gotoxy(48, 22);
	printf("                                     ");
	gotoxytext(48, 20, "ÁÖ»çÀ§¸¦ µ¹·ÁÁÖ¼¼¿ä  ¢Ñ Enter ¢Ð");

	srand(time(NULL));
	while (1) {
		Sleep(100);
		//ÁÖ»çÀ§ 1ºÎÅÍ 6±îÁö ·£´ý
		d.dice1 = rand() % 6 + 1;
		d.dice2 = rand() % 6 + 1;
		d.sum = d.dice1 + d.dice2;
		DiceShape(d.dice1);
		DiceShape2(d.dice2);
		// ÁÖ»çÀ§ ¸ð¾çÀÌ µ¹¾Æ°¡´Âµ¥ Å°¸¦ ´©¸£¸é ¸ØÃã
		if (kbhit()) {
			getch();
			sndPlaySoundA("..\\sound\\DiceItem00000_Swing.wav", SND_ASYNC | SND_NODEFAULT);
			break;
		}
	}
	//d.dice1 = 4;// rand() % 6 + 1;
	//d.dice2 = 2;// rand() % 6 + 1;
	//d.sum = d.dice1 + d.dice2;
	if (d.dice1 == d.dice2) {
		sndPlaySoundA("..\\sound\\Double_A01.wav", SND_ASYNC | SND_NODEFAULT);
		d.equal = 1;
	}
	gotoxy(48, 22);
	printf("ÁÖ»çÀ§ÀÇ °ªÀº %d ÀÔ´Ï´Ù", d.sum);
	Sleep(500);
	gotoxy(48, 20);
	printf("                                     ");
	return d;
}

//À¯³ª
//ÁÖ»çÀ§ ´õºí
void DoubleDice() {
	gotoxy(48, 24);
	printf("´õºíÀÔ´Ï´Ù ÇÑ¹ø ´õ µ¹·ÁÁÖ¼¼¿ä!");
	Sleep(500);
	gotoxy(48, 24);
	printf("                                  ");
}

//À¯³ª
//ÁÖ»çÀ§ µðÀÚÀÎ
void DiceShape(int dice) {

	if (dice == 1) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­          ¦­");
		gotoxy(45, 15); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(45, 16); printf("  ¦­          ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice == 2) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(45, 15); printf("  ¦­          ¦­");
		gotoxy(45, 16); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice == 3) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(45, 15); printf("  ¦­          ¦­");
		gotoxy(45, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice == 4) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 15); printf("  ¦­          ¦­");
		gotoxy(45, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice == 5) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 15); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(45, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice == 6) {
		gotoxy(45, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(45, 13); printf("  ¦­          ¦­");
		gotoxy(45, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 15); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(45, 17); printf("  ¦­          ¦­");
		gotoxy(45, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
}

void DiceShape2(int dice2) {

	if (dice2 == 1) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­          ¦­");
		gotoxy(65, 15); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(65, 16); printf("  ¦­          ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice2 == 2) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(65, 15); printf("  ¦­          ¦­");
		gotoxy(65, 16); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice2 == 3) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(65, 15); printf("  ¦­          ¦­");
		gotoxy(65, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice2 == 4) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 15); printf("  ¦­          ¦­");
		gotoxy(65, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice2 == 5) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 15); printf("  ¦­    ¡Ü    ¦­");
		gotoxy(65, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
	if (dice2 == 6) {
		gotoxy(65, 12); printf("  ¦®¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxy(65, 13); printf("  ¦­          ¦­");
		gotoxy(65, 14); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 15); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 16); printf("  ¦­ ¡Ü    ¡Ü ¦­");
		gotoxy(65, 17); printf("  ¦­          ¦­");
		gotoxy(65, 18); printf("  ¦±¦¬¦¬¦¬¦¬¦¬¦°");
	}
}

/*°ÔÀÓÆÇ ±×·ÁÁÜ*/
void GameBoard() {

	//¿ÜºÎ Å×µÎ¸®
	gotoxytext(17, 1, "¦®¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¯");
	for (int i = 2; i < 46; i++) {
		if (i % 5 == 1) {
			gotoxytext(17, i, "¦²");
			gotoxytext(107, i, "¦´");
		}
		else {
			gotoxytext(17, i, "¦­");
			gotoxytext(107, i, "¦­");
		}
	}
	gotoxytext(17, 46, "¦±¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦°");

	//³»ºÎ Å×µÎ¸®
	gotoxytext(27, 6, "¦¶¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¶");
	for (int i = 7; i < 41; i++) {
		if (i % 5 == 1) {
			gotoxytext(27, i, "¦´");
			gotoxytext(97, i, "¦²");
		}
		else {
			gotoxytext(27, i, "¦­");
			gotoxytext(97, i, "¦­");
		}
	}
	gotoxytext(27, 41, "¦¶¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¶");

	//À­ÂÊ ¼¼·Î¼±
	for (int i = 27; i < 107; i += 10) {
		for (int j = 2; j < 6; j++) {
			gotoxytext(i, j, "¦­");
		}
	}

	//¾Æ·§ÂÊ ¼¼·Î¼±
	for (int i = 27; i < 107; i += 10) {
		for (int j = 42; j < 46; j++) {
			gotoxytext(i, j, "¦­");
		}
	}

	//¿ÞÂÊ °¡·Î¼±
	for (int j = 6; j < 46; j += 5) {
		for (int i = 19; i < 26; i += 2) {
			gotoxytext(i, j, "¦¬");
		}
	}

	//¿À¸¥ÂÊ °¡·Î¼±
	for (int j = 6; j < 46; j += 5) {
		for (int i = 99; i < 106; i += 2) {
			gotoxytext(i, j, "¦¬");
		}
	}


	//À¯³ª - °ÔÀÓÆÇ¿¡ Áö¿ªÀÌ¸§ Ãâ·Â, »ö ÁöÁ¤
	int i = 0;

	//¿ÞÂÊ ¼¼·ÎÁÙ
	for (int j = 42; j > 5; j -= 5) {
		gotoxy(19, j); printf("%8s", localName[i]);
		if (i == 0 || i == 2) {
			settextcolor(0, 10);
		}
		else if (i == 1) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 3) {
			settextcolor(0, 3);
		}
		else if (i == 4 || i == 5 || i == 6) {
			settextcolor(0, 2);
		}
		i++;
	}
	settextcolor(0x0007, 007700);
	//À§ÂÊ °¡·ÎÁÙ
	for (int j = 19; j < 105; j += 10) {
		gotoxy(j, 2); printf("%8s", localName[i]);
		if (i == 8) {
			settextcolor(0, 3);
		}
		else if (i == 9 || i == 10) {
			settextcolor(0, 9);
		}
		else if (i == 11) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 12 || i == 14) {
			settextcolor(0, 1);
		}
		else if (i == 13) {
			settextcolor(0, 3);
		}
		else if (i == 15) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 16) {
			settextcolor(0, 13);
		}
		i++;
	}
	//¿À¸¥ÂÊ ¼¼·ÎÁÙ
	for (int j = 7; j < 47; j += 5) {
		gotoxy(99, j); printf("%8s", localName[i]);
		if (i == 17) {
			settextcolor(0, 3);
		}
		else if (i == 18) {
			settextcolor(0, 13);
		}
		else if (i == 19) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 20 || i == 21 || i == 22) {
			settextcolor(0, 5);
		}
		else if (i == 23) {
			settextcolor(0x0007, 007700);
		}
		i++;
	}
	settextcolor(0x0007, 007700);
	//¾Æ·¡ÂÊ °¡·ÎÁÙ
	for (int j = 89; j > 22; j -= 10) {
		if (i == 25) {
			settextcolor(0, 3);
		}
		else if (i == 26 || i == 27) {
			settextcolor(0, 12);
		}
		else if (i == 28) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 29) {
			settextcolor(0, 4);
		}
		else if (i == 30) {
			settextcolor(0x0007, 007700);
		}
		else if (i == 31) {
			settextcolor(0, 4);
		}
		gotoxy(j, 42); printf("%8s", localName[i]);
		settextcolor(0x0007, 007700);
		i++;
	}

	//À¯³ª
	//ÅØ½ºÆ® Ã¢
	gotoxytext(32, 24, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	for (int i = 25; i<35; i++) {
		gotoxytext(32, i, "¦­");
		gotoxytext(92, i, "¦­");
	}
	gotoxytext(32, 35, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");


}

/*ÇÃ·¹ÀÌ¾îÁ¤º¸ÆÇ ±×·ÁÁÜ*/
void DrawPlayer(int totalNumber) {

	gotoxytext(29, 7, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxytext(29, 8, "¦­                        ¦­");
	gotoxytext(29, 9, "¦­                        ¦­");
	gotoxytext(29, 10, "¦­                        ¦­");
	gotoxytext(29, 11, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	gotoxytext(31, 10, "º¸À¯¸¶ºí: ");

	gotoxytext(69, 36, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxytext(69, 37, "¦­                        ¦­");
	gotoxytext(69, 38, "¦­                        ¦­");
	gotoxytext(69, 39, "¦­                        ¦­");
	gotoxytext(69, 40, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	gotoxytext(71, 39, "º¸À¯¸¶ºí: ");

	if (totalNumber == 3 || totalNumber == 4) {
		gotoxytext(29, 36, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		gotoxytext(29, 37, "¦­                        ¦­");
		gotoxytext(29, 38, "¦­                        ¦­");
		gotoxytext(29, 39, "¦­                        ¦­");
		gotoxytext(29, 40, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		gotoxytext(31, 39, "º¸À¯¸¶ºí: ");

		if (totalNumber == 4) {
			gotoxytext(69, 7, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
			gotoxytext(69, 8, "¦­                        ¦­");
			gotoxytext(69, 9, "¦­                        ¦­");
			gotoxytext(69, 10, "¦­                        ¦­");
			gotoxytext(69, 11, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

			gotoxytext(71, 10, "º¸À¯¸¶ºí: ");
		}
	}
}

//À¯³ª
//°ÔÀÓ ½ÃÀÛÇÒ¶§ ·ÎµùÈ­¸é
void Loading() {

	system("mode con:cols=130 lines=48"); //ÄÜ¼ÖÃ¢ Å©±â
	gotoxy(25, 10); DARK_SKY_BLUE printf("¦®¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(25, 11); printf("¦­ ¦®¦¬¦¬¦¯ ¦­");
	gotoxy(25, 12); printf("¦­ ¦­    ¦­ ¦­");
	gotoxy(25, 13); printf("¦­ ¦±¦¬¦¬¦° ¦­");
	gotoxy(25, 14); printf("¦±¦¬¦¯  ¦®¦¬¦°");
	gotoxy(25, 15); printf("    ¦­  ¦­  ");
	gotoxy(25, 16); printf("    ¦­  ¦­  ");
	gotoxy(25, 17); printf("¦®¦¬¦°  ¦±¦¬¦¯");
	gotoxy(25, 18); printf("¦­          ¦­");
	gotoxy(25, 19); printf("¦±¦¬¦¬¦¬¦¬¦¬¦°");

	gotoxy(39, 11); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(39, 12); printf("¦­  ¦®¦¬¦¬¦¬¦°");
	gotoxy(39, 13); printf("¦­  ¦­      ");
	gotoxy(39, 14); printf("¦­  ¦±¦¬¦¬¦¬¦¯");
	gotoxy(39, 15); printf("¦±¦¬¦¬¦¬¦¬¦¬¦°");
	gotoxy(39, 16); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(39, 17); printf("¦­          ¦­");
	gotoxy(39, 18); printf("¦±¦¬¦¯  ¦®¦¬¦°");
	gotoxy(39, 19); printf("    ¦­  ¦­  ");
	gotoxy(39, 20); printf("    ¦­  ¦­  ");
	gotoxy(39, 21); printf("    ¦±¦¬¦°");

	gotoxy(53, 12); printf("  ¦¬¦¬¦¬  ¦®¦¯");
	gotoxy(53, 13); printf("¦­¦®¦¬¦¯¦­¦­¦­");
	gotoxy(53, 14); printf("¦­¦±¦¬¦°¦­¦­¦­");
	gotoxy(53, 15); printf("  ¦¬¦¬¦¬  ¦­¦­");
	gotoxy(53, 16); printf("¦®¦¬¦¬¦¬¦¯¦­¦­");
	gotoxy(53, 17); printf("¦±¦¬¦¬¦¬¦°¦±¦°");

	gotoxy(67, 10); printf("            ¦®¦¯");
	gotoxy(67, 11); printf("¦®¦¬¦¬¦¬¦¬¦¯¦­¦­");
	gotoxy(67, 12); printf("¦­        ¦­¦­¦­");
	gotoxy(67, 13); printf("¦­¦®¦¬¦¬¦¯¦­¦­¦­");
	gotoxy(67, 14); printf("¦­¦­    ¦­¦­¦­¦±¦¯");
	gotoxy(67, 15); printf("¦­¦­    ¦­¦­¦­¦®¦°");
	gotoxy(67, 16); printf("¦­¦­    ¦­¦­¦­¦­");
	gotoxy(67, 17); printf("¦­¦±¦¬¦¬¦°¦­¦­¦­");
	gotoxy(67, 18); printf("¦­        ¦­¦­¦­");
	gotoxy(67, 19); printf("¦±¦¬¦¬¦¬¦¬¦°¦­¦­");
	gotoxy(67, 20); printf("            ¦±¦°");

	gotoxy(85, 10); printf("¦®¦¬¦¯    ¦®¦¬¦¯");;
	gotoxy(85, 11); printf("¦­  ¦±¦¬¦¬¦°  ¦­");
	gotoxy(85, 12); printf("¦­  ¦®¦¬¦¬¦¯  ¦­");
	gotoxy(85, 13); printf("¦­  ¦±¦¬¦¬¦°  ¦­");
	gotoxy(85, 14); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦°");
	gotoxy(85, 15); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(85, 16); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦°");
	gotoxy(85, 17); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(85, 18); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¯¦­");
	gotoxy(85, 19); printf("¦®¦¬¦¬¦¬¦¬¦¬¦°¦­");
	gotoxy(85, 20); printf("¦­¦®¦¬¦¬¦¬¦¬¦¬¦°");
	gotoxy(85, 21); printf("¦­¦±¦¬¦¬¦¬¦¬¦¬¦¯");
	gotoxy(85, 22); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦°");;


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
	gotoxy(45, 32); printf("¢º");
	Sleep(200);
	gotoxy(50, 32); printf("¢º");
	Sleep(200);
	gotoxy(55, 32); printf("¢º");
	Sleep(200);
	gotoxy(60, 32); printf("¢º");
	Sleep(200);
	gotoxy(65, 32); printf("¢º");
	Sleep(200);
	gotoxy(70, 32); printf("¢º");
	Sleep(200);
	gotoxy(75, 32); printf("¢º");
	Sleep(200);
	GRAY

}

//À¯³ª
//°ÔÀÓ ¸Þ´º
void Menu() {

	clrText();

	settextcolor(0x0007, 000000);
	gotoxytext(50, 28, "¢Ñ");

	settextcolor(0, 3);
	gotoxytext(55, 28, "[1] °ÔÀÓ ½ÃÀÛ");
	settextcolor(0x0007, 000000);
	gotoxytext(55, 30, "[2] °ÔÀÓ ¼³¸í");

}

//À¯³ª
//°ÔÀÓ ¼³¸í Ã¢
void Explain() {

	int select;
	gotoxy(20, 5); DARK_SKY_BLUE
		printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦³¦¬¦¬¦³¦¬¦¬¦¯");
	for (int i = 6; i<42; i++) {
		gotoxytext(20, i, "¦­");
		gotoxytext(106, i, "¦­");
	}
	gotoxy(25, 7); printf("°ÔÀÓ ½ÃÀÛÀº Enter¸¦ ´­·¯ÁÖ¼¼¿ä!");
	gotoxy(91, 7); printf("¦¬"); gotoxy(96, 6); printf("¦®¦¯"); gotoxy(96, 7); printf("¦±¦°"); gotoxy(103, 7); printf("¥¹");
	gotoxy(88, 6); printf("¦­"); gotoxy(94, 6); printf("¦­"); gotoxy(100, 6); printf("¦­");
	gotoxy(88, 7); printf("¦­"); gotoxy(94, 7); printf("¦­"); gotoxy(100, 7); printf("¦­");
	gotoxy(20, 8); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦µ¦¬¦¬¦µ¦¬¦¬¦´");
	gotoxy(20, 42); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
	GRAY
		gotoxy(25, 11); printf("[1] °ÔÀÓ ½ÃÀÛÇÏ±â¸¦ ¼±ÅÃÇÏ¸é °ÔÀÓÀÌ ½ÃÀÛ");
	gotoxy(25, 13); printf("[2] ÇÃ·¹ÀÌ¾î´Â 2¸íÀ¸·Î Á¦ÇÑ, Ä«µå¼±ÅÃÀ¸·Î ¼ø¼­¸¦ °áÁ¤");
	gotoxy(25, 15); printf("[3] ÁÖ»çÀ§¸¦ ±¼·Á ³ª¿Â ¸¸Å­ ÀüÁø, µµÂøÇÑ µµ½Ã¿¡ È£ÅÚ ÁöÀ» ¼ö ÀÖÀ½");
	gotoxy(25, 16); printf("[4] È£ÅÚÀ» ÁöÀº ÀÚ½ÅÀÇ Áö¿ª¿¡ µµÂø ½Ã ·£µå ¸¶Å© °Ç¼³");
	gotoxy(27, 17); printf("  ¶Ç´Â Ãâ¹ßÁöÁ¡À¸·Î °¡¸é ÀÚ½ÅÀÇ Áö¿ª ÇÑ °÷¿¡ °Ç¹° °Ç¼³ °¡´É");
	gotoxy(25, 20); printf("[5] ´Ù¸¥ ÇÃ·¹ÀÌ¾îÀÇ Áö¿ª¿¡ µµÂøÇßÀ» ½Ã ÅëÇà·á ÁöºÒ°ú Áö¿ª & °Ç¹° ÀÎ¼ö °¡´É");
	gotoxy(27, 21); printf("   ¢Ñ ´Ü, ·£µå ¸¶Å©³ª °ü±¤Áö´Â ÀÎ¼ö ºÒ°¡´É");
	gotoxy(25, 23); printf("[6] Çà¿î Ä«µå¿¡ µµÂø ½Ã, ³ª¿À´Â Ä«µå ³»¿ëÀ» ¼öÇà");
	gotoxy(25, 25); printf("[7] ¼¼°è¿©Çà¿¡ µµÂø ½Ã, ºñ¿ëÀ» ÁöºÒÇÏ°í ´ÙÀ½ ÅÏ¿¡ ¿øÇÏ´Â Áö¿ªÀ¸·Î ÀÌµ¿ °¡´É");
	gotoxy(25, 26); printf("[8] ¹«ÀÎµµ¿¡ µµÂø ½Ã, ÁÖ»çÀ§ ´õºíÀÌ ³ª¿À°Å³ª, µ·À» ÁöºÒÇØ¾ß Å»Ãâ °¡´É!");
	gotoxy(27, 27); printf("  Å»ÃâÀ» ¸øÇßÀ» °æ¿ì »ó´ë¹æÀ¸·Î ÅÏÀÌ ³Ñ¾î °¨. ÃÖ´ë 3È¸!");
	gotoxy(25, 30); printf("[9] ¿Ã¸²ÇÈ¿¡ µµÂø ½Ã, ÀÚ½ÅÀÇ ¶¥ ÇÑ°÷ÀÇ ÅëÇà·á¸¦ 2¹è·Î »ó½Â");
	gotoxy(25, 32); printf("[10] ½Â¸® Á¶°Ç : ¶óÀÎµ¶Á¡, Æ®¸®ÇÃ µ¶Á¡, °ü±¤Áö µ¶Á¡, »ó´ë¹æ ÆÄ»ê");
	gotoxy(25, 34); printf("    ¢Ñ ¶óÀÎ µ¶Á¡ ¦¡ ÇÑ ÁÙ¿¡ ÀÖ´Â Áö¿ªÀ» ¸ðµÎ Â÷Áö");
	gotoxy(25, 35); printf("    ¢Ñ Æ®¸®ÇÃ µ¶Á¡ ¦¡ 3°¡Áö ÄÃ·¯ÀÇ ¸ðµç Áö¿ªÀ» Â÷Áö");
	gotoxy(25, 36); printf("    ¢Ñ °ü±¤Áö µ¶Á¡ ¦¡ 5°³ÀÇ °ü±¤Áö¸¦ ¸ðµÎ Â÷Áö");
	gotoxy(25, 37); printf("    ¢Ñ ÆÄ»ê ¦¡ »ó´ë¹æÀÇ º¸À¯¸¶ºí ºÎÁ·");

	if (select = _getch()) { //Å°¸¦ ´©¸£¸é °ÔÀÓ½ÃÀÛ
		system("cls");
		//StartGame();
	}

}

/*ÇÃ·¹ÀÌ¾îÀÇ ¸¶ºí»óÅÂ¸¦ ±×·ÁÁÜ*/
void PlayerState() {
	gotoxy(42, 10); printf("             ");
	gotoxy(42, 10); printf("%d", player[0].marble);
	gotoxy(82, 39); printf("             ");
	gotoxy(82, 39); printf("%d", player[1].marble);

	//if (totalNumber == 3 || totalNumber == 4) {
	//	gotoxy(42, 39); printf("             ");
	//	gotoxy(42, 39); printf("%d", player[0].marble);

	//	if (totalNumber == 4) {
	//		gotoxy(82, 10); printf("             ");
	//		gotoxy(82, 10); printf("%d", player[0].marble);
	//	}
	//}
}

/*ÅØ½ºÆ®È­¸é Áö¿ì±â*/
void clrText() {
	for (int i = 25; i < 35; i++) {
		gotoxytext(34, i, "                                                         ");
	}
}

/*º¸À¯¸®½ºÆ® Áö¿ì±â*/
void clrList() {
	for (int i = 0; i < 40; i++) {
		gotoxytext(110, i, "                       ");
	}

}

/*Ä«µå Áö¿ì±â*/
void clrCard() {

	for (int i = 16; i < 26; i++) {
		gotoxy(112, i); printf("                ");
	}

}

void clrDice()
{
	for (int i = 12; i < 20; i++) {
		gotoxytext(45, i, "                                             ");
	}
}

void SetDrawColor(int turn){
	if (turn == 0)
		PLAYER1
	else if (turn == 1)
		PLAYER2
	else if (turn == 2)
		PLAYER3
	else
		PLAYER4
}