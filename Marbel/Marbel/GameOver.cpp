#include "player.h"
#include "buildEvent.h"
#include "start.h"
#include "draw.h"

extern LinkedList *list1, *list2;   //플레이어1,2의 보유지역 연결리스트
extern Player player[2];
extern Local local[32];

//price = localPrice[board][2];
//marble = player[turn].marble;

int SellBuilding(int turn, int price) {
	//player 2일때 (turn:1)
	LinkedList *list;
	if (turn == 0) { list = list1;}
	else { 	list = list2; }

	int marble = player[turn].marble;
	int cost = price - marble;
	char name[10];
	
	while (price > cost) {
		clrText();
		clrList();
		//gotoxytext(34, 30, "보유한 지역입니다.");
		PrintList(list2);
		gotoxy(34, 30);
		printf("부족한 마블: %d  매각할 지역이름을 입력해주세요.", cost);
		gotoxy(34, 31);
		scanf("%s", name);
		int cnt = 0;
		Node *node = FindNode(list, name);
		/*while (node != NULL) {
			cnt++;
			if (cnt > 0) {
				gotoxy(34, 31);
				printf("다시 입력해주세요.");
				Sleep(500);
				gotoxy(34, 31);
				printf("                  ");
			}
			gotoxy(34, 31);
			scanf("%s", name);
		}*/

		int money = node->price / 2;
		deletNode(list, name);	//노드삭제
		local[node->num].state = -1;
		free(node);
		player[turn].marble += money;
		if (list->size == 0) { return -1; };
	}
	player[turn].marble -= marble - price;
	player[1 - turn].marble += price;
	//gotoxytext(34, 32, "매각을 완료했습니다.");
	return 0;

}

void Bankrupt(int turn, int price) {
	LinkedList *list;
	if (turn == 0) {
		list = list1;
	}
	else {
		list = list2;
	}

	int answer;
	gotoxytext(34, 31, "통행료가 부족합니다.\n");
	gotoxy(48, 31);
	printf("1) 매각  2) 파산  (선택) ▶ ");
	answer = _getch() - 48;
	gotoxy(80, 31); printf("%d", answer);

	if (answer == 1) {
		if (list->size <= 0) {
			clrText();
			gotoxytext(34, 30, "매각할 지역이 없습니다.");
			gotoxytext(34, 31, "파산!!!!");
			exit(1);
		}
		else if (SellBuilding(turn, price) == -1) {
			clrText();
			gotoxytext(34, 30, "모든 건물을 매각해도 부족합니다.");
			gotoxytext(34, 31, "파산!!!!");
			exit(1);
		}
		else {
			gotoxytext(34, 32, "매각을 완료했습니다.");
		}
	}
	else {
		clrText();
		gotoxytext(34, 31, "파산!!!!");
		exit(1);
	}
}