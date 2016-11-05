#include "draw.h"
#include "fortuneCard.h"
#include "specialLocal.h"
#include "player.h"
#include "start.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void FortuneCard(int turn) {
	
	clrText();

	for (int i = 0; i < 6; i++) {
		Sleep(50);
		DrawFortuneCard();
		Sleep(50);
		DrawFortuneCard2();
	}

	srand(time(NULL));
	int n = 1;// rand() % 7 + 1;

	switch (n)
	{
	case 1:
		HalfAngelCard(turn);
		break;
	case 2:
		AngelCard(turn);
		break;
	case 3:
		InviteTravel(turn);
		break;
	case 4:
		GoStart(turn);
		break;
	case 5:
		GoIsland(turn);
		break;
	case 6:
		HoldOlympic(turn);
		break;
	case 7:
		CompelSale(turn);
		break;
	default:
		break;
	}

	//Sleep(700);
	clrText();
	//getchar();
	clrCard();
}

void DrawFortuneCard() {
	gotoxy(112, 16); printf("┏━━━━━┓");
	gotoxy(112, 17); printf("┃          ┃");
	gotoxy(112, 18); printf("┃  ★★★  ┃");
	gotoxy(112, 19); printf("┃ ★    ★ ┃");
	gotoxy(112, 20); printf("┃     ★   ┃");
	gotoxy(112, 21); printf("┃    ★    ┃");
	gotoxy(112, 22); printf("┃          ┃");
	gotoxy(112, 23); printf("┃    ★    ┃");
	gotoxy(112, 24); printf("┃          ┃");
	gotoxy(112, 25); printf("┗━━━━━┛");
}

void DrawFortuneCard2() {
	gotoxy(112, 16); printf("┏━━━━━┓");
	gotoxy(112, 17); printf("┃          ┃");
	gotoxy(112, 18); printf("┃  ☆☆☆  ┃");
	gotoxy(112, 19); printf("┃ ☆    ☆ ┃");
	gotoxy(112, 20); printf("┃   ☆     ┃");
	gotoxy(112, 21); printf("┃    ☆    ┃");
	gotoxy(112, 22); printf("┃          ┃");
	gotoxy(112, 23); printf("┃    ☆    ┃");
	gotoxy(112, 24); printf("┃          ┃");
	gotoxy(112, 25); printf("┗━━━━━┛");
}

void HalfAngelCard(int turn) {
	int select;
	gotoxytext(48, 30, "★ 천사카드 ★");
	gotoxytext(48, 31, "통행료 반값 할인");
	gotoxytext(48, 32, "1) 보관  2) 버리기 (선택) ☞");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {
		gotoxytext(48, 33, "카드를 보관합니다.");
		player[turn].card = 1;		
	}
	else {
		gotoxytext(48, 33, "카드를 버립니다.");
	}
	Sleep(700);
	clrText();
}

void AngelCard(int turn) {
	int select;
	gotoxytext(48, 30, "★ 천사카드 ★");
	gotoxytext(48, 31, "통행료 면제");
	gotoxytext(48, 32, "1) 보관  2) 버리기 (선택) ☞");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {
		gotoxytext(48, 33, "카드를 보관합니다.");
		player[turn].card = 2;
	}
	else {
		gotoxytext(48, 33, "카드를 버립니다.");
	}
}

void InviteTravel(int turn) {
	gotoxytext(48, 30, "★ 세계여행 초대권 ★");
	gotoxytext(35, 31, "여행을 떠나요 ~ 지금 즉시 세계여행으로 이동!");
	Sleep(700);
	int now = player[turn].board;
	
	if (now < 24) {
		movePlayer(24 - now, turn);
	}
	else {
		movePlayer(28, turn);
	}
	player[turn].state = 3;	//다음턴에 이동하는거니까
	PlayerState();
}

void GoStart(int turn) {
	gotoxytext(48, 30, "★ 출발지 GO ★");
	gotoxytext(35, 31, "새 마음 새 출발 ~ 지금 즉시 출발지로 이동!");
	Sleep(700);

	int now = player[turn].board;
	movePlayer(32 - now, turn);

	StartEvent(turn);
	PlayerState();

}

void GoIsland(int turn) {
	clrText();
	gotoxytext(48, 30, "★ 무인도 탐험 ★");
	gotoxytext(35, 31, "너무 앞서갔네요.. 지금 즉시 무인도로 이동!");
	Sleep(700);
	
	int now = player[turn].board;

	if (now < 8) {
		movePlayer(8 - now, turn);
	}
	else {
		movePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 2;
	clrText();
	PlayerState();
}

void HoldOlympic(int turn) {
	gotoxytext(48, 30, "★ 올림픽 개최 ★");
	gotoxytext(35, 31, "올림픽 즉시 개최!!! 원하는 곳에 올림픽 개최");
	Sleep(500);
	clrText();
	OlympicEvent(turn);
}

//void ChangeLocal(int turn) {
//
//	gotoxytext(48, 43, "★ 도시 체인지 ★");
//	gotoxytext(48, 44, "원하는 상대의 도시와 내 도시를 맞교환 (랜드마크 건설된 도시 공격불가)");
//
//}

void CompelSale(int turn) {
	int select, count = 0;
	char name[10];
	gotoxytext(48, 30, "★ 강제 매각 ★");
	gotoxytext(35, 31, "원하는 상대의 도시를 강제로 매각 (랜드마크 공격불가)");
	gotoxytext(48, 32, "1) 매각  2) 버리기 (선택) ☞");
	select = _getch() - 48;
	gotoxy(80, 30); printf("%d", select);
	if (select == 1) {

		LinkedList *list;
		if (turn == 0) { list = list2; }
		else { list = list1; }

		if (list->size - list->size2 < 1) {
			clrText();
			gotoxy(48, 30); printf("list->size : %d", list->size);
			gotoxy(48, 31); printf("list->size : %d", list->size2);
			gotoxytext(35, 32, "매각할 지역이 없습니다.");
			Sleep(500);
			return;
		}
		for(int k=0;k<1;){
			clrText();
			gotoxytext(35, 32, "매각할 도시 이름을 입력해주세요");
			gotoxy(35, 33);
			scanf("%s", name);
			Node *node = FindNode(list, name);

			if (node != NULL && local[node->num].state != 2 && local[node->num].state != 3) {
				count++;
				k++;
				local[node->num].state = -1;
				player[1 - turn].marble += node->price / 2;
				gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");
				deletNode(list, name);
			}
			else {
				gotoxytext(35, 34, "다시 입력해주세요.");
				gotoxytext(35, 35, "보유하지 않은 도시나 랜드마크는 공격이 불가능 합니다.");
				Sleep(500);
			}
		}
	}
	else {
		gotoxytext(48, 33, "카드를 버립니다.");
	}

}



int DoAngel(int turn, int price) {
	int select;
	if (player[turn].card == 1) {
		gotoxy(34, 30); printf("통행료 반값 할인 카드가 보관되어있습니다.");
	}
	else {
		gotoxy(34, 30); printf("통행료 면제 카드가 보관되어있습니다.");
	}
	gotoxytext(34, 31, "보관된 카드를 사용하시겠습니까?");
	gotoxytext(34, 32, "1) 사용  2) 미사용 (선택) ☞");
	select = _getch() - 48;
	gotoxy(70, 32); printf("%d", select);
	if (select == 1) {
		gotoxytext(34, 33, "카드를 사용합니다.");
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		return price;
	}
	else {
		gotoxytext(34, 34, "사용하지 않습니다.");
	}
	Sleep(500);
	clrText();
}