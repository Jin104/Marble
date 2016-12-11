#include "Start.h"
#include "Player.h"	
#include "BuildEvent.h"
#include "Client.h"

Local local[32];	//지역 32개
Player player[4];	//플레이어 2명

LinkedList *list1 = NewList();		//플레이어가 소유한 지역의 리스트
LinkedList *list2 = NewList();
LinkedList *list3 = NewList();
LinkedList *list4 = NewList();

int tNum;
//extern SOCKET sock;
void StartGame(int totalNumber, int playerTurn, char *name,void *socks, bool isServer) {
	
	tNum = totalNumber;

	system("mode con: cols=130 lines=48");
	printf("%d\n", playerTurn);
	Sleep(1000);
	system("cls");
	GameBoard();	//게임판 출력
	DrawPlayer(totalNumber);	//플레이어판 출력
	initLocal();	//지역 초기화
	initPlayerCoord(totalNumber);	//플레이어 정보출력

	PlaySound(NULL, 0, 0);
	int doubleCnt = 0;

	while (1) {

		for (int turn = 0; turn < totalNumber; turn++) {		//플레이어 순서 0:player1  1:player2  2:player3  3:player4

			SetDrawColor(turn);
			gotoxytext(1, 20, player[turn].name);

			GRAY
			gotoxytext(1, 21, "님의 차례입니다!");

			switch (player[turn].state)		//플레이어에 상태를 받아서 그것에대한 이벤트를 발생
			{
			case 2:	//세계여행에있는 상태
				if (WorldTourEvent(turn, playerTurn, socks, isServer) == -1) {
					player[turn].state = 0;	//플레이어상태를 기본으로
					goto A;	//주사위를 굴리는 곳부터
				}
				else {
					goto B;	//다음턴으로
				}

			case 1:	//무인도에있는 상태
				doubleCnt = 0;
				if (IslandEvent(turn, playerTurn, socks, isServer) == -1) {
					player[turn].state = 0;
					goto B;	//다음턴으로
				}
			default:	//기본상태일때
				/*더블이 3번이상일때 무인도로*/
				if (doubleCnt > 2) {
					GoIsland(turn);	//무인도로 이동
					player[turn].marble -= 75;	//무인도로갈때는 월급을 지급하지 않음
					doubleCnt = 0;
					goto B;	//다음턴으로
				}
			A:

				Dice d;
				char sumData[2];
				char equalData[2];
				int select;



				/*선택지 처리    다른 곳의 선택지 처리도 비슷해서 여기에만 주석 달았습니다*/
				//자기의 차례일때
				if (turn == playerTurn) {
					d = GameDice(turn);	//주사위 굴리기
					itoa(d.sum, sumData, 10);
					itoa(d.equal, equalData, 10);
					if (isServer)	//자신이 서버면
					{
						SendMsg(sumData, sizeof(sumData), 0);	//다른 클라이언트에게 결과값 보냄
						SendMsg(equalData, sizeof(equalData), 0);
					}
					else  //서버가 아니면
					{
						send((SOCKET)socks, sumData, sizeof(sumData), 0);	//서버에게 결과값 보냄
						send((SOCKET)socks, equalData, sizeof(equalData), 0);
					}
					select = atoi(sumData);
					MovePlayer(select, turn);	//나온만큼 이동
				}
				else  //자기의 차례가 아니면
				{
					if (isServer)	//자신이 서버면
					{
						SOCKET *sockArr = (SOCKET *)socks;
						while (recv(sockArr[turn], sumData, sizeof(sumData), 0) <= 0);	//결과값을 받음
						while (recv(sockArr[turn], equalData, sizeof(equalData), 0) <= 0);
						SendMsg(sumData, sizeof(sumData), turn);	//받은 결과값을 다른 클라이언트에게 보냄
						SendMsg(equalData, sizeof(equalData), turn);
					}
					else  //서버가 아니면
					{
						while (recv((SOCKET)socks, sumData, sizeof(sumData), 0) <= 0);	//결과값을 받음
						while (recv((SOCKET)socks, equalData, sizeof(equalData), 0) <= 0);
					}
					select = atoi(sumData);
					MovePlayer(select, turn);	//나온만큼 이동
				}
			
				/*3번이상 더블을 제외하고*/
				if (doubleCnt < 2) {
					BuildingEvent(turn, player[turn].board, playerTurn, socks, isServer);	//도착한지역에대한 이벤트
				}
				
				/*더블이나왔을때*/
				if (atoi(equalData)==1 && player[turn].state == 0) {
					turn--;	//턴을 바꾸지않기위해
					doubleCnt++;
				}
				else {
					gotoxy(73, 10);
					printf("             ");
					doubleCnt = 0;
				}
			B:
				gotoxytext(1, 20, "              ");
				gotoxy(48, 20);
				printf("                                     ");
				clrDice();
				clrCard();
				break;

			}
		}
	}
}

/*지역정보 초기화*/
void initLocal() {
	for (int i = 0; i < boardNum; i++) {
		strcpy(local[i].name, localName[i]);
		local[i].price = localPrice[i][0];
		local[i].x = localX[i];
		local[i].y = localY[i];
	}
}

/*초기 플레이어정보 출력*/
void initPlayerCoord(int totalNumber) {

	PLAYER1
		gotoxytext(33, 8, player[0].name);
	gotoxy(player[0].playerX, player[0].playerY);
	printf("◆");
	GRAY
		gotoxy(42, 10); printf("%d", player[0].marble);

	PLAYER2
		gotoxytext(73, 37, player[1].name);
	player[1].playerX = player[0].playerX + 2;
	gotoxy(player[1].playerX, player[1].playerY);
	printf("◆");
	GRAY
		gotoxy(42, 10); printf("%d", player[1].marble);

	if (totalNumber >= 3) {
		PLAYER3
			gotoxytext(33, 37, player[2].name);
		player[2].playerX = player[1].playerX + 2;
		gotoxy(player[2].playerX, player[2].playerY);
		printf("◆");
		GRAY
			gotoxy(42, 10); printf("%d", player[2].marble);

		if (totalNumber > 3) {
			PLAYER4
				gotoxytext(73, 8, player[3].name);
			player[3].playerX = player[2].playerX + 2;
			gotoxy(player[3].playerX, player[3].playerY);
			printf("◆");
			GRAY
				gotoxy(42, 10); printf("%d", player[3].marble);
		}
	}

}

/*플레이어를 이동시켜줌   i:이동시킬숫자  turn:플레이어순서*/
void MovePlayer(int i, int turn) {

	for (int j = 0; j < i; j++) {
		sndPlaySoundA("..\\sound\\DiceItem00000_0.wav", SND_ASYNC | SND_NODEFAULT);
		gotoxytext(player[turn].playerX, player[turn].playerY, "  ");	//이전위치의 말을 지워줌
		player[turn].board++;

		/*출발지를 지나게되면 지역을 다시 0부터*/
		if (player[turn].board > 31) {
			player[turn].board -= 32;
			player[turn].marble += 75;	//출발지를 지나면 월급지급
		}

		/*플레이어의 위치를 지역의 위치로 바꾸고 말 출력*/
		player[turn].playerX = local[player[turn].board].x + (turn * 2);
		player[turn].playerY = local[player[turn].board].y;
		gotoxy(player[turn].playerX, player[turn].playerY);

		SetDrawColor(turn);
		printf("◆");
		GRAY
			Sleep(200);
	}

}
