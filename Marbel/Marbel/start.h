#pragma once

#define TURN1 0
#define TURN2 1

typedef struct _Player {
	int playerBoard=0;
	int playerX=21;
	int playerY=44;
	char name[10];
	int marble = 5000000;
	
}Player;

void StartGame();
void movePlayer(int i);