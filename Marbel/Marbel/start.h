#pragma once

typedef struct _Player{
	int turn = 0;	//playerTurn에서 Turn정해줄때
	int board=0;	//
	int playerX=21;	//위치X좌표
	int playerY=45;	//위치Y좌표
	char name[10];	//이름
	int marble = 1000;	//보유마블
	int state = 0;	//상태 0: 기본 1:출발지 2:무인도 3:세계여행
	int card = 0;	//소유카드 0: 기본 1:천사카드 2:반천사카드
	int count = 0;	//무인도에 갇혔을때 던진 주사위 턴 수
}Player;

void StartGame();
void initLocal();
void initPlayerCoord();
void movePlayer(int i, int turn);
void playerTurn();
