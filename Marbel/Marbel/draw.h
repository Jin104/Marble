#pragma once

#include "graphics.h"

/*주사위 각 주사위의 값, 합의 값*/
typedef struct {
	int dice1;
	int dice2;
	int sum;
}Dice;

Dice GameDice(int i);	//주사위 굴리기
void DoubleDice();	//주사위 더블이 나왔을때 사용
void GameBoard();	//게임판
void DiceShape(int dice);	//주사위 그림1
void DiceShape2(int dice2);	//주사위 그림2
void DrawPlayer(int totalNumber);	//플레이어 창
void PlayerState();	//플레이어 마블상태

void Menu();	//메뉴
void Explain();	//설명
void Loading();	//로딩화면
void clrText();	//텍스트 출력 지우기
void clrList();	//지역리스트 출력 지우기
void clrCard();	//카드 출력 지우기