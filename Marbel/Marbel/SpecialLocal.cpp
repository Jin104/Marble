#include "player.h"
#include "Start.h"
#include "BuildEvent.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];
extern int tNum;

//유나
//보너스 게임 이벤트
void BonusEvent(int turn, int board, int playerTurn, void *socks, bool isServer) {

	int select, select1, correct;
	char data[2];

	if (turn == playerTurn) {
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

	srand(time(NULL));
	correct = rand() % 2 + 1;

	if (correct == 1) {
		if (correct == select1) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\Maccau_Success_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			}
			if (turn == playerTurn)
				player[turn].marble += 50;
		}
		else
			gotoxytext(37, 30, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}
	else {
		if (correct == select1) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\Maccau_Success_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "짝짝짝 ~ 맞추셨습니다! 50만 마블 지급!");
			}
			player[turn].marble += 50;
		}
		else
			if (turn == playerTurn)
				gotoxytext(37, 30, "맞추지 못했습니다...다음에 다시 도전하세요!");
	}

	Sleep(800);
	clrText();
}

/*출발지 건설 이벤트*/
void StartEvent(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {

	int select;
	int select1;
	char data[2];

	char name[10];
	if (turn == playerTurn) {
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
	else {
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

		if(turn==playerTurn)
			PrintList(list);

		int cnt = 0;
		/*보유한 호텔과 랜드마크의 수*/
		for (int j = 0; j < boardNum; j++) {
			if (local[j].state == turn + 4 || local[j].state == turn + 2) {
				cnt++;
			}
		}

		/*보유한 건물의 수가 있을때*/
		if (list->size - cnt > 0) {

			for (int k = 0; k < 1;) {
				if (turn == playerTurn) {
					clrText();
					gotoxytext(37, 28, "랜드마크를 지을 건물을 입력하세요. (관광지 불가)");
					gotoxy(37, 29);
					scanf("%s", name);

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
				
				/*소유한 지역을 입력할때*/
				if (node != NULL) {

					/*지역의 상태가 랜드마크가 아닐때*/
					if (local[node->num].state != turn + 4 && local[node->num].state != turn + 8) {
						k++;
						local[node->num].state = turn + 4;
						local[node->num].price = localPrice[node->num][3];
						modifiNode(list, name, localPrice[node->num][3]);
						
						SetDrawColor(turn);
						gotoxytext(local[node->num].x, local[node->num].y - 2, "♣♣♣");
						GRAY
						sndPlaySoundA("..\\sound\\LandMark_A01.wav", SND_ASYNC | SND_NODEFAULT);
						if(turn==playerTurn)
							gotoxytext(37, 33, "랜드마크를 건설했습니다!");
						Sleep(500);
						clrText();
					}
					else {
						if (turn == playerTurn)
							gotoxytext(37, 33, "관광지나 랜드마크는 불가능합니다.");
						Sleep(700);
						clrText();
					}
				}
				else {
					if (turn == playerTurn)
						gotoxytext(37, 33, "없는 지역 입니다. 다시 입력해주세요.");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			if (turn == playerTurn)
				gotoxytext(37, 28, "건설할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 28, "건설하지 않습니다.");
	}

	Sleep(900);
	clrText();
	clrList();
}

/*무인도*/
int IslandEvent(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	char data[2];

	if (turn == playerTurn) {
		gotoxytext(37, 27, "★ 무인도 ★");
		gotoxytext(37, 28, "무인도에 갇혔습니다! 탈출방법 (선택) ☞ ");
		gotoxytext(37, 29, "1) 한턴 쉬기   2) 50만 마블 지불");

		gotoxy(80, 28);
		cursor_view(1);
		do {
			select = _getch() - 48;
			gotoxyint(80, 28, select);
			gotoxytext(80, 28, "      ");

		} while (select != 1 && select != 2);
		cursor_view(0);
		gotoxyint(80, 28, select);
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
		if(turn==playerTurn)
			gotoxytext(37, 31, "한턴 쉽니다");
		Sleep(900);
		clrText();
		return -1;
	}
	else {
		player[turn].marble -= 50;
		if (turn == playerTurn)
			gotoxytext(37, 31, "50만 마블이 지불 되었습니다");
		player[turn].state = 0;	//플레이어 상태 변경
		Sleep(900);
		clrText();
		return 0;
	}
}

/*올림픽*/
void OlympicEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select, select1;
	char name[10];
	char data[2];

	if (turn == playerTurn) {
		sndPlaySoundA("..\\sound\\Olympic_A01.wav", SND_ASYNC | SND_NODEFAULT);
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
		
		if(turn==playerTurn)
			PrintList(list);

		/*보유지역이 있을때*/
		if (list->size > 0) {

			for (int k = 0; k < 1;) {
				clrText();
				if (turn == playerTurn) {
					gotoxytext(37, 27, "도시의 이름을 입력하세요 ☞ ");
					gotoxy(70, 27); scanf("%s", name);

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

				if (node != NULL) {
					k++;
					/*다른지역의 올림픽상태를 해제*/
					for (int i = 0; i < 32; i++) {
						local[i].olystate = 0;
					}
					/*입력한지역에 올림픽개최*/
					local[node->num].olystate = 1;

					if(turn==playerTurn)
						gotoxytext(37, 32, "통행료 2배가 상승되었습니다!");
					Sleep(900);
					clrText();

				}
				else {
					if (turn == playerTurn)
						gotoxytext(37, 31, "없는 지역 입니다. 다시 입력해주세요. ");
					Sleep(700);
					clrText();
				}
			}
		}
		else {
			clrText();
			if (turn == playerTurn)
				gotoxytext(37, 28, "개최할 지역이 없습니다.");
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 28, "개최하지 않습니다.");
	}

	Sleep(900);
	clrText();

}

/*세계여행*/
int WorldTourEvent(int turn, int playerTurn, void *socks, bool isServer) {
	int select, select1;
	int k, k1;
	char name[10];
	char data[2];
	
	if (turn == playerTurn) {
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
		clrText();
		if (player[turn].marble < 10) {
			if(turn==playerTurn)
				gotoxytext(37, 33, "여행경비가 부족합니다.");
			return -1;
		}

		if (turn == playerTurn)
			sndPlaySoundA("..\\sound\\WorldTour_A01.wav", SND_ASYNC | SND_NODEFAULT);
		
		int cnt = 0;
		for (int k = 0; k < 1;) {
			int n;

			if (turn == playerTurn) {
				clrText();
				gotoxytext(37, 29, "여행할 곳을 입력하세요  ☞");
				gotoxy(70, 29);
				cursor_view(1);
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

			/*입력한게 월드맵에 있는지*/
			for (int j = 0; j < boardNum; j++) {
				if (strcmp(local[j].name, name) == 0) {
					/*포츈카드 입력시*/
					if (j == 12) {
						for (int m = 0; m < 1;) {

							if (turn == playerTurn) {
								gotoxytext(37, 32, "몇번째 포츈카드로 갈까요? ☞");
								gotoxy(70, 32);
								k = getch() - 48;
								gotoxyint(70, 32, k);
								clrText();
								itoa(k, data, 10);

								if (isServer)
								{
									SendMsg(data, sizeof(data), 0);
								}
								else
								{
									send((SOCKET)socks, data, sizeof(data), 0);
								}
								k1 = atoi(data);
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
								k1 = atoi(data);
							}

							switch (k1)
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
								if (turn == playerTurn)
									gotoxytext(37, 33, "잘못입력하셨습니다.");
								Sleep(500);
								clrText();
								break;
							}
						}
					}
					else {
						n = j;
					}
					cnt++;
					break;
				}
			}
			if (cnt > 0) {
				clrText();
				if (turn == playerTurn)
					gotoxytext(37, 33, "이동합니다");
				k++;
				player[turn].marble -= 10;
				player[turn].state = 0;
				int move;

				if (n > 24) {
					move = n - 24;
				}
				else {
					move = n + 8;
				}
				MovePlayer(move, turn);
				BuildingEvent(turn, player[turn].board, playerTurn,socks, isServer);
			}
			else {
				clrText();
				if (turn == playerTurn)
					gotoxytext(37, 33, "없는 지역 입니다. 다시 입력해주세요.");
				Sleep(700);
				clrText();
			}
		}
	}
	else {
		clrText();
		if (turn == playerTurn)
			gotoxytext(37, 33, "여행하지 않습니다.");
		return -1;
	}

	Sleep(900);
	clrText();
}

//유나
//국세청 이벤트
void TaxEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	int tax = 0;

	if (turn == playerTurn) {
		gotoxytext(37, 27, "★ 국세청 ★");
		gotoxytext(37, 28, "국세청 입니다 세금을 지불해주세요");
		gotoxytext(37, 29, "[자신의 지역/건물 10% 징수]");
	}
	for (int k = 0; k < 32; k++) {
		if (local[k].state == turn || local[k].state == turn + 4 || local[k].state == turn + 8) {
			tax += local[k].price;
		}
	}

	tax = (0.1)*tax;
	if (turn == playerTurn)
		gotoxy(70, 30); printf("세금은 %d 마블 입니다", tax);

	if (player[turn].marble >= tax) {
		player[turn].marble -= tax;
		Sleep(1000);
		if (turn == playerTurn)
			gotoxytext(37, 32, "세금 지불이 완료 되었습니다");
	}
	else {
		Bankrupt(turn, tax, playerTurn, socks, isServer, list);
	}

	PlayerState(tNum);
	Sleep(900);
	clrText();
}
