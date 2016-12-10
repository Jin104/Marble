#pragma once

#include "SpecialLocal.h"
#include "FortuneCard.h"
#include "GameOver.h"
#include "Player.h"


void BuildingEvent(int turn, int board, int playerTurn, void *socks, bool isServer);	//������ ���¿� ���� �߻��ϴ� �̺�Ʈ
void BuildRandmark(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//������ ȣ���϶� ���帶ũ�� �Ǽ�
void Takeover(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list, LinkedList *myList);	//������ ȣ���϶� �μ�

