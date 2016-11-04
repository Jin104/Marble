#include "player.h"
#include "start.h"
#include "draw.h"

extern Player player[2];
extern Local local[32];

void bonusEvent(int i) {
	int select, select2;
	int correct;
	gotoxytext(48, 29, "★ 동전 게임 맞추기 ★");
	gotoxytext(48, 30, "1) 앞면  2) 뒷면  (선택) ☞");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	srand(time(NULL));
	correct = rand() % 2 + 1;
	if (correct == 1) {
		if (correct == select) {
			gotoxytext(48, 32, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			player[i].marble += 50;
		}
		else
			gotoxytext(48, 32, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}
	else {
		if (correct == select) {
			gotoxytext(48, 32, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			player[i].marble += 50;
		}
		else
			gotoxytext(48, 33, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}

	Sleep(1000);
	clrText();
}

void StartEvent(int i) {
	if (player[i].board >= boardNum) { //?
		gotoxytext(48, 29, "한바퀴를 돌아서 월급이 지급되었습니다!");
		player[i].marble += 750000;
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                           ");
}

void IslandEvent(int i) {
	int select;
	if (player[i].board == 8) {
		gotoxytext(48, 29, "★무인도 탈출 방법★");
		gotoxytext(48, 30, "무인도에 갇혔습니다! 탈출방법 (선택) ☞ ");
		gotoxytext(48, 31, "1) 주사위 더블 3번   2) 50만 마블 지불");
		select = _getch() - 48;
		gotoxy(80, 31); printf("%d", select);
		if (select == 1) {
			Dice GameDice();
			//무인도 탈출
		}
		else {
			player[i].marble -= 50;
			gotoxytext(48, 33, "50만 마블이 지불 되었습니다");
		}
		Sleep(500);
		clrText();
	}
}

void OlympicEvent(int i) {
	char name[10];
	if (player[i].board == 16) {
		gotoxytext(48, 29, "★올림픽 개최★");
		gotoxytext(48, 30, "원하는 지역의 이름을 입력하면 통행료 2배 ~");
		gotoxytext(48, 31, "(단, 자신의 지역만 가능): ");
		scanf("%s", name[10]);
		local[i].price *= 2;
		gotoxytext(48, 33, "통행료 2배가 상승되었습니다!");
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                                ");
	gotoxy(48, 30);
	printf("                                                ");
	gotoxy(48, 31);
	printf("                                                ");
	gotoxy(48, 33);
	printf("                                                ");
}

void WorldTourEvent(int i) {
	char name[10];
	if (player[i].board == 24) {
		gotoxytext(48, 29, "★세계 여행★");
		gotoxytext(48, 30, "원하는 지역의 이름을 입력하면 세계여행 ~");
		scanf("%s", name);
		while (player[i].board != 0) {
			player[i].turn = 1;
		}
		//gotoxytext(48, 32, "다음 턴때 세계여행 가능!");
		for (i = 0; i<boardNum; i++) {
			if (!strcmp(local[i].name, local->name)) { //?
			}
		}


		Sleep(1000);
		gotoxy(48, 29);
		printf("                                              ");
		gotoxy(48, 30);
		printf("                                              ");
		gotoxy(48, 32);
		printf("                                              ");
	}
}
void TaxEvent(int i) {
	int tax;
	if (player[i].board == 31) {
		gotoxytext(48, 29, "★국세청★");
		gotoxytext(48, 30, "국세청 입니다 세금을 지불해주세요");
		gotoxytext(48, 31, "(자신의 지역/건물 10% 징수)");
		tax = (local[i].price) * (0.1);
		player[i].marble -= tax;
		Sleep(1000);
		gotoxytext(48, 33, "세금 지불이 완료 되었습니다");
	}
	Sleep(1000);
	gotoxy(48, 29);
	printf("                                              ");
	gotoxy(48, 30);
	printf("                                              ");
	gotoxy(48, 31);
	printf("                                              ");
	gotoxy(48, 33);
	printf("                                              ");
}