#pragma once

void Bankrupt(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list);	//파산
int SellBuilding(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list);	//매각

void TouristMonop(int turn, int playerTurn);	//관광지독점
void ColorMonop(int turn, int playerTurn);	//트리플 독점(컬러독점3개)
void LineMonop(int turn, int playerTurn);	//라인독점

void CheckGameOver(int turn, int playerTurn);	//독점함수 3개를 모아놓음