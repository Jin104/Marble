#include "Player.h"
#include "BuildEvent.h"
#include "Start.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
extern Local local[32];
extern int tNum;
char data[2];
void BuildingEvent(int turn, int board, int playerTurn, void *socks, bool isServer) {

	/*
	turn=> 현재 플레이어 번호		0:player1  1:player2  2:player3  3:player4
	borad=> 플레이어가있는 지역번호
	state=> 지역의 구매상태
	-1: 비어있음    0~3각 플레이어의 호텔     4~7각 플레이어의 랜드마크     8~11각 플레이어의 관광지
	board=> 지역의 특수성   0시작 2보너스게임 4,9,14,18,25관광지 8무인도 12,20,28포츈카드 16올림픽 24세계여행 30국세청
	*/

	int select;
	int select1;
	int state = local[board].state;

	LinkedList *list;
	if (turn == 0)
		list = list1;
	else if(turn == 1)
		list = list2;
	else if (turn == 2)
		list = list3;
	else
		list = list4;

	switch (board)
	{
	case 0:	//출발지
		StartEvent(turn, board, playerTurn, socks, isServer, list);
		break;
	case 2:	//보너스게임
		BonusEvent(turn, board, playerTurn, socks, isServer);
		PlayerState(tNum);
		break;
	case 8:	//무인도
		if(turn==playerTurn)
			gotoxytext(37, 28, "무인도 당첨 다음 턴에 탈출 가능 !");
		Sleep(800);
		clrText();
		player[turn].state = 1;
		break;
	case 12: case 20: case 28:
		FortuneCard(turn, board, playerTurn, socks, isServer, list);
		break;
	case 16:
		OlympicEvent(turn, playerTurn, socks, isServer, list);
		PlayerState(tNum);
		break;
	case 24:
		gotoxytext(37, 28, "세계여행 ~~ 다음턴에 원하는곳으로 이동 !");
		Sleep(800);
		clrText();
		player[turn].state = 2;
		break;
	case 30:
		TaxEvent(turn, playerTurn, socks, isServer, list);
		break;
	default:

		switch (state)
		{
		case -1:   //지역이 비어있을때
			if (player[turn].marble >= local[board].price) {	//구매할돈이 있으면
				
				if (turn == playerTurn) {

					gotoxytext(37, 27, "비어있는 지역입니다. 구매하시겠습니까?");
					gotoxytext(37, 28, "1) YES  2) NO  (선택) ☞ ");

					gotoxy(70, 28);
					cursor_view(1);
					do {
						select = _getch() - 48;
						gotoxyint(70, 28, select);
						gotoxytext(70, 28, "      ");
					} while (select != 1 && select != 2);
					cursor_view(0);
					gotoxyint(70, 28, select);
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
							
				Sleep(500);

				if (select1 == 1) {
					if (board != 4 && board != 9 && board != 14 && board != 18 && board != 25) {   //관광지는 제외
						gotoxytext(37, 30, "호텔을 건설했습니다.");
						local[board].state = turn;   //지역의 상태를 바꿔줌
					}
					else {
						gotoxytext(37, 30, "관광지를 구매했습니다.");
						local[board].state = turn + 8;   //지역의 상태를 바꿔줌
					}

					player[turn].marble -= localPrice[board][0];   //보유 마블 감소

					Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //새로운 지역노드생성
					HangNode(list, node);   //플레이어의 리스트에 지역노드를 연결해줌
					if (turn == playerTurn) {
						PrintList(list);
					}
					SetDrawColor(turn);
					gotoxytext(local[board].x, local[board].y - 2, "▲▲▲");
					GRAY
				}
			}
			else {
				gotoxy(37, 27);
				printf("구매할 돈이 부족합니다.\n");
			}
			break;

		case 0:   //player1의 호텔이 지어져있는경우
			if (turn == 0){
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else 
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*지역이 올림픽 상태면 통행료 2배 증가*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn) {
					printf("통행료는 %d마블 입니다.", toll);
				}

				int price = toll;
				/*보유한 카드가 있으면*/
				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn) {
						printf("통행료는 %d마블 입니다.", price);
					}
				}

				/*보유마블이 통행료보다 적으면 파산실행(건물매각)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*인수할 것인지*/

				Takeover(turn, board, playerTurn, socks, isServer, list1, list);
				
				Sleep(500);

			}
			break;

		case 1:	//player2의 호텔이 지어져있는경우
			if (turn == 1)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*지역이 올림픽 상태면 통행료 2배 증가*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				/*보유한 카드가 있으면*/
				if (player[turn].card == 1 || player[turn].card == 2) {

					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("통행료는 %d마블 입니다.", price);
				}

				/*보유마블이 통행료보다 적으면 파산실행(건물매각)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*인수할 것인지*/
				Takeover(turn, board, playerTurn, socks, isServer, list2, list);

				Sleep(500);

			}
			break;

		case 2:	//player3의 호텔이 지어져있는경우
			if (turn == 2)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*지역이 올림픽 상태면 통행료 2배 증가*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				/*보유한 카드가 있으면*/
				if (player[turn].card == 1 || player[turn].card == 2) {

					price -= DoAngel(turn, toll, playerTurn, socks, isServer);

					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("통행료는 %d마블 입니다.", price);
				}

				/*보유마블이 통행료보다 적으면 파산실행(건물매각)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*인수할 것인지*/
				Takeover(turn, board, playerTurn, socks, isServer, list2, list);
				Sleep(500);

			}
			break;
		case 3:	//player4의 호텔이 지어져있는경우
			if (turn == 3)
			{
				BuildRandmark(turn, board, playerTurn, socks, isServer, list);
			}
			else
			{
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				/*지역이 올림픽 상태면 통행료 2배 증가*/
				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				/*보유한 카드가 있으면*/
				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					if (turn == playerTurn)
						printf("통행료는 %d마블 입니다.", price);
				}

				/*보유마블이 통행료보다 적으면 파산실행(건물매각)*/
				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}

				/*인수할 것인지*/
				Takeover(turn, board, playerTurn, socks, isServer, list3, list);
				Sleep(500);

			}
			break;

		case 4:	//player1의 랜드마크가 지어져있는경우
			if (turn != 0) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if(turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 5:	//player2의 랜드마크가 지어져있는경우
			if (turn != 1) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 6:	//player3의 랜드마크가 지어져있는경우
			if (turn != 2) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 7:	//player4의 랜드마크가 지어져있는경우
			if (turn != 3) {
				gotoxy(37, 28);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;

		case 8:	//player1의 관광지인 경우
			if (turn != 0) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 9:
			if (turn != 1) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 10:
			if (turn != 2) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		case 11:
			if (turn != 3) {
				gotoxy(37, 28);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				if (turn == playerTurn)
					printf("통행료는 %d마블 입니다.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll, playerTurn, socks, isServer);
					gotoxy(37, 31);
					printf("통행료는 %d마블 입니다.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll, playerTurn, socks, isServer, list);
				}
				else {
					player[turn].marble -= price;
				}
				Sleep(500);
			}
			break;
		default:
			break;
		}

		PlayerState(tNum);
		Sleep(700);
		clrList();
		clrText();
		
		CheckGameOver(turn, playerTurn);
		break;
	}
}

void BuildRandmark(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select;
	int select1;
	
	if(turn == playerTurn){
		gotoxytext(37, 27, "랜드마크를 건설하시겠습니까?");
		gotoxy(37, 28);
		printf("1) YES  2) NO  (선택) ☞ ");

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

	if (select1 == 1) {
		if (player[turn].marble >= localPrice[board][1]) {
			if (turn == playerTurn) {
				sndPlaySoundA("..\\sound\\LandMark_A01.wav", SND_ASYNC | SND_NODEFAULT);
				gotoxytext(37, 30, "랜드마크를 건설했습니다.");
			}
			local[board].state = turn + 4;      //지역의 상태변경
			local[board].price = localPrice[board][3];   //지역의 가격변경

			player[turn].marble -= localPrice[board][1];
			modifiNode(list, local[board].name, localPrice[board][3]);	//지역노드의 가격수정

			SetDrawColor(turn);
			gotoxytext(local[board].x, local[board].y - 2, "♣♣♣");	//랜드마크 모양으로 변경
			GRAY
		}
		else
		{
			if (turn == playerTurn)
			{
				gotoxytext(37, 30, "건설할 돈이 없습니다.");
			}
		}
	}
}

void Takeover(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list, LinkedList *myList) {

	int select, select1;
	Sleep(500);
	if (player[turn].marble > localPrice[board][0]) {   //인수할 돈이 있을때
		if (turn == playerTurn) {
			gotoxy(37, 27);
			printf("인수하시겠습니까? 인수료는 %d입니다.\n", localPrice[board][0]);
			gotoxy(37, 28);
			printf("1) YES  2) NO  (선택) ☞ ");

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

		if (select1 == 1) {
			Sleep(500);
			gotoxytext(37, 30, "인수를 완료했습니다.\n");
			clrText();
			player[turn].marble -= localPrice[board][0];   //보유마블 감소
			player[1 - turn].marble += localPrice[board][0];
			local[board].state = turn;   //지역의 상태 변경
			Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //지역노드 생성
			
			deletNode(list, local[board].name);   //상대방의 연결리스트에서 지역노드 삭제
			
			HangNode(myList, node);   //자신의 연결리스트에 지역노드 연결
			SetDrawColor(turn);
			gotoxytext(local[board].x, local[board].y - 2, "▲▲▲");
			GRAY
			return;
		}
	}
	else {
		gotoxy(37, 30);
		printf("인수할 돈이 부족합니다.\n");
		clrText();
	}
}
