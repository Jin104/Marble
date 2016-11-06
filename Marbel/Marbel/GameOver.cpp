#include "Player.h"
#include "BuildEvent.h"
#include "Start.h"

extern LinkedList *list1, *list2;   //플레이어1,2의 보유지역 연결리스트
extern Player player[2];
extern Local local[32];

/*건물 매각*/
int SellBuilding(int turn, int price) {

	LinkedList *list;
	if (turn == 0)
		list = list1;
	else
		list = list2;

	char name[10];
	
	/*지불금액이 플레이어의 보유마블보다 큰경우*/
	while (price > player[turn].marble) {

		clrText();
		clrList();
		gotoxytext(37, 27, "매각가는 절반입니다.");
		PrintList(list);
		gotoxy(65, 27);
		printf("%d 마블이 부족합니다.", price - player[turn].marble);
		gotoxy(37, 29); printf("매각할 지역이름을 입력해주세요.");
		gotoxytext(37, 30, "입력 ☞ ");
		cursor_view(1);
		gotoxy(53, 30); scanf("%s", name);
		cursor_view(0);

		Node *node = FindNode(list, name);	//리스트에서 입력한지역이 있는지 확인
		int cnt = 0;
		if (node != NULL) {	//있으면

			int money = node->price / 2;	//매각가는 가격의 절반

			local[node->num].state = -1;	//건물의 상태를 기본으로
			gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");	//건물그림 지우기
			deletNode(list, name);	//노드삭제
			player[turn].marble += money;	//보유마블에 매각가 더하기
			PlayerState();

			/*노드의 개수가 0일때*/
			if (list->size < 1) {
				gotoxytext(37, 32, "더이상 매각할건물이 없습니다.");
				Sleep(900);
				return -1;
			};
		}
		else {
			gotoxytext(37, 32, "다시 입력해주세요.");
			Sleep(500);
			gotoxytext(37, 32, "                  ");
		}
	}

	/*매각이 끝나면 상대방에게 마블 지급*/
	player[turn].marble -= price;
	player[1 - turn].marble += price;
	PlayerState();
	return 0;

}

/*파산*/
void Bankrupt(int turn, int price) {
	LinkedList *list;
	if (turn == 0)
		list = list1;
	else
		list = list2;
	
	int select;
	gotoxytext(37, 27, "통행료가 부족합니다.\n");
	gotoxy(37, 28);
	printf("1) 매각  2) 파산  (선택) ☞ ");

	gotoxy(73, 28);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 29, select);

	if (select == 1) {
		if (SellBuilding(turn, price) == -1) {
			clrText();
			gotoxytext(37, 27, "모든 건물을 매각해도 부족합니다..");
			Sleep(700);
			clrText();
			gotoxy(45, 30);
			printf("%s님의 파산승리!", player[1 - turn].name);
			
			gotoxytext(37, 33, "Enter키를 누르면 게임이 종료됩니다!");
			getch();
			system("pause>null");
			exit(1);
		}
		else {
			gotoxytext(37, 27, "매각을 완료했습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 27, "이런! 상대방의 파산승리로 패배 ! GAME OVER..");
		gotoxytext(37, 29, "Enter키를 누르면 게임이 종료됩니다!");
		gotoxy(37, 31);
		exit(1);
	}
}

void TouristMonop(int turn) {
	int cnt = 0;
	for (int i = 0; i < boardNum; i++) {
		if (local[i].state == 4) {
			cnt++;
		}
	}
	if (cnt == 5) {
		clrText();
		gotoxy(37, 27); printf("축하합니다! %s님의 관광지독점 승리!", player[turn].name);
		gotoxytext(37, 29, "Enter키를 누르면 게임이 종료됩니다!");
		gotoxy(37, 31);
		exit(1);
	}
}

void ColorMonop(int turn) {
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
	int color = 0;
	
	//local[1].state
}

void LineMonop(int turn) {

	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	for (int i = 1; i < 8; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt1++;
		}
	}

	for (int i = 9; i < 16; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt2++;
		}
	}

	for (int i = 17; i < 24; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt3++;
		}
	}

	for (int i = 25; i < 32; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt4++;
		}
	}
	if (cnt1 == 6 || cnt2 == 6 || cnt3 == 6 || cnt4 == 5) {
		clrText();
		gotoxy(37, 27); printf("축하합니다! %s님의 라인독점 승리!", player[turn].name);
		gotoxytext(37, 29, "Enter키를 누르면 게임이 종료됩니다!");
		gotoxy(37, 31);
		exit(1);
	}


}

void CheckGameOver(int turn) {
	TouristMonop(turn);
	ColorMonop(turn);
	LineMonop(turn);
}