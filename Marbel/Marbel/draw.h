#pragma once

#include "graphics.h"

typedef struct {
	int dice1;
	int dice2;
	int sum;
}Dice;

Dice GameDice();
void DoubleDice();
void GameBoard();
void DiceShape(int dice);
void DiceShape2(int dice2);
void DrawPlayer();

void Explain();
void Loading();