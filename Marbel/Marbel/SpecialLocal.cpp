#include "player.h"
#include "start.h"
#include "draw.h"
#include "gameOver.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void BonusEvent(int i) {
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

	int select;
	char name[10];
	gotoxytext(48, 29, "★출발지 혜택★");
	gotoxytext(48, 30, "자신의 지역에 랜드마크 건설 가능! (관광지/랜드마크인곳은 불가)");
	gotoxytext(35, 31, "1) 건설 2)취소  ▶ ");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {

		LinkedList *list;
		if (i == 0) {
			list = list1;
		}
		else {
			list = list2;
		}

		PrintList(list);

		int cnt = 0;
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == i + 4 || local[j].state == i + 2) {
				cnt++;
			}
		}

		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				gotoxy(75, 31); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {

					if (local[node->num].state != i + 4 || local[node->num].state != i + 2) {
						k++;
						local[node->num].state = i + 2;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][i + 2]);
						if (i == 0) {
							gotoxytext(local[node->num].x, local[node->num].y - 2, "♧♧♧");
						}
						else {
							gotoxytext(local[node->num].x, local[node->num].y - 2, "♣♣♣");
						}

						gotoxytext(48, 33, "랜드마크를 지었습니다!");
						Sleep(500);
						clrText();
					}
					else {
						clrText();
						gotoxy(48, 34); printf("관광지나 랜드마크는 불가능합니다.");
						Sleep(700);
						clrText();
					}
				}
				else {
					clrText();
					gotoxy(48, 34); printf("없는 지역 입니다. 다시 입력해주세요. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			gotoxy(48, 34); printf("건설할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "건설하지 않습니다.");
	}

	Sleep(500);
	clrText();
}

int IslandEvent(int i) {
	int select;
	gotoxytext(48, 29, "★ 무인도 ★");
	gotoxytext(48, 30, "무인도에 갇혔습니다! 탈출방법 (선택) ☞ ");
	gotoxytext(48, 31, "1) 한턴 쉬기   2) 50만 마블 지불");
	select = _getch() - 48;
	gotoxy(80, 31); printf("%d", select);
	if (select == 1) {
		gotoxy(48, 33); printf("한턴 쉽니다");
		Sleep(500);
		clrText();
		return -1;
	}
	else {
		player[i].marble -= 50;
		gotoxytext(48, 33, "50만 마블이 지불 되었습니다");
		player[i].state = 0;
		player[i].count = 0;
		Sleep(500);
		clrText();
		return 0;
	}
	

}

void OlympicEvent(int i) {
	int select;
	char name[10] = " ";
	gotoxytext(48, 29, "★올림픽 개최★");
	gotoxytext(48, 30, "원하는 지역의 이름을 입력하면 통행료가 2배 ~");
	gotoxytext(35, 31, "1) 개최 2)취소  ▶ ");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {
		LinkedList *list;
		if (i == 0) {
			list = list1;
		}
		else {
			list = list2;
		}

		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				gotoxy(75, 31); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {
					k++;
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}

					local[node->num].olystate = 1;

					gotoxytext(48, 33, "통행료 2배가 상승되었습니다!");
					Sleep(500);
					clrText();

				}
				else {
					clrText();
					gotoxy(48, 34); printf("없는 지역 입니다. 다시 입력해주세요. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			gotoxy(48, 34); printf("개최할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "개최하지 않습니다.");
	}

	Sleep(500);
	clrText();

}

int WorldTourEvent(int i) {
	char name[10];
	int select;
	gotoxytext(48, 29, "★세계 여행★");
	gotoxytext(48, 30, "원하는 지역의 이름을 입력하면 세계여행 ~");
	gotoxytext(48, 31, "1) 여행 2)취소");
	select = _getch() - 48;
	gotoxy(60, 31); printf("%d", select);
	if (select == 1) {
		if (player[i].marble <= 10) {
			gotoxytext(48, 31, "여행경비가 부족합니다.");
			return -1;
		}

		int cnt = 0;
		while (cnt != 0) {
			gotoxy(48, 31); scanf("%s", name);

			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					cnt++;
				}
			}

			if (cnt == 0) {
				//local[]
				gotoxy(48, 34); printf("이동합니다");
				player[i].marble -= 10;
				player[i].state = 0;
			}
			else {
				clrText();
				gotoxy(48, 34); printf("없는 지역 입니다. 다시 입력해주세요. ");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		gotoxytext(48, 33, "개최하지 않습니다.");
	}

	Sleep(1000);
	clrText();

}

void TaxEvent(int i) {
	int tax = 0;

	gotoxytext(48, 29, "★국세청★");
	gotoxytext(48, 30, "국세청 입니다 세금을 지불해주세요");
	gotoxytext(48, 31, "(자신의 지역/건물 10% 징수)");
	for (int k = 0; k < 32; k++) {
		if (local[k].state == i || local[k].state == i + 2 || local[k].state == i + 4) {
			tax += local[k].price;
		}
	}
	tax = (0.1)*tax;
	gotoxy(70, 30); printf("세금: %d ", tax);

	if (player[i].marble >= tax) {
		player[i].marble -= tax;
		Sleep(2000);
		gotoxytext(48, 33, "세금 지불이 완료 되었습니다");
	}else{
		Bankrupt(i, tax);
	}

	PlayerState();
	Sleep(1000);
	clrText();
}
