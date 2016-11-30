#include "Start.h"
#include "Player.h"
#include "BuildEvent.h"

Local local[32];	//지역 32개
Player player[4];	//플레이어 2명

LinkedList *list1 = NewList();		//플레이어가 소유한 지역의 리스트
LinkedList *list2 = NewList();
LinkedList *list3 = NewList();
LinkedList *list4 = NewList();

void StartGame(int totalNumber, int playerTurn, char *name) {

	PlayerTurn(totalNumber);	//순서

	system("mode con: cols=130 lines=48");
	printf("%d\n", totalNumber);
	system("pause");
	GameBoard();	//게임판 출력
	DrawPlayer(totalNumber);	//플레이어판 출력
	initLocal();	//지역 초기화
	initPlayerCoord(totalNumber);	//플레이어 정보출력

	PlaySound(NULL, 0, 0);
	int doubleCnt = 0;
	while (1) {

		for (int i = 0; i < totalNumber; i++) {		//플레이어 순서 0:player1  1:player2

			if (i == 0)
				PLAYER1
			else if(i==1)
				PLAYER2
			else if(i==2)
				PLAYER3
			else
				PLAYER4

			gotoxytext(1, 20, player[i].name);

			GRAY
				gotoxytext(1, 21, "님의 차례입니다!");

			switch (player[i].state)		//플레이어에 상태를 받아서 그것에대한 이벤트를 발생
			{
			case 2:	//세계여행에있는 상태
				if (WorldTourEvent(i) == -1) {
					player[i].state = 0;	//플레이어상태를 기본으로
					goto A;	//주사위를 굴리는 곳부터
				}
				else {
					goto B;	//다음턴으로
				}

			case 1:	//무인도에있는 상태
				doubleCnt = 0;
				if (IslandEvent(i) == -1) {
					player[i].state = 0;
					goto B;	//다음턴으로
				}
			default:	//기본상태일때
				/*더블이 3번이상일때 무인도로*/
				if (doubleCnt > 2) {
					GoIsland(i);	//무인도로 이동
					player[i].marble -= 75;	//무인도로갈때는 월급을 지급하지 않음
					doubleCnt = 0;
					goto B;	//다음턴으로
				}
			A:
				Dice d;
				d = GameDice(i);	//주사위 굴리기
				MovePlayer(d.sum, i);	//나온만큼 이동

										/*3번이상 더블을 제외하고*/
				if (doubleCnt < 2) {
					BuildingEvent(i, player[i].board);	//도착한지역에대한 이벤트
				}

				/*더블이나왔을때*/
				if (d.dice1 == d.dice2 && player[i].state == 0) {
					i--;	//턴을 바꾸지않기위해
					doubleCnt++;
					gotoxy(73, 10);
					printf("더블 %d번째", doubleCnt);
				}
				else {
					gotoxy(73, 10);
					printf("             ");
					doubleCnt = 0;
				}
			B:
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
		gotoxy(42, 10); printf("%d", player[0].marble);

	if (totalNumber >= 3) {
		PLAYER3
			gotoxytext(33, 37, player[2].name);
		player[2].playerX = player[1].playerX + 2;
		gotoxy(player[2].playerX, player[2].playerY);
		printf("◆");
		GRAY
			gotoxy(42, 10); printf("%d", player[0].marble);

		if (totalNumber > 3) {
			PLAYER4
				gotoxytext(73, 8, player[3].name);
			player[3].playerX = player[2].playerX + 2;
			gotoxy(player[3].playerX, player[3].playerY);
			printf("◆");
			GRAY
				gotoxy(42, 10); printf("%d", player[0].marble);
		}
	}
	GRAY
		gotoxy(42, 10); printf("%d", player[0].marble);
	gotoxy(82, 39); printf("%d", player[1].marble);

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

		if (turn == 0)
			PLAYER1
		else if(turn == 1)
			PLAYER2
		else if(turn == 2)
			PLAYER3
		else
			PLAYER4

		printf("◆");
		GRAY
			Sleep(200);
	}

}

/*플레이어 순서를 정해줌*/
void PlayerTurn(int totalNumber) {

	//for (int i = 0; i < totalNumber; i++) {
	//	//player[i].myTurn=

	//}

	Sleep(800);
}