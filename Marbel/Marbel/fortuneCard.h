#pragma once

#include "Player.h"
void FortuneCard(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//포츈카드 랜덤으로 생성해서 뽑음
void DrawFortuneCard();	//카드 그림1
void DrawFortuneCard2();	//카드 그림2

void HalfAngelCard(int turn, int playerTurn, void *socks, bool isServer);	//반천사 카드
void AngelCard(int turn, int playerTurn, void *socks, bool isServer);	//천사 카드
void InviteTravel(int turn, int playerTurn);	//세계여행초대 카드
void GoStart(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//출발지로가는 카드
void GoIsland(int turn);	//무인도로가는 카드
void HoldOlympic(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//올림픽을 개최하는 카드
void CompelSale(int turn, int playerTurn, void *socks, bool isServer);	//강제매각 카드

int DoAngel(int turn, int price, int playerTurn, void *socks, bool isServer);	//반천사,천사카드가 있을때 사용
