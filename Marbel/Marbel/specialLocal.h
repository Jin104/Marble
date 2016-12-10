#pragma once

#include "Player.h"
void BonusEvent(int turn, int board, int playerTurn, void *socks, bool isServer);	//보너스게임
void StartEvent(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//출발지
int IslandEvent(int turn, int playerTurn, void *socks, bool isServer);	//무인도
void OlympicEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//올림픽개최
int WorldTourEvent(int turn, int playerTurn, void *socks, bool isServer);	//세계이동
void TaxEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//국세청