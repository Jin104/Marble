#include "Start.h"
#include "BuildEvent.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];

void FortuneCard(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

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
	int n = rand() % 7 + 1;

	/*나온수에따라 이벤트발생*/
	switch (n)
	{
	case 1:
		if (isServer)
			HalfAngelCard(turn, playerTurn, socks, true);
		else
			HalfAngelCard(turn, playerTurn, socks, false);
		break;
	case 2:
		if (isServer)
			AngelCard(turn, playerTurn, socks, true);
		else
			AngelCard(turn, playerTurn, socks, false);
		break;
	case 3:
		InviteTravel(turn, playerTurn);
		break;
	case 4:
		if(isServer)
			GoStart(turn, board, playerTurn, socks, true, list);
		else
			GoStart(turn, board, playerTurn, socks, false, list);
		break;
	case 5:
		GoIsland(turn);
		break;
	case 6:
		if (isServer)
			HoldOlympic(turn, playerTurn, socks, true, list);
		else
			HoldOlympic(turn, playerTurn, socks, false, list);
		break;
	case 7:
		if (isServer)
			CompelSale(turn, playerTurn, socks, true);
		else
			CompelSale(turn, playerTurn, socks, false);
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
void HalfAngelCard(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	gotoxytext(37, 27, "★ 천사카드 ★ - 통행료 반값 할인");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardGet_A01.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 30, "카드를 보관합니다.");
		}
		player[turn].card = 1;		//플레이어의 카드상태 변경
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 30, "카드를 버립니다.");
	}
	Sleep(900);
	clrText();
}

/*통행료 면제 카드*/
void AngelCard(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	gotoxytext(37, 27, "★ 천사카드 ★ - 통행료 면제");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardGet_A01.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 30, "카드를 보관합니다.");
		}
		player[turn].card = 2;		//플레이어의 카드상태 변경
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 30, "카드를 버립니다.");
	}
	Sleep(900);
	clrText();
}

/*세계여행으로가는 카드*/
void InviteTravel(int turn, int playerTurn) {
	
	gotoxytext(37, 27, "★ 세계여행 초대권 ★");
	gotoxytext(37, 28, "여행을 떠나요 ~ 지금 즉시 세계여행으로 이동!");
	Sleep(900);

	/*플레이어위치에따라 이동*/
	int now = player[turn].board;
	if (now < 24) {
		MovePlayer(24 - now, turn);
	}
	else {
		MovePlayer(28, turn);
	}
	player[turn].state = 2;	//플레이어의 상태변경
	PlayerState();
}

/*출발지로가는 카드*/
void GoStart(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

	gotoxytext(37, 27, "★ 출발지 GO ★");
	gotoxytext(37, 28, "새 마음 새 출발 ~ 지금 즉시 출발지로 이동!");

	Sleep(900);
	clrText();
	/*플레이어위치에따라 이동*/
	int now = player[turn].board;
	MovePlayer(32 - now, turn);

	if (isServer)
		StartEvent(turn, board, playerTurn, socks, true, list);
	else
		StartEvent(turn, board, playerTurn, socks, false, list);

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
		MovePlayer(8 - now, turn);
	}
	else {
		MovePlayer(40 - now, turn);
		player[turn].marble -= 75;
	}
	player[turn].state = 1;	//플레이어상태 변경
	clrText();
	PlayerState();
}

/*올림픽으로가는 카드*/
void HoldOlympic(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	gotoxytext(37, 27, "★ 올림픽 개최 ★");
	gotoxytext(37, 28, "올림픽 즉시 개최!!! 원하는 곳에 올림픽 개최");
	
	Sleep(900);
	clrText();
	OlympicEvent(turn, playerTurn, socks, isServer, list);	//올림픽개최이벤트 실행
}

/*강제매각 카드*/
void CompelSale(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1,select2, count = 0;
	char data[2];
	char name[10];

	gotoxytext(38, 27, "★ 강제 매각 ★");
	gotoxytext(38, 28, "원하는 상대의 도시를 강제로 매각 (랜드마크 공격불가)");
	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		
		if (turn == playerTurn) {

			gotoxytext(38, 28, "몇번째 플레이어의 지역을 매각할까요?");
			gotoxy(70, 29);
			cursor_view(1);

			do {
				select = _getch() - 48;
				gotoxyint(70, 29, select);
				gotoxytext(70, 29, "      ");

			} while (select != 1 && select != 2 && select != 3 && select != 4);
			cursor_view(0);
			gotoxyint(70, 29, select);
			clrText();
			itoa(select, data, 10);

			if (isServer)
			{
				SendMsg(data, sizeof(data), 0);
			}
			else
			{
				send((SOCKET)socks, data, sizeof(data), 0);
			}
			select2 = atoi(data);
		}
		else
		{
			if (isServer)
			{
				SOCKET *sockArr = (SOCKET *)socks;
				while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
				SendMsg(data, sizeof(data), turn);
			}
			else
			{
				while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
			}
			select2 = atoi(data);
		}

		LinkedList *list;
		if (select2 == 0)
			list = list1;
		else if (select2 == 1)
			list = list2;
		else if (select2 == 2)
			list = list3;
		else
			list = list4;

		/*상대방의 보유지역에서 랜드마크를 뺀 수가 0이면 매각불가*/
		if (list->size - list->size2 < 1) {
			clrText();
			if(turn==playerTurn)
				gotoxytext(38, 28, "매각할 지역이 없습니다.");
			Sleep(900);
			return;
		}
		if (turn == playerTurn)
			sndPlaySoundA("..\\sound\\ChanceCardAtt_A01.wav", SND_ASYNC | SND_NODEFAULT);
		/*도시이름을 제대로 입력할때까지*/
		for (int k = 0; k<1;) {
			clrText();

			if (turn == playerTurn) {
				gotoxytext(38, 27, "매각할 도시 이름을 입력해주세요");
				gotoxytext(38, 29, "☞  ");
				cursor_view(1);
				gotoxy(44, 29);
				scanf("%s", name);
				cursor_view(0);

				if (isServer)
				{
					SendMsg(name, sizeof(name), 0);
				}
				else
				{
					send((SOCKET)socks, name, sizeof(name), 0);
				}
			}
			else
			{
				if (isServer)
				{
					SOCKET *sockArr = (SOCKET *)socks;
					while (recv(sockArr[turn], name, sizeof(name), 0) <= 0);
					SendMsg(name, sizeof(name), turn);
				}
				else
				{
					while (recv((SOCKET)socks, name, sizeof(name), 0) <= 0);
				}
			}

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
				if (turn == playerTurn) {
					gotoxytext(38, 31, "다시 입력해주세요");
					gotoxytext(38, 32, "보유하지 않은 도시나 랜드마크는 공격이 불가능 합니다");
				}
				Sleep(800);
			}
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(40, 28, "카드를 버립니다");
		Sleep(900);
	}

}

/*천사카드 실행*/
int DoAngel(int turn, int price, int playerTurn, void *socks, bool isServer) {
	int select,select1;
	char data[2];
	Sleep(500);

	if (turn == playerTurn) {
		sndPlaySoundA("..\\sound\\ChanceCardUsePop_A01.wav", SND_ASYNC | SND_NODEFAULT);
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
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);

	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) {
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\ChanceCardataef_A03.wav", SND_ASYNC | SND_NODEFAULT);
			gotoxytext(37, 32, "카드를 사용합니다.");
		}
		/*카드 종류에 따라 통행료 변경*/
		if (player[turn].card == 1) {
			price = price / 2;
		}
		player[turn].card = 0;
		clrText();
		return price;
	}
	else {
		if (turn == playerTurn)
			gotoxytext(37, 31, "사용하지 않습니다.");
	}
	Sleep(900);
	clrText();
}