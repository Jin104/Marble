#include "player.h"
#include "Start.h"
#include "BuildEvent.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void BonusEvent(int i) {

	int select, correct;
	gotoxytext(37, 27, "★ 동전 게임 맞추기 ★");
	gotoxytext(37, 28, "1) 앞면  2) 뒷면  (선택) ☞");
	
	gotoxy(70, 28);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	srand(time(NULL));
	correct = rand() % 2 + 1;

	if (correct == 1) {
		if (correct == select) {
			gotoxytext(37, 30, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			player[i].marble += 50;
		}
		else
			gotoxytext(37, 30, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}
	else {
		if (correct == select) {
			gotoxytext(37, 30, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			player[i].marble += 50;
		}
		else
			gotoxytext(37, 30, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}

	Sleep(800);
	clrText();
}

/*출발지 건설 이벤트*/
void StartEvent(int i) {

	int select;
	char name[10];
	gotoxytext(37, 27, "★ 출발지 혜택 ★");
	gotoxytext(37, 28, "자신의 지역에 랜드마크 건설 가능!");
	gotoxytext(37, 29, "1) 건설 2)취소  (선택) ☞ ");
	
	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);

	if (select == 1) {

		LinkedList *list;
		if (i == 0) 
			list = list1;
		else
			list = list2;

		PrintList(list);

		int cnt = 0;
		/*보유한 호텔과 랜드마크의 수*/
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == i + 4 || local[j].state == i + 2) {
				cnt++;
			}
		}

		/*보유한 건물의 수가 있을때*/
		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				gotoxytext(37, 28, "랜드마크를 지을 건물을 입력하세요. (관광지 불가)");
				gotoxy(38, 28); 
				scanf("%s", name);
				Node *node = FindNode(list, name);
				
				/*소유하나 지역을 입력할때*/
				if (node != NULL) {

					/*지역의 상태가 랜드마크가 아닐때*/
					if (local[node->num].state != i + 4 && local[node->num].state != i + 2) {
						k++;
						local[node->num].state = i + 2;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][i + 2]);
						if (i == 0)
							PLAYER1
						else
							PLAYER2
						
						gotoxytext(local[node->num].x, local[node->num].y - 2, "♣♣♣");
						gotoxytext(37, 33, "랜드마크를 지었습니다!");
						Sleep(500);
						clrText();
					}
					else {
						gotoxy(37, 33); printf("관광지나 랜드마크는 불가능합니다.");
						Sleep(700);
						clrText();
					}
				}
				else {
					gotoxy(37, 33); printf("없는 지역 입니다. 다시 입력해주세요. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			gotoxy(37, 28); printf("건설할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 28, "건설하지 않습니다.");
	}

	Sleep(900);
	clrText();
	clrList();
}

/*무인도*/
int IslandEvent(int i) {
	int select;
	gotoxytext(37, 27, "★ 무인도 ★");
	gotoxytext(37, 28, "무인도에 갇혔습니다! 탈출방법 (선택) ☞ ");
	gotoxytext(37, 29, "1) 한턴 쉬기   2) 50만 마블 지불");

	gotoxy(80, 28);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);


	if (select == 1) {
		gotoxy(37, 31); 
		printf("한턴 쉽니다");
		Sleep(900);
		clrText();
		return -1;
	}
	else {
		player[i].marble -= 50;
		gotoxytext(37, 31, "50만 마블이 지불 되었습니다");
		player[i].state = 0;
		player[i].count = 0;
		Sleep(900);
		clrText();
		return 0;
	}


}

/*올림픽*/
void OlympicEvent(int i) {
	int select;
	char name[10];
	gotoxytext(37, 27, "★ 올림픽 개최 ★");
	gotoxytext(37, 28, "원하는 지역의 이름을 입력하면 통행료가 2배 ~");
	gotoxytext(37, 29, "1) 개최 2)취소  ☞ ");
	
	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);


	if (select == 1) {

		LinkedList *list;
		if (i == 0)
			list = list1;
		else
			list = list2;

		PrintList(list);
		/*보유지역이 있을때*/
		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				gotoxytext(37, 27, "도시의 이름을 입력하세요 ☞ ");
				gotoxy(70, 27); scanf("%s", name);
				Node *node = FindNode(list, name);
				if (node != NULL) {
					k++;
					/*다른지역의 올림픽상태를 해제*/
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}
					/*입력한지역에 올림픽개최*/
					local[node->num].olystate = 1;

					gotoxytext(37, 32, "통행료 2배가 상승되었습니다!");
					Sleep(900);
					clrText();

				}
				else {
					gotoxy(37, 31); printf("없는 지역 입니다. 다시 입력해주세요. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			gotoxy(37, 28); printf("개최할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 28, "개최하지 않습니다.");
	}

	Sleep(900);
	clrText();

}

/*세계여행*/
int WorldTourEvent(int i) {
	char name[10];
	int select;
	gotoxytext(37, 27, "★ 세계 여행 ★");
	gotoxytext(37, 28, "원하는 지역의 이름을 입력하면 세계여행 ~");
	gotoxytext(37, 29, "1) 여행 2)취소 ☞");

	gotoxy(70, 29);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);

	if (select == 1) {
		clrText();
		if (player[i].marble < 10) {
			gotoxytext(37, 33, "여행경비가 부족합니다.");
			return -1;
		}

		int cnt = 0;
		for (int k = 0; k < 1;) {
			int n;
			clrText();
			gotoxytext(37, 29, "여행할 곳을 입력하세요  ☞");
			gotoxy(70, 29); 
			cursor_view(1); 
			scanf("%s", name);
			cursor_view(0);
			
			/*입력한게 월드맵에 있는지*/
			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					/*포츈카드 입력시*/
					if (j == 12) {
						for (int m = 0; m < 1;) {
							gotoxytext(37, 32, "몇번째 포츈카드로 갈까요? ☞");
							int k;
							gotoxy(70, 32); scanf("%d", &k);
							switch (k)
							{
							case 1:
								m++;
								n = 12;
								break;
							case 2:
								m++;
								n = 20;
								break;
							case 3:
								m++;
								n = 28;
								break;
							default:
								gotoxytext(37, 33, "잘못입력하셨습니다.");
								Sleep(500);
								clrText();
								break;
							}
						}

					}else{
						n = j;
					}
					cnt++;
					break;
				}
			}
			if (cnt > 0) {
				clrText();
				gotoxytext(37, 33, "이동합니다");
				k++;
				player[i].marble -= 10;
				player[i].state = 0;
				int move;
				
				if (n > 24) {
					move = n - 24;
				}else{
					move = n + 8;
				}
				movePlayer(move, i);
				BuildingEvent(i, player[i].board);
			}
			else {
				clrText();
				gotoxy(37, 33); printf("없는 지역 입니다. 다시 입력해주세요. ");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		gotoxytext(37, 33, "여행하지 않습니다.");
		return -1;
	}

	Sleep(900);
	clrText();

}

void TaxEvent(int i) {
	int tax = 0;

	gotoxytext(37, 27, "★ 국세청 ★");
	gotoxytext(37, 28, "국세청 입니다 세금을 지불해주세요");
	gotoxytext(37, 29, "[자신의 지역/건물 10% 징수]");

	for (int k = 0; k < 32; k++) {
		if (local[k].state == i || local[k].state == i + 2 || local[k].state == i + 4) {
			tax += local[k].price;
		}
	}

	tax = (0.1)*tax;
	gotoxy(70, 30); printf("세금은 %d 마블 입니다", tax);

	if (player[i].marble >= tax) {
		player[i].marble -= tax;
		Sleep(1000);
		gotoxytext(37, 32, "세금 지불이 완료 되었습니다");
	}
	else {
		Bankrupt(i, tax);
	}

	PlayerState();
	Sleep(900);
	clrText();
}
