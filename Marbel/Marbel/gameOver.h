#pragma once

void Bankrupt(int turn, int price);	//파산
int SellBuilding(int turn, int price);	//매각

void TouristMonop(int turn);	//관광지독점
void ColorMonop(int turn);	//트리플 독점(컬러독점3개)
void LineMonop(int turn);	//라인독점

void CheckGameOver(int turn);	//독점함수 3개를 모아놓음