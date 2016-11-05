#pragma once

#include "specialLocal.h"
#include "fortuneCard.h"
#include "gameOver.h"

void buildBuilding(int turn, int board);


//sate //-1: 비어있음 0:player1의 호텔 1:player2의 호텔 2:player1의 랜드마크 
//3:player2의 랜드마크 4:player1의 관광지 5:player2의 관광지

void BuildRandmark(int turn, int board);
void Takeover(int turn, int board);

