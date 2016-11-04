#pragma once

#include "specialLocal.h"
void buildBuilding(int turn, int board);


//sate //-1: ������� 0:player1�� ȣ�� 1:player2�� ȣ�� 2:player1�� ���帶ũ 
//3:player2�� ���帶ũ 4:player1�� ������ 5:player2�� ������

void BuildRandmark(int turn, int board);
void Takeover(int turn, int board);
void PayMarble(int turn, int price);


void Bankrupt(int turn, int price);
int SellBuilding(int turn, int price);