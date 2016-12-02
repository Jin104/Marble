#pragma once

#include "Draw.h"

void StartGame(int totalNumber, int playerTurn);	//게임시작
void initLocal();	//지역초기화
void initPlayerCoord(int totalNumber);	//플레이어초기화
void MovePlayer(int i, int turn);	//플레이어 이동
void PlayerTurn(int totalNumber);	//플레이어 순서 정하기
void StartGame2(void* playerturn);