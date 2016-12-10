#pragma once

#include "SpecialLocal.h"
#include "FortuneCard.h"
#include "GameOver.h"
#include "Player.h"


void BuildingEvent(int turn, int board, int playerTurn, void *socks, bool isServer);	//지역의 상태에 따라 발생하는 이벤트
void BuildRandmark(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//지역이 호텔일때 랜드마크를 건설
void Takeover(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list, LinkedList *myList);	//지역이 호텔일때 인수

