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
	int state = 0;	//0: �⺻ 1:������Ǽ� 2:���ε� 3:���迩��
	//char LocalName[10];
}Player;

void StartGame();
void initLocal();
void initPlayerCoord();
void movePlayer(int i, int turn);
void playerTurn();
