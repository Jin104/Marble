#pragma once

#define TURN1 0
#define TURN2 1

typedef struct _Player{
	int turn = 0;
	int board=0;
	int playerX=21;
	int playerY=45;
	char name[10];
	int marble = 300;
	int dCount = 0;	
	int state = 0;	//0: 기본 1:출발지건설 2:무인도 3:세계여행
	//char LocalName[10];
}Player;

void StartGame();
void initLocal();
void initPlayerCoord();
void movePlayer(int i, int turn);
void playerTurn();
