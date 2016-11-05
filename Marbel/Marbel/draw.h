#pragma once

#include "graphics.h"

typedef struct {
	int dice1;
	int dice2;
	int sum;
}Dice;

Dice GameDice(int i);
void DoubleDice();
void GameBoard();
void DiceShape(int dice);
void DiceShape2(int dice2);
void DrawPlayer();

void Explain();
void Loading();
void clrText();
void PlayerState();
void clrList();
void clrCard();