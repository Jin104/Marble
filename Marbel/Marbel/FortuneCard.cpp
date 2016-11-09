#include "Start.h"
#include "BuildEvent.h"
#include "Player.h"

extern LinkedList *list1, *list2;
extern Player player[2];
extern Local local[32];

void FortuneCard(int turn) {
	
	clrText();

	/*카드모양 회전*/
	for (int i = 0; i < 6; i++) {
		Sleep(30);
		DrawFortuneCard();
		Sleep(30);
		DrawFortuneCard2();
		Sleep(30);
		DrawFortuneCard();
	}

	/*1부터 7까지 랜덤한 수 생성*/
	srand(time(NULL));
	int n = 1;// rand() % 7 + 1;

	/*나온수에따라 이벤트발생*/
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
	clrText();
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

/*통행료 반값 카드*/
void HalfAngelCard(int turn) {
	int select;
	gotoxytext(37, 27, "★ 천사카드 ★ - 통행료 반값 할인");
	gotoxytext(37, 28, "1) 보관  2) 버리기 (선택) ☞");
	gotoxy(70, 28);
	cursor_view(1);

	/*1또는 2를 입력할때까지*/
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	if (select == 1) {
		gotoxytext(37, 30, "카드를 보관합니다.");
		player[turn].card = 1;		//플레이어의 카드상태 변경
	}
	else {
		gotoxytext(37, 30, "카드를 버립니다.");
	}
	Sleep(900);
	clrText();
}

/*통행료 면제 카드*/
void AngelCard(int turn) {
	int select;
	gotoxytext(37, 27, "★ 천사카드 ★ - 통행료 면제");
	gotoxytext(37, 28, "1) 보관  2) 버리기 (선택) ☞");
	gotoxy(70, 28);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	if (select == 1) {
		gotoxytext(37, 30, "카드를 보관합니다.");
		player[turn].card = 2;
	}
	else {
		gotoxytext(37, 30, "카드를 버립니다.");
	}
	Sleep(900);
	clrText();
}

/*세계여행으로가는 카드*/
void InviteTravel(int turn) {
	gotoxytext(37, 27, "★ 세계여행 초대권 ★");
	gotoxytext(37, 28, "여행을 떠나요 ~ 지금 즉시 세계여행으로 이동!");
	Sleep(900);

	/*플레이어위치에따라 이동*/
	int now = player[turn].board;
	if (now < 24) {
		movePlayer(24 - now, turn);
	}
	else {
		movePlayer(28, turn);
	}
	player[turn].state = 2;	//플레이어의 상태변경
	PlayerState();
}

/*출발지로가는 카드*/
void GoStart(int turn) {
	gotoxytext(37, 27, "★ 출발지 GO ★");
	gotoxytext(37, 28, "새 마음 새 출발 ~ 지금 즉시 출발지로 이동!");
	Sleep(900);
	clrText();
	/*플레이어위치에따라 이동*/
	int now = player[turn].board;
	movePlayer(32 - now, turn);

	StartEvent(turn);	//출발지이벤트 실행
	PlayerState();

}

/*무인도로가는 카드*/
void GoIsland(int turn) {
	clrText();
	gotoxytext(37, 27, "★ 무인도 탐험 ★");
	gotoxytext(37, 28, "너무 앞서갔네요.. 지금 즉시 무인도로 이동!");
	Sleep(900);
	
	/*플레이어위치에따라 이동*/
	int now = player[turn].board;
	if (now < 8) {
		movePlayer(8 - now, turn);
	}
	else {
		movePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 1;	//플레이어상태 변경
	clrText();
	PlayerState();
}

/*올림픽으로가는 카드*/
void HoldOlympic(int turn) {
	gotoxytext(37, 27, "★ 올림픽 개최 ★");
	gotoxytext(37, 28, "올림픽 즉시 개최!!! 원하는 곳에 올림픽 개최");
	Sleep(900);
	clrText();
	OlympicEvent(turn);	//올림픽개최이벤트 실행
}

/*강제매각 카드*/
void CompelSale(int turn) {
	int select, count = 0;
	char name[10];
	gotoxytext(38, 27, "★ 강제 매각 ★");
	gotoxytext(38, 28, "원하는 상대의 도시를 강제로 매각 (랜드마크 공격불가)");
	gotoxytext(38, 29, "1) 매각  2) 버리기 (선택) ☞"); 

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
		if (turn == 0)
			list = list2;
		else
			list = list1;

		/*상대방의 보유지역에서 랜드마크를 뺀 수가 0이면 매각불가*/
		if (list->size - list->size2 < 1) {
			clrText();
			gotoxytext(40, 28, "매각할 지역이 없습니다.");
			Sleep(900);
			return;
		}

		/*도시이름을 제대로 입력할때까지*/
		for(int k=0;k<1;){
			clrText();
			gotoxytext(38, 27, "매각할 도시 이름을 입력해주세요");
			gotoxytext(38, 29, "☞  ");
			cursor_view(1);
			gotoxy(44, 29);
			scanf("%s", name);
			cursor_view(0);
			Node *node = FindNode(list, name);

			/*입력한 도시가 없거나, 랜드마크인 경우는 매각 불가*/
			if (node != NULL && local[node->num].state != 2 && local[node->num].state != 3) {
				count++;
				k++;
				local[node->num].state = -1;	//도시의 상태를 기본으로 변경
				player[1 - turn].marble += node->price / 2;	//상대방에게 매각한 돈을 줌
				gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");	//건물그림 지움
				deletNode(list, name);	//상대방의 리스트에서 지역노드 삭제
			}
			else {
				gotoxytext(38, 31, "다시 입력해주세요");
				gotoxytext(38, 32, "보유하지 않은 도시나 랜드마크는 공격이 불가능 합니다");
				Sleep(800);
			}
		}
	}
	else {
		clrText();
		gotoxytext(40, 28, "카드를 버립니다");
		Sleep(900);
	}

}


/*천사카드 실행*/
int DoAngel(int turn, int price) {
	int select;
	Sleep(500);
	if (player[turn].card == 1) {
		gotoxytext(37, 27, "통행료 반값 할인 카드가 보관되어있습니다.");
	}
	else {
		gotoxytext(37, 27, "통행료 면제 카드가 보관되어있습니다.");
	}
	gotoxytext(37, 28, "보관된 카드를 사용하시겠습니까?");
	gotoxytext(37, 29, "1) 사용  2) 미사용 (선택) ☞ ");

	gotoxy(70, 29);
	cursor_view(1);

	do {
		select = _getch() - 48;
		gotoxyint(70, 29, select);
		gotoxytext(70, 29, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);
	clrText();
	if (select == 1) {
		gotoxytext(37, 32, "카드를 사용합니다.");
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		clrText();
		return price;
	}
	else {
		gotoxytext(37, 31, "사용하지 않습니다.");
	}
	Sleep(900);
	clrText();
}