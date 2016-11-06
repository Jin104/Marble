#pragma once

#define TURN1 0
#define TURN2 1

typedef struct _Player{

	int turn = 0;
	int board=0;
	int playerX=21;
	int playerY=45;
	char name[10];
	int marble = 5000000;
	int dCount = 0;
	
}Player;

void StartGame();
void initLocal();
void initPlayerCoord();
void movePlayer(int i, int turn);
void playerTurn();
